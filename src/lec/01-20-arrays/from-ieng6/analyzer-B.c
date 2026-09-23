#include <string.h>
#include <stdio.h>
#include <stdint.h>

// There's no way to return an array in C
// (well, sort of we will see a way but it introduces
// more problems. The out parameter thing is the way
// to go most of the time, and is what C libraries do!)

void uppercase_ascii(char s[]) {
  for(int i = 0; s[i] != '\0'; i += 1) {
    if(s[i] >= 'a' && s[i] <= 'z') { s[i] -= 32; }
  }
}

// "result" parameter, "out" parameter
void truncate_to_n(char s[], uint32_t n, char result[]) {
  for(int i = 0; i < n; i += 1) {
    result[i] = s[i];
  }
  result[n] = '\0';
}

int main() {
  char input[100];
  fgets(input, 100, stdin);
  printf("The input was: %s\n", input);
  char truncated[7];
  truncate_to_n(input, 6, truncated);
  printf("First 6 bytes of input: %s\n", truncated);
  uppercase_ascii(input);
  printf("Input with ASCII uppercased: %s\n", input);
}

