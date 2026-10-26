// Struct definition 
typedef struct {
    char *command;
    char *args[MAX_ARGS];  /* exec expects the command at args[0]. */
    pid_t pid;
    int return_value;
} Program;
