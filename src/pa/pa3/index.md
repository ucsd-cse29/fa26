# PA3 - The Pioneer Shell: Due Thursday, February 12th at 11:59pm - [Github Classroom Link](https://classroom.github.com/a/cpys2JKd)

Looking for resubmission? [Click here](https://ucsd-cse29.github.io/wi26/pa/pa3/resubmission/index.html)

This assignment is from [CSE29
SP24](https://cse29sp24.github.io/docs/pas/pa6.html#acknowledgements), which has
its own list of acknowledgments!

## Learning Goals

This assignment calls upon many of the concepts that you have practiced in previous PAs. Specifically, we will practice the following concepts in C:

- string manipulation using library functions,
- command line arguments,
- process management using fork(), exec(), and wait(), and of course,
- using the terminal and vim.

We'll also get practice with a new set of library functions for opening, reading from, and writing to files.

## Introduction

Throughout this quarter, you have been interacting with the ieng6 server via the terminal – you've used `vim` to write code, used `gcc` and `make` to compile, used `git` to commit and push your changes, etc. At the heart of all this lies the shell, which acts as the user interface for the operating system.

At its core, the shell is a program that reads and parses user input, and runs built-in commands (such as `cd`) or executable programs (such as `ls`, `gcc`, `make`, or `vim`).

As a way to wrap up this quarter, you will now create your own shell (a massively simplified one of course). We shall call it– (drumroll please)

### The Pioneer Shell

The **PIoneer SHell**, or as we endearingly call it, `pish` (a name with such elegance as other popular programs in the UNIX world, e.g., `git`).

## Getting Started

The starter code for this assignment is hosted on GitHub classroom. Use the following link to accept the GitHub Classroom assignment:

Github Classroom: [https://classroom.github.com/a/cpys2JKd](https://classroom.github.com/a/cpys2JKd)

## Overall Task

### Interactive Mode

Your basic shell simply runs on an infinite loop; it repeatedly:

- prints out a prompt,
- reads keyboard input from the user
- parses the input into a command and argument list
- if the input is a built-in shell command, then executes the command directly
- otherwise, creates a child process to run the program specified in the input command, and waits for that process to finish

This mode of operation is called the **interactive mode**.

### Batch Mode

Shell programs (like `bash`, which is what you have been using on ieng6) also support a batch execution mode, i.e., scripts. In this mode, instead of printing out a prompt and waiting for user input, the shell reads from a script file and executes the commands from that file one line at a time.

In both modes, once the shell hits the end-of-file marker (EOF), it should call `exit(EXIT_SUCCESS)` to exit gracefully. In the interactive mode, this can be done by pressing Ctrl-D.

## Parsing Input

Every time the shell reads a line of input (be it from stdin or from a file), it breaks it down into our familiar `argv` array.

For instance, if the user enters `"ls -a -l\n"` (notice the newline character), the shell should break it down into `argv[0] = "ls"`, `argv[1] = "-a"`, and `argv[2] = "-l"`. In the starter code, we provide a struct to hold the parsed command.

### Handling Whitespaces

You should make sure your code is robust enough to handle various sorts of whitespace characters. In this PA, we expect your shell to handle any arbitrary number of spaces ( ) and tabs (\t) between arguments.

For example, your shell should be able to handle the following input: `" \tls\t\t-a -l "`, and still run the ls program with the correct `argv` array.

`strtok` will be **VERY** helpful for this.

## Built-In Commands

Whenever your shell executes a command, it should check whether the command is a built-in command or not. Specifically, the first whitespace-separated value in the user input string is the command. For example, if the user enters `ls -a -l tests/`, we break it down into `argv[0] = "ls"`, `argv[1] = "-a"`, `argv[2] = "-l"`, and `argv[3] = "tests/"`, and the command we are checking for is `argv[0]`, which is `"ls"`.

If the command is one of the following built-in commands, your shell should invoke your implementation of that built-in command.

There are three built-in commands to implement for this project: `exit`, `cd`, and `history`.

### Built-in Command: `exit`

When the user types `exit`, your shell should call the exit system call with `EXIT_SUCCESS` (macro for 0). This command does not take arguments. If any is provided, the shell raises a usage error.

### Built-in Command: `cd`

`cd` should be run with precisely 1 argument, which is the path to change to. You should use the `chdir()` system call with the argument supplied by the user. If `chdir()` fails (refer to man page to see how to detect failure), you should use call `perror("cd")` to print an error message.

### Built-in Command: `history`

When the user enters the `history` command, the shell should print out the list of commands a user has ever entered in interactive mode.

(If you are on ieng6, open the `~/.bash_history` file to take a look at all the commands you have executed. How far you've come this quarter!)

To do this, we will need to write the execution history to a file for persistent storage. Just like bash, we designate a hidden file in the user's home directory to store the command history.

Our history file will be stored at `~/.pish_history`. (You will find a function in the starter code that will help you get this file path.)

**Important:** When adding a command to history, if the user enters an empty command (0 length or whitespace-only), it should not be added to the history.

When the user types in the `history` command to our shell, it should print out all the contents of our history file, adding a counter to each line:

```bash
▶ history
1 history
▶ pwd
/home/jpolitz/cse29wi26/pa3/Simple-Shell
▶ ls
Makefile  script.sh  pish  pish.c  pish.h  pish_history.c
pish_history.o  pish.o
▶ history
1 history
2 pwd
3 ls
4 history
```

Note that the number before each line is added by `history`. The contents of `.pish_history` should not contain the leading numbers.

## Running Programs

If, instead, the command is not one of the aforementioned built-in commands, the shell treats it as a program, and spawns a child process to run and manage the program using the `fork()` and `exec()` family of system calls, along with `wait()`.

## Excluded Features

Now because our shells are quite simple, there are a lot of things that you may be accustomed to using that will not be present in our shell. (Just so you are aware how much work the authors of the bash shell put into their product!)

You will not be able to:

- use the arrow keys to navigate your command history,
- use Tab to autocomplete commands,
- use the tilde character (~) to represent your home directory,
- use redirection (> and <),
- pipe between commands (|),
- and many more…

Don't be concerned when these things don't work in your shell implementation!

If this were an upper-division C course, we would also ask you to implement redirection and piping.

## Handling Errors

Because the shell is quite a complex program, we expect you to handle many different errors and print appropriate error messages. To make this simple, we now introduce:

### Usage Errors

This only applies to built-in commands. When the user invokes one of the shell's built-in commands, we need to check if they are doing it correctly.

- For `cd`, we expect `argc == 2`,
- For `history` and `exit`, we expect `argc == 1`.

If the user enters an incorrect command, e.g. `exit 1` or `cd` without a path, then you should call the `usage_error()` function in the starter code, and continue to the next iteration of the loop.

### Errors to handle

You need to handle errors from the following system calls/library functions using `perror()`. Please pay attention to the string we give to `perror()` in each case and reproduce it in your code exactly.

- `fopen()` failure: `perror("open")`,
- `chdir()` failure: `perror("cd")`,
- `execvp()` failure: `perror("pish")`,
- `fork()` failure: `perror("fork")`

## The Code Base

You are given the following files:

- **pish.h**: Defines `struct pish_arg` for handling command parsing; declares functions handling the history feature.
- **pish.c**: Implements the shell, including parsing, some built-in commands, and running programs.
- **pish_history.c**: Implements the history feature.
- **Makefile**: Builds the project.
- **ref-pish**: A reference implementation of the shell. Note that in this version, the history is written to `~/.ref_pish_history` rather than `~/.pish_history`, to avoid conflict with your own shell program.

### struct pish_arg

In pish.h, you will find the definition of `struct pish_arg`:

```c
#define MAX_ARGC 64

struct pish_arg {
    int argc;
    char *argv[MAX_ARGC];
};
```

In our starter code, all functions handling a command (after it has been parsed) will be given a `struct pish_arg` argument.

## Running pish

First, run `make` to compile everything. You should see the `pish` executable in your assignment directory.

To run pish in interactive mode (accepting keyboard input), type

```bash
$ ./pish
```

Or, to run a script (e.g., script.sh), type

```bash
$ ./pish script.sh
```

The same applies for the reference implementation `ref-pish`.

## Design Questions

On `ieng6` , start your shell, and from your shell, run vim . Then, in another terminal logged into the same ieng6 machine (e.g. ieng6-201, ieng6-202, ieng6-203), run `ps -u` . Copy-paste the output, and answer:

- Which listed process is your shell?
- Which listed process is the `bash` shell that you started your shell from?
- Which listed process is the `vim` process that started from your shell?
- Run `ps -au` . Copy-paste the output. Make a few guesses about what you think is happening with these other processes.

## What to Hand In

- Submit your code to Gradescope
- CREDITS.txt is required (more details on the [syllabus](https://ucsd-cse29.github.io/wi26/#assignments-and-academic-integrity))
- We will run your program with `make` and `./pish` in both interactive and batch mode
- Submit a **PDF** with your Design Question Answers on Gradescope

## Resources and Policy

Refer to [the policies on assignments](https://ucsd-cse29.github.io/wi26/#assignments-and-academic-integrity) for working with others or appropriate use of tools like ChatGPT or Github Copilot.

You can use any code from class, lab, or discussion in your work.
