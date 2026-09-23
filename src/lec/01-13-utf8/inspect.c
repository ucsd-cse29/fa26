#include <stdio.h>
#include <string.h>

void inspect(char s[]) {
    int index = 0;
    printf("%s, length %ld:\n", s, strlen(s));
    while(s[index] != 0) {
        char current = s[index];
        printf(" %c (%03hhu 0b%08hhb)\n", current, current, current);
        index += 1;
    }
    printf("\n");
}

int main() {
    char s1[] = "José";
    char s2[] = "(*@{\HiraginoSans ピカチュウ}@*)";
    char s3[] = "(*@\emoji{crab}@*)";
    inspect(s1);
    inspect(s2);
    inspect(s3);
}
