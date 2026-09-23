#include <unistd.h>
#include <stdio.h>

int main() {
  char* args[] = {"alpaca", NULL};
  execvp("./nonsense", args);
                          // When this line runs, execvp
                          // FAILS to run ./nonsense
                          // and RETURNS, continuing
                          // to line 11 to print
  printf("Done executing\n");
}


