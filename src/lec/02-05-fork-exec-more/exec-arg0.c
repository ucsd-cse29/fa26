#include <unistd.h>
#include <stdio.h>

int main() {
  char* args[] = { "alpaca", NULL };
  execvp("./arg0", args);
                          // When this line runs, the WHOLE 
                          // PROGRAM is replaced by the arg0
                          // program. Nothing else in this
                          // file runs
  printf("Done executing\n");
}