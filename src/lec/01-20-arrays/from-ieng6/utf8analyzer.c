#include <string.h>
#include <stdio.h>
#include <stdint.h>




void uppercase_ascii(char s[]) {
  for(int i = 0; s[i] != '\0'; i += 1) {
    if(s[i] >= 'a' && s[i] <= 'z') { s[i] -= 32; }
  }
}





void truncate_to_n_bytes(char s[], uint32_t howmany) {
  s[howmany] = '\0'; 
}

int main() {
  char input[100];
  fgets(input, 100, stdin);
  printf("The input was: %s\n", input);
  truncate_to_n_bytes(input, 6);
  printf("First 6 bytes of input: %s\n", input);
  uppercase_ascii(input);
  printf("Input with ASCII uppercased: %s\n", input);
}


