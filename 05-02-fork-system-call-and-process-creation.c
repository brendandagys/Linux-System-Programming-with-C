/* Output may look like:

I am the parent
I am the child

OR

I am the child
I am the parent

...we can't be sure of the order of parent/child. */

#include <stdio.h>
#include <unistd.h>

int main()
{
  if (fork())
    printf("I am the parent\n");
  else
    printf("I am the child\n");
}
