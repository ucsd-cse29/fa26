#include <stdio.h>
#include <string.h>

void inspect(char str[]) {
    for (int i = 0; str[i] != '\0'; i++) {
        char c = str[i];
        printf("(%c %d) ", c, c);
    }
    printf("\n");
}

int main() {
    char jose[] = "José";
    char crab[] = "🦀";
    char china[] = "中";

    printf("Jose: %s\n", jose);
    inspect(jose);
}
