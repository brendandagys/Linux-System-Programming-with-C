#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

struct record {
  int id;
  char name[80];
};

int main() {
  int fd, size = sizeof(struct record);
  struct record info;

  fd = open("02-03-datafile", O_RDWR);

  lseek(fd, size, SEEK_SET); // Skip one record
  read(fd, &info, size);     // Read second record

  info.id = 99;               // Modify second record
  lseek(fd, -size, SEEK_CUR); // Backspace
  write(fd, &info, size);     // Write modified second record

  close(fd);
}
