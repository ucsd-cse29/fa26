# PA3 - The Sea(C) Shell: Resubmission Due 11/20 at 10pm

### If you want to resubmit PA3, please read this section carefully. You need to pass all the tests in the original PA3, while also implementing an extra functionality

Implement `seash` as originally described. Also update `seash` to support a new built-in command `$?` that prints the exit status of the last command executed. This should work for built-in commands, non-built-in commands, and commands run in the background with `&`. For example:

```bash
you@🐚 /home/you/cse29/pa3$ ls
seash  seash.c
you@🐚 /home/you/cse29/pa3$ $?
0
you@🐚 /home/you/cse29/pa3$ echo hello
hello
you@🐚 /home/you/cse29/pa3$ $?
0
you@🐚 /home/you/cse29/pa3$ ls nonexistent
ls: cannot access 'nonexistent': No such file or directory
you@🐚 /home/you/cse29/pa3$ $?
2
you@🐚 /home/you/cse29/pa3$ $?
2
you@🐚 /home/you/cse29/pa3$ cd nonexistent
cd: No such file or directory
you@🐚 /home/you/cse29/pa3$ $?
1
```

The `$?` command should also be recorded in the command history. It should **not** affect what the last exit code was (this includes `$? <anything>`, which is a usage error; see below).

`$?` will only be tested in interactive mode.

For built-in commands, you have to set the exit status yourself: 0 if the command succeeds, and 1 if it fails (including usage errors). If in doubt, follow Linux conventions.

## Errors

For each of the following errors, call the `usage_error()` function in the starter code and continue to the next iteration of the loop.

- If the user enters `$?` as the very first command (there is no previous exit code).
- If the user enters `$? <anything>` (if argc != 1).

### Hints

You may find the `WEXITSTATUS` macro useful.

## Design Question Resubmission

If you want to resubmit the design questions, the new Gradescope assignment also includes this new design question:

We've implemented support for background processes, with the last argument being &. How would you extend your implementation to add the `jobs` command to list running background jobs and the `fg <pid>` command to wait for a specific job to finish?

## What to Hand In

- Submit your updated code to Gradescope
- CREDITS.txt is required (more details on the [syllabus](https://cse29.site/#assignments-and-academic-integrity))
- We will run your program with `gcc seash.c -o seash` and `./seash` in both interactive and batch mode

If you are resubmitting the design questions, answer **ALL** of the design questions in the new Gradescope assignment: the original PA3 questions (even the ones you got correct in your previous submission) and the `jobs`/`fg` question above.

## Resources and Policy

Refer to [the policies on assignments](https://cse29.site/#assignments-and-academic-integrity) for working with others or appropriate use of tools like ChatGPT or Github Copilot.

You can use any code from class, lab, or discussion in your work. You must write your own answers to the design questions.
