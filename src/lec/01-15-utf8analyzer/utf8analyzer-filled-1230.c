#include <string.h>
#include <stdio.h>
#include <stdint.h>

int8_t is_ascii(char s[]) {
  for(int i = 0; s[i] != '\0'; i += 1) {
    if((s[i] & 0b10000000) == 0b10000000) {
      return 0; // This 0 means "false"
    }
  }
  return 1;
}

int8_t width_from_start_byte(char c) {
  if((c & 0b10000000) == 0b00000000) { return 1; } // ASCII = 1 byte
  if((c & 0b11100000) == 0b11000000) { return 2; } // 2 byte case
  if((c & 0b11110000) == 0b11100000) { return 3; } // 3 byte case
  if((c & 0b11111000) == 0b11110000) { return 4; } // 3 byte case
  // if((c & 0xF8) == 0xF0)   thanks robot 🤖
  return -1;
}


// Count the number of _code points_ in the string
int32_t utf8_len(char s[]) {
  int byte_index = 0, cp_count = 0;
  while(s[byte_index] != '\0') {
    int width = width_from_start_byte(s[byte_index]);
    printf("byte_index: %03d; byte: %08hhb; cp_count: %d\n", byte_index, s[byte_index], cp_count);
    cp_count += 1;
    byte_index += width;
  }
  return cp_count;
}

int main() {
  char input[100];
  fgets(input, 100, stdin);
  printf("The input was: %s\n", input);
  printf("The strlen  of input is: %ld\n", strlen(input));
  printf("The utf8len of input is: %d\n", utf8_len(input));
  printf("Is ASCII? %d\n", is_ascii(input));
  printf("Width based on byte 0: %d\n", width_from_start_byte(input[0]));
}
