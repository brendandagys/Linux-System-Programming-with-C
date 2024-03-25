#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  char *buffer;
  int fd, size, count;

  if (argc != 3) {
    printf("Usage: %s blocksize blockcount\n", argv[0]);
    exit(1);
  }

  fd = open("02-05-rawio.out", O_WRONLY | O_CREAT | O_TRUNC, 0600);

  size = atoi(argv[1]);
  count = atoi(argv[2]);

  buffer = malloc(size);

  for (int i = 0; i < count; i++) {
    write(fd, buffer, size);
  }

  free(buffer);
  close(fd);
}
