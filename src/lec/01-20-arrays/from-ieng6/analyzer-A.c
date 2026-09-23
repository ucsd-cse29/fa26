#include <string.h>
#include <stdio.h>
#include <stdint.h>

// Q: Why not just compute + return a new string?
// A: You cannot in any useful way return a new array
//   followup Q: Just use pointers? (Whatever that is?)
//            A: Now you have 2 problems


// We could do the same thing to uppercase_ascii!
void uppercase_ascii(char s[]) {
  for(int i = 0; s[i] != '\0'; i += 1) {
    if(s[i] >= 'a' && s[i] <= 'z') { s[i] -= 32; }
  }
}


// Takes a C string s, a desired length, and a result C string
// and copies the first n characters of s to result, and
// adds a null-terminator to result
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
  char truncate_result[7];
  truncate_to_n(input, 6, truncate_result);
  printf("First 6 bytes of input: %s\n", truncate_result);
  uppercase_ascii(input);
  printf("Input with ASCII uppercased: %s\n", input);
}

