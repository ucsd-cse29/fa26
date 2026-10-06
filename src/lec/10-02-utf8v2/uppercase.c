#include <stdio.h>

int main(void)
{
    char uppercase = 'A';
    char lowercase = uppercase | 0x20;

    printf("uppercase: %c\nlowercase: %c\n",
        uppercase, lowercase);
    return 0;
}
