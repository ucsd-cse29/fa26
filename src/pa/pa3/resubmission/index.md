# PA3 - The Pioneer Shell: Resubmission Due 2/26 at 11:59pm

### If you want to resubmit PA3, please read this section carefully. You need to pass all the tests in the original PA3, while also implementing an extra functionality

Implement `pish` as originally described. Also update `pish` to support a new built-in command `$?` that prints the exit status of the last command executed. This should work for both built-in and non-built-in commands. For example:

```bash
▶ ls
Makefile  script.sh  pish  pish.c  pish.h  pish_history.c  pish_history.o  pish.o
▶ $?
0
▶ echo hello
hello
▶ $?
0
▶ ls nonexistent
ls: nonexistent: No such file or directory
▶ $?
1
▶ $?
1
▶ cd nonexistent
cd: no such file or directory: nonexistent
▶ $?
1
```

The `$?` command should also be recorded in the command history. It should **not** affect what the last exit code was.

## Errors

For each of the following errors, call the `usage_error()` function in the starter code and continue to the next iteration of the loop.

- If the user enters `$?` as the very first command (there is no previous exit code).
- If the user enters `$? <anything>` (if argc != 1).

### Hints

You may find the `WEXITSTATUS` macro useful.

## Design Question Resubmission

If you want to resubmit the design questions, we will be asking this updated design question in a new Gradescope assignment. Please submit a PDF containing your answer to the following question:

Look up how to run background processes at the shell with & (feel free to use an AI tool to help you see some examples!). Describe a little bit about what might change in your shell if you wanted to allow background processes to run while the shell continues to take input.

## What to Hand In

- Submit your updated code to Gradescope
- CREDITS.txt is required (more details on the [syllabus](https://ucsd-cse29.github.io/wi26/#assignments-and-academic-integrity))
- We will run your program with `make` and `./pish` in both interactive and batch mode

If you are resubmitting the design question, submit a PDF containing your answer to the design question in the new Gradescope assignment.

## Resources and Policy

Refer to [the policies on assignments](https://ucsd-cse29.github.io/wi26/#assignments-and-academic-integrity) for working with others or appropriate use of tools like ChatGPT or Github Copilot.

You can use any code from class, lab, or discussion in your work. You must write your own answers to the design questions.
