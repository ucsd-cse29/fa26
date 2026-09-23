#include <stdio.h>

void uppercase(char str[]) {
  for(int i = 0; str[i] != '\0'; i += 1) {
    if(str[i] >= 'a' && str[i] <= 'z') {
      str[i] = str[i] - 32;    
    }
  }
}

void inspect(char str[]) {
    for (int i = 0; str[i] != '\0'; i++) {
        char c = str[i];
        printf("(%c %d) ", c, c);
    }
    printf("\n");
}

int main() {
    char message[] = "Hello!";
    printf("%s\n", message);
    printf("(%c %d) (%c %d) (%c %d) (%c %d) (%c %d) (%c %d) (%c %d)\n",
           message[0], message[0],
           message[1], message[1],
           message[2], message[2],
           message[3], message[3],
           message[4], message[4],
           message[5], message[5],
           message[6], message[6]);
    inspect(message);

    // After this call, message should contain "HELLO!"
    uppercase(message);
    inspect(message);
    printf("After uppercase: %s\n", message);
    inspect(message);
}








