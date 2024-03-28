#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

// A minimal shell
int main()
{
  char line[100];

  // Main command loop
  while (printf("> "), gets(line) != NULL)
  {
    if (fork() == 0)
    {
      // Child
      execlp(line, line, (char *)0); // Don't need to cast

      // Don't come here unless `execlp` fails
      printf("%s: Not found\n", line);
      exit(1);
    }
    else
      wait(0);
  }
}
