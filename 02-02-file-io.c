#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BSIZE 16384

int main() {
  int fin, fout;
  char buf[BSIZE];
  int count;

  if ((fin = open("01-03-foo", O_RDONLY)) < 0) {
    perror("foo");
    exit(1);
  }

  if ((fout = open("02-02-bar", O_WRONLY | O_CREAT, 0644)) < 0) {
    perror("bar");
    exit(2);
  }

  while ((count = read(fin, buf, BSIZE)) > 0)
    write(fout, buf, count);

  close(fin);
  close(fout);
}
