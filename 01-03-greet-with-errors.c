#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  // Simulate this failing by running `chmod 400 01-03-foo`
  int fd = open("01-03-foo", O_WRONLY | O_CREAT, 0644);

  if (fd < 0) {
    printf("Error number %d\n", errno);
    perror("foo");
    exit(1);
  }

  write(fd, "hello world", 11);
  close(fd);
}
