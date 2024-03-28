#include <stdio.h>
#include <unistd.h>

int main()
{
  static char *cmd[] = {"ps", "ls", "date", "goof"};
  int i;

  printf("0=ps, 1=ls, 2=date, 3=goof : ");
  scanf("%d", &i);

  execlp(cmd[i], cmd[i], NULL);

  printf("Command not found\n");
}
