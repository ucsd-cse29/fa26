#include <stdio.h>

int is_char_multibyte(char c) {
  // TODO
  return 0;
}

int main(void)
{
    char crab[] = "🦀"; 

    printf("Is %s multibyte? %d\n", crab, is_char_multibyte(crab[0]));
    return 0;
}
