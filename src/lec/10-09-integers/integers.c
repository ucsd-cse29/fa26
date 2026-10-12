#include <stdio.h>
#include <stdint.h>

int main() {
  // Single byte integers
  char c = 1;
  int8_t ci = 1;

  // Multi-byte integers
  short s = 0x0FFF;
  int16_t si = 2;

  // Funky thing 1: truncating 
  //c = s;
  

  uint32_t codepoint = ((uint32_t)c << 10) | (uint32_t)c;


  printf("s: %d c: %d\n", s, c); // -1

  return 0;
}
