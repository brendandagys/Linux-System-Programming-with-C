/* Add up sizes of all files in the current directory */

#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>

int main() {
  DIR *d;
  struct dirent *info; // A directory entry
  struct stat sb;      // The stat buffer
  long total = 0;      // Total of file sizes

  d = opendir(".");

  while ((info = readdir(d)) != NULL) {
    stat(info->d_name, &sb);
    printf("Name: %s | Type: %d\n", info->d_name, info->d_type);
    total += sb.st_size;
  }

  closedir(d);

  printf("Total size = %ld\n", total);
}
