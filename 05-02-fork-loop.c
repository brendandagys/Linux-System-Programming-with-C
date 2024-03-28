/*Parent and child output will be interleaved in a non-deterministic way.
Occassionally, you may see child output appearing after the prompt.
This is expected behavior.*/

#include <stdio.h>
#include <unistd.h>

int main()
{
  int i;

  if (fork())
  {
    for (i = 0; i < 100000; i++)
      printf("**     PARENT %d\n", i);
  }
  else
  {
    for (i = 0; i < 100000; i++)
      printf("  **   CHILD %d\n", i);
  }
}
