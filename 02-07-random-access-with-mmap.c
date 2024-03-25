#include <fcntl.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>

struct record {
  int id;
  char name[80];
};

int main() {
  int fd;
  size_t size;
  struct record *records;

  fd = open("foo", O_RDWR);
  size = lseek(fd, 0, SEEK_END); // Seek to end of file to get offset/size

  // Map in the whole file, viewing it as an array of records
  records = (struct record *)mmap(NULL, size, PROT_READ | PROT_WRITE,
                                  MAP_PRIVATE, fd, 0);
  records[1].id = 99;

  // Sync the mapping back out to the file
  msync(records, size, MS_SYNC);

  close(fd);
}
