#include <unistd.h>
#include <stdio.h>


int main() {
  int a = 100;
  printf("%d %p\n", a, &a);
  int pid = fork();
  if(pid == 0) { a = 999; }
  while(1) {
    printf("[%d]: %d %p\n", pid, a, &a);
  }
// Virtual Memory

  // What will this print?

  // 100 0xfff71234

  // A
  // 999 0xfff71234
  // 999 0xfff71234

  // B
  // 999 0xfff71234
  // 999 0xfff71900


}
