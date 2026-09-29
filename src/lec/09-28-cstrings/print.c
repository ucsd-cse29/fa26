#include <stdio.h>

int main() {
  char n = 72;
  char neg = -27;
  char a[] = "Hello World";

  printf("%s\n", a); // String
                     
  printf("Different ways of printing a positive char\n");
  printf("%d\n", n); // Signed int
  printf("%u\n", n); // Unsigned int
  printf("%c\n", n); // Character
  
  printf("Different ways of printing a negative char\n");
  printf("%d\n", neg); // Signed int
  printf("%u\n", neg); // Unsigned int
  printf("%c\n", neg); // Character

  return 0;
}
