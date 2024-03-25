#include <stdio.h>
#include <sys/stat.h>
#include <time.h>

int main() {
  struct stat sb; // The stat buffer

  stat("01-03-foo", &sb);

  printf("Last accessed: %s", ctime(&sb.st_atime));
  printf("Last modified: %s", ctime(&sb.st_mtime));
  printf("Last changed: %s", ctime(&sb.st_ctime));
}
