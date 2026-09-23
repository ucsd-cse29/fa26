#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main() {
  int value = 17;
  int pid = fork();
  if(pid == 0) {
    printf("In child before assignment: %p => %d\n", &value, value);
    value = 999;
    while(1) {
      printf("In child:\t%p => %d\n", &value, value);
    }
  }
  else {
    printf("In parent before assignment: %p => %d\n", &value, value);
    value = 3333;
    while(1) {
      printf("In parent:\t%p => %d\n", &value, value);
    }
  }
}

