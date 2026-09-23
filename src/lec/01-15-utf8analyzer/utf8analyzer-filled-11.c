#include <string.h>
#include <stdio.h>
#include <stdint.h>

int8_t is_ascii(char s[]) {
  for(int i = 0; s[i] != 0; i += 1) {
    if((s[i] & 0b10000000) == 0b10000000) {
      return 0;
    }
  }
  return 1;
}

int8_t width_from_start_byte(char c) {
  if((c & 0b10000000) == 0b00000000) { return 1; }
  if((c & 0b11100000) == 0b11000000) { return 2; }
  if((c & 0b11110000) == 0b11100000) { return 3; }
  if((c & 0b11111000) == 0b11110000) { return 4; }
  return -1;
}

// Count the number of _code points_ in the string
int32_t utf8_len(char s[]) {
  int byte_index = 0, length = 0;
  while(s[byte_index] != '\0') {
    int width = width_from_start_byte(s[byte_index]);
    byte_index += width;
    length += 1;
  }
  return length;
}

int main() {
  char input[100];
  fgets(input, 100, stdin);
  printf("The input was: %s\n", input);
  printf("Is ASCII? %d\n", is_ascii(input));
  printf("Width of start byte: %d\n", width_from_start_byte(input[0]));
  printf("strlen: %ld\n", strlen(input));
  printf("utf8_len: %d\n", utf8_len(input));
}


// José ate yummy 🦀

// J 1
// o 1
// s 1
// é 2
//   1
// ate yummy 10
// 🦀 4
// \n 1
