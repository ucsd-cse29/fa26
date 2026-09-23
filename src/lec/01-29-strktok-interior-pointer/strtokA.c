#include <stdio.h>
#include <string.h>

// using strtok

int main() {
  char str[] = "Joe Politz,jpolitz@ucsd.edu,Instructor";
  printf("str@%p: %p \"%s\"\n", &str, str, str);

  char* a = strtok(str, ",");
  char* b = strtok(NULL, ",");
  char* c = strtok(NULL, ",");
  char* d = strtok(NULL, ",");


  printf("a@%p: %p, \"%s\"\n", &a, a, a);
  printf("b@%p: %p, \"%s\"\n", &b, b, b);
  printf("c@%p: %p, \"%s\"\n", &c, c, c);
  printf("d@%p: %p, \"%s\"\n", &d, d, d);
}

