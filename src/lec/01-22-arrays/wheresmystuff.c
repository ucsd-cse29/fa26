#include <stdio.h>
#include <stdint.h>

void wheresmystuff(char* s) {
  int x = 12;
  uint8_t y = 53;
  char z = 9;
  double ns[] = { 4.0, 3.0, 9.0 };

  printf("x=%d, %lu bytes, starts at: %p\n", x, sizeof(x), &x);
  printf("y=%hhu, %lu bytes, starts at: %p\n", y, sizeof(y), &y);
  printf("z=%hhd, %lu bytes, starts at: %p\n", z, sizeof(z), &z);
  printf("ns=[%f,%f,%f], %lu bytes, starts at: %p\n",
         ns[0], ns[1], ns[2], sizeof(ns), &ns);

  printf("s=\"%s\"@%p, %lu bytes, starts at: %p\n", s, s, sizeof(s), &s);
}

int main() {
  char str[] = "14 char string";
  wheresmystuff(str);
  printf("\nstr takes up %lu bytes starting at: %p\n", sizeof(str), &str);
}

