/* Build a histogram of modification hours of files */

#include <dirent.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

// Hour-by-hour histogram of modification times
int modtimehist[24];
int rflag = 0, aflag = 0;

void process_file(char *name) {
  struct stat sb;    // The stat buffer
  struct tm *bdtime; // Broken-down time

  printf("Processing file %s\n", name);

  if (stat(name, &sb) < 0) {
    perror(name);
    exit(2);
  }

  bdtime = localtime(&sb.st_mtime); // Modification time
  modtimehist[bdtime->tm_hour]++;
}

void process_dir(char *dirname) {
  DIR *d;
  struct dirent *info;
  char fullfilename[PATH_MAX];
  struct stat sb;

  printf("Processing directory %s\n", dirname);
  d = opendir(dirname);
  if (d == NULL) {
    perror(dirname);
    exit(1);
  }

  while ((info = readdir(d)) != NULL) {
    if (info->d_name[0] == '.' && !aflag)
      continue;

    // Build absolute name of the file
    strcpy(fullfilename, dirname);
    strcat(fullfilename, "/");
    strcat(fullfilename, info->d_name);

    // Recurse if `rflag` is set, but not on `.` or `..`
    stat(fullfilename, &sb);

    if (strcmp(info->d_name, ".") && strcmp(info->d_name, "..") && rflag &&
        S_ISDIR(sb.st_mode))
      process_dir(fullfilename); // Recurse
    else
      process_file(fullfilename);
  }

  closedir(d);
}

int main(int argc, char *argv[]) {
  int i, c;
  char dirname[PATH_MAX];

  // Zero-out the histogram
  for (i = 0; i < 24; i++)
    modtimehist[i] = 0;

  opterr = 0; // Suppress `getopt`s own error messages

  while ((c = getopt(argc, argv, "ar")) != EOF) {
    switch (c) {
    case 'a':
      aflag = 1;
      break;
    case 'r':
      rflag = 1;
      break;
    case '?':
      fprintf(stderr, "Invalid option: -%c\n", optopt);
    }
  }

  argv += optind; // Adjust to move past the options
  argc -= optind;

  if (argc != 1) {
    fprintf(stderr, "Usage: modtimehist [-a] [-r] dirname\n");
    exit(1);
  }

  // If not an absolute path, make it one
  if (argv[0][0] == '/')
    strncpy(dirname, argv[0], PATH_MAX);
  else {
    getcwd(dirname, PATH_MAX);
    strcat(dirname, "/");
    strcat(dirname, argv[0]);
  }

  process_dir(dirname);

  // Display the histogram
  for (i = 0; i < 24; i++)
    printf("Hour %2d: count = %6d\n", i, modtimehist[i]);
}
