#include <stdio.h>

void uppercase_ascii(char s[]) {
  for(int i = 0; s[i] != '\0'; i += 1) {
    if(s[i] >= 'a' && s[i] <= 'z') { s[i] -= 32; }
  }
}

// c: [Hi class] c2: [It's joe\0]
// Hi classIt's joe\0
// ^       ^
// c       c2
int main() {
  char c[8] = { 'H', 'i', ' ', 'c', 'l', 'a', 's', 's' };
  int x = 90;
  char c2[] = { 'I', 't', ' ', 'm', 'e' };
  uppercase_ascii(c);
  c2[6] = 'Z';
  printf("%s\n", c);
  printf("%s\n", c2);
}
