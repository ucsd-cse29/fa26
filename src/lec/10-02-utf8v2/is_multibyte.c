#include <stdio.h>

int is_char_multibyte(char c) {
  if ((c & 0b10000000) > 0)
    return 1;
  return 0;
}

int main(void)
{
    char crab[] = "🦀"; 
    char ascii[] = "abcdefieatih"; 

    printf("Is %s multibyte? %d\n", crab,
        is_char_multibyte(crab[0]));
    printf("Is %s multibyte? %d\n", ascii,
        is_char_multibyte(ascii[0]));

    return 0;
}
