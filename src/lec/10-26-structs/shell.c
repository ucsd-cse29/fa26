#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

// In order to run this:
// - fork
// - exec

struct Command {
  char name[64];
  char* args[64];
  int numargs;
  pid_t pid;
  int ret;
};

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

  struct Command cmds[100];
  int cmds_len = 0;

  while(1) {
    printf("CSE29> ");
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

    strcpy(cmds[cmds_len].name, args[0]);

    int pid = fork();
    cmds[cmds_len].pid = pid;
    
    cmds_len++;

    // This code is run in the child
    if(pid == 0) {
      execvp(args[0], args);
      // Do I ever run more code after this?
    }
    // This code is run in the parent
    else { // Can we print the exit code of the child?
      int status;
      wait(&status);
      printf("status: %d %b\n", status, status);
      int actual_status = WEXITSTATUS(status);
      printf("return code: %d\n", actual_status);
    }

    printf("======Commands run\n");
    for (int i = 0; i < cmds_len; i++) {
      printf("   Name: %s\n", cmds[i].name);
      printf("   Pid: %d\n", cmds[i].pid);
    }

  }

  return 0;
}

