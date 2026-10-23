#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

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
    if(input[strlen(input) - 1] == '\n') {
      input[strlen(input) - 1] = 0;
    }
    printf("Now computer run this: %s\n", input);

    char* args[1000];
    int argc = parse_args(input, args);
    args[argc] = NULL; // execvp expects a NULL
                       // at the end of the arg list

    int pid = fork();
    if(pid == 0) {
      execvp(args[0], args);
    }
    else { // Can we print the exit code of the child?
      int status;
      wait(&status);
      printf("status: %d %b\n", status, status);
      int actual_status = WEXITSTATUS(status);
      printf("return code: %d\n", actual_status);
    }
  }
}

