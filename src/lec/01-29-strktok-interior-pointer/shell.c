#include <stdio.h>
#include <string.h>

// In order to run this:
// - fork
// - exec

int parse_args(char* input, char** args) {
  char* current = strtok(input, " ");
  int current_index = 0;
  while(current != NULL) {
    args[current_index] = current;
    current = strtok(NULL, " ");
    current_index += 1;
  }
  return current_index;
}

int main() {
  while(1) {
    printf("⇒ ");
    char input[2048];
    fgets(input, 2048, stdin);
    printf("Now computer run this: %s\n", input);

    char* args[1000];
    int argc = parse_args(input, args);
    for(int i = 0; i < argc; i += 1) {
      printf("args[%d]: %s\n", i, args[i]);
    }
  }
}
