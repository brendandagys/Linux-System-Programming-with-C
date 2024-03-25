/* Monitor specified files for change, using `inotify` */

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/inotify.h>
#include <sys/stat.h>
#include <sys/types.h>

// A buffer big enough to read 100 events at a time
#define BUFSIZE (100 * (sizeof(struct inotify_event) + NAME_MAX + 1))

int main() {
  FILE *fconfig; // Descriptor for config file
  FILE *fout;    // Descriptor for output file
  char watchname[PATH_MAX];
  struct stat sb; // Stat buffer
  int notifyfd, watchfd;
  char eventbuf[BUFSIZE]; // Events are read into here
  int n;
  char *p;
  struct inotify_event *event;

  // Holds the names of the watched files, indexed by the watch descriptor
  char watchednames[100][NAME_MAX + 1];

  notifyfd = inotify_init(); // Not checked for error

  // Open the config file
  if ((fconfig = fopen("monitor.conf", "r")) == NULL) {
    printf("Unable to open the config file\n");
    exit(1);
  }

  // Read all watched file names from config file
  while (fgets(watchname, PATH_MAX, fconfig) != NULL) {
    // Remove the newline
    watchname[strlen(watchname) - 1] = '\0';

    if (stat(watchname, &sb) < 0) {
      printf("Cannot stat %s, ignored\n", watchname);
      continue;
    }

    if (S_ISREG(sb.st_mode)) {
      // Regular file; add to watch list
      if ((watchfd = inotify_add_watch(notifyfd, watchname,
                                       IN_MODIFY | IN_DELETE_SELF)) < 0) {
        printf("Error adding watch for %s\n", watchname);
      } else {
        printf("Added %s to watch list on descriptor %d\n", watchname, watchfd);
        // Record the file watched on this watch descriptor
        strcpy(watchednames[watchfd], watchname);
      }
    } else {
      printf("%s is not a regular file; ignored\n", watchname);
    }
  }

  // All watches are in place; now just read and report events
  fout = fopen("monitor.out", "a");

  while (1) {
    // Multiple events could be delivered
    n = read(notifyfd, eventbuf, BUFSIZE);

    // Loop over all events and report them. Tricky, because event records are not of fixed length
    for (p = eventbuf; p < eventbuf + n;) {
      // Cast memory at `p` to a pointer of type `struct inotify_event`
      event = (struct inotify_event *) p;
      p += sizeof(struct inotify_event) + event->len;
      // Display the event
      if (event->mask & IN_MODIFY) fprintf(fout, "%s was modified\n", watchednames[event->wd]);
      if (event->mask & IN_DELETE_SELF) fprintf(fout, "%s was deleted\n", watchednames[event->wd]);
      fflush(fout);
    }
  }
}
