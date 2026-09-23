#include <stdio.h>
#include <unistd.h>

int main() {
  int pid1 = fork();
  int pid2 = fork();
  printf("The pids are: %d %d\n", pid1, pid2);
}

