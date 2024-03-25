#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  char *buffer;
  int size, count;
  FILE *fd;

  if (argc != 3) {
    printf("Usage: %s blocksize blockcount\n", argv[0]);
    exit(1);
  }

  fd = fopen("02-05-bufio.out", "w");

  size = atoi(argv[1]);
  count = atoi(argv[2]);

  buffer = malloc(size);

  for (int i = 0; i < count; i++) {
    fwrite(buffer, size, 1, fd);
  }

  free(buffer);
  fclose(fd);
}
