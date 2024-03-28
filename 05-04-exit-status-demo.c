// Exit status demo
// Can call `kill <pid>` to simulate a signal

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
  int status;

  if (fork())
  {
    // Parent
    printf("Parent waiting for child...\n");
    wait(&status);

    if (WIFEXITED(status))
      printf("Child ended normally, exit status = %d\n", WEXITSTATUS(status));
    if (WIFSIGNALED(status)) // `true` if child terminated by signal
      printf("Child terminated by signal %d\n", WTERMSIG(status)); // The signal number
  }
  else
  {
    // Child
    printf("Child running -- PID is %d\n", getpid());
    // *(int *)0 = 42; // Simulate a signal (11 [sigsegv])
    sleep(5);
    exit(3);
  }
}
