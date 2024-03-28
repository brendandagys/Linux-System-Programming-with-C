/* Equivalent to "ls | sort -r" */

#include <unistd.h>

int main() {
  int p[2]; // p[0] is downstream, p[1] is upstream

  pipe(p); // Create the pipe

  if (fork() == 0) {
    // Child: connect `stdout` (1) to pipe's upstream end
    dup2(p[1], 1);
    close(p[0]);
    execlp("ls", "ls", (char *)0);
  }

  // Parent: connect `stdin` (0) to pipe's downstream end
  dup2(p[0], 0);
  close(p[1]);
  execlp("sort", "sort", "-r", (char *)0);
}
