// Command line argument processing using `getopt()`
// Usage example: argdemo -a -b -n 700 -t blue

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int c;
  int aflag = 0;
  int bflag = 0;
  int numoption = 0;
  char txtoption[200] = "default";

  opterr = 0; // Delete this to see `getopt()`s own error messages

  while ((c = getopt(argc, argv, "abn:t:")) != EOF) {
    switch (c) {
    case 'a':
      aflag = 1;
      break;
    case 'b':
      bflag = 1;
      break;
    case 'n':
      numoption = atoi(optarg);
      break;
    case 't':
      strcpy(txtoption, optarg);
      break;
    case '?':
      fprintf(stderr, "Invalid option: -%c\n", optopt);
    }
  }

  if (aflag)
    printf("Option a is set\n");
  if (bflag)
    printf("Option b is set\n");
  printf("Numeric option value is %d\n", numoption);
  printf("Text    option value is %s\n", txtoption);

  // Finished with the options. `argv` has been re-ordered so non-option
  // arguments are at the end

  argv += optind; // Adjust to move past the options
  argc -= optind;

  while (argc--) {
    printf("Arg: %s\n", *argv++);
  }
}
