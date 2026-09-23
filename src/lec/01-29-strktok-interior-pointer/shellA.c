#include <stdio.h>
#include <string.h>


// In readings:
// - fork
// - exec


// Split up input on spaces, store in args
// Return how many args we saw
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
    char* args[1000];
    int count = parse_args(input, args);
    for(int i = 0; i < count; i += 1) {
      printf("args[%d]: %s\n", i, args[i]);
    }
    printf("Here's where we would run %s\n", input);
  }
}
