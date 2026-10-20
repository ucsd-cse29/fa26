# Lab 4: Pipes and filters in UNIX

In this lab, you will get to know the commands `less` and `grep`, and experiment with input and output redirection.

## Lab 4 learning objectives

* Get more comfortable and efficient using the command line
* Use `less` and `grep` to view and search through text files
* Recognize and use pipe and redirection operators

# Icebreaker

**Clone our starter code from [Classroom 50](https://classroom50.org/ucsd-cse29-fall2026/cse29-fa26/assignments/lab-4/accept) into your account on `ieng6`.**


# Icebreaker

If you could choose a superpower to have, what would it be? What would you do with it?
Who’s your favorite superhero/villain, if you have any?

<div class="note">

Please write your names and answers on your whiteboard. No check-off is needed!

</div>


<div class="quality">

Before you get right into more unix commands, we have a quality of life improvement.
Recall that in lab2 you made a pair of ssh keys to allow you to securely access github from your ieng6 account.
There is another pair of keys we can make which give you the power to never have to type your password when signing into ieng6 again.
The tutorial for this resides in the last lab: [here](../week3/index#identify-yourself-to-ieng6).

</div>

# Searching and Filtering Program Output

In this lab, we’ll walk you through some helpful UNIX commands that are commonly used to save and filter program output.
There are multiple ways to achieve the same result, and we’ll demonstrate advantages and disadvantages of each.

In the starter code, you are given a `problem.c` source code file. This program creates a large 2D array, fills it with numbers, and prints them out.
Fortunately, whoever wrote this was thoughtful enough to write code to check for an out-of-bounds error.
Unfortunately, whoever wrote this was not thoughtful enough to debug the program.
Fortunately, you don’t need to debug this program; we’re going to use this program as an example of how the following UNIX commands can be used to parse a lot of program output easily.

Compile and run `problem` to see exactly what "a lot of program output" means.

```
$ gcc -g -o problem problem.c
$ ./problem
```
Every so often there’s an error message, but it’s separated by all the expected program output. For programs with more errors and more output, you could imagine how we wouldn’t want to keep scrolling up the terminal to read. There are multiple ways in which we can filter out everything but the error messages.

## Say Less

In previous Projects, we’ve already used the *indirection* (`<`) and *redirection* (`>`) operators. These are used to feed input into a program, or redirect the output of a program into a file. Let’s first save the output of the program to a text file:

```
$ ./problem > problem.txt
```

Redirection overwrites any content of the destination file with the output. There also exists the append (`>>`) operator, which works similarly to redirection, but appends the output to the end of the destination file instead of overwriting.

```
$ ./problem >> problem.txt
```

You can use `cat` to view the contents of the file, but this is no better than letting the program output directly to the terminal. Instead, we can say `less` to start a program to display a portion of the file and navigate freely through it. It’s like `cat`, but shows less at a time.

```
$ less problem.txt
```

<div class="note">

The `less` command succeeds the `more` command, which does the same thing but does not support backwards navigation. In this sense, `less` is like `more`, but also (as `man less` duly notes) `less` is the opposite of `more`.

</div>

The one subcommand you need to know is to type `h` while in this program to display a list of subcommands. Some especially helpful subcommands include `q` to quit and `f`/`b` to move forward/backward one window. You may also notice that you can use `j` and `k` to move forward or backward by one line, just like in Vim. The subcommand we want to use to filter out all lines that do not have an error is to type "&" followed by the word "error", then press Enter. `less` will insert a slash ("/") in between to indicate that what follows is a pattern to match. This method of filtering is convenient if you don’t want to clutter the terminal interface, but requires that the output exists in a file already.

<div class="checkoff">

Once you have filtered the lines in `problem.txt` such that only the "error" lines remain, as a team, write the error on your whiteboard. Call over a TA/tutor to get checked off.

</div>

## Search with `grep`

The `grep` command is most commonly used to search for lines of a file that match some string. `grep` takes in two arguments: the "pattern" to match, and a file to read from.

```
$ grep error problem.txt
```

This command directly outputs to the terminal, which can be acceptable if you expect the output to be short, and helpful if you don’t want to run the search as a subcommand within another program, as with `less`.

Try practicing filtering file contents with `message.txt`, using either `less` or `grep`. This file contains the output of another command, which created a large array, assigned random capital character values, and printed it out. For some strange reason, the output shows that some characters were written way out of bounds at column index 42, but it’s hard to tell what’s happened when each line is separated by all the other output. Use `less` or `grep` to search for all lines that contain the string "42". Are you [surprised](https://www.youtube.com/watch?v=dQw4w9WgXcQ) by what you find?

# Flow Like Water

## Piping

Both of these methods require you to create a file which contains the output of a file. This is generally pretty easy to do, but can be undesirable if you have a lot of output that you don’t want to be saved into a really large file (or are indecisive about naming files). The solution to circumvent this is to use *pipes*.

~~Within industry, piping is a system of pipes used to convey fluids (liquids and gases) from one location to another.~~ Within UNIX, the pipe operator (`|`) is used to directly feed output from one program as input into another program. We can pipe directly from the `problem` program into either `less` or `grep` to accomplish the same result as running these commands on the `problem.txt` file.

```
$ ./problem | less
$ ./problem | grep error
```

We can compound indirection, redirection, and pipe operators to create helpful commands. Understanding how these operators work in conjunction with each other can be understood as an analogy to actual pipes, rendered below as cool animations.

By default, print statements in programs output directly to the terminal interface. So this command:

```
$ ./problem
```

looks like this:

<div class="flowchart">
    <div class="program">
        ./problem
    </div>
    <div class="flow-to-terminal">
        <div class="text-flow">
            <span>arr[0][0] = 0</span>
            <span>arr[0][1] = 1</span>
            <span>arr[0][2] = 2</span>
            <span>arr[0][3] = 3</span>
            <span>arr[0][4] = 4</span>
            <span>arr[0][5] = 5</span>
        </div>
    </div>
    <div class="terminal">
        Terminal
    </div>
</div>

By using the redirection operator, we install an elbow pipe to redirect the flow of output into a file. The output no longer flows into the terminal.

```
$ ./problem > problem.txt
```

<div class="flowchart">
    <div class="program">
        ./problem
    </div>
    <div class="redirect">
        <div class="text-flow">
            <span>arr[0][0] = 0</span>
            <span>arr[0][1] = 1</span>
            <span>arr[0][2] = 2</span>
            <span>arr[0][3] = 3</span>
            <span>arr[0][4] = 4</span>
            <span>arr[0][5] = 5</span>
        </div>
    </div>
    <div class="file">
        <div class="text">problem.txt</div>
        <div class="folded-corner"></div>
    </div>
    <div class="terminal" style="margin-left: 2rem">
        Terminal
    </div>
</div>

By using the pipe operator, we install a coupling between the output and input of two programs. Without any other pipes at the end, the
output of the second program flow into the terminal.

```
$ ./problem | grep error
```

<div class="flowchart">
    <div class="program">
        ./problem
    </div>
    <div class="pipe">
        <div class="text-flow">
            <span>arr[0][0] = 0</span>
            <span>arr[0][1] = 1</span>
            <span>arr[0][2] = 2</span>
            <span>arr[0][3] = 3</span>
            <span>arr[0][4] = 4</span>
            <span>arr[0][5] = 5</span>
        </div>
    </div>
    <div class="program">
        <div class="text">grep error</div>
    </div>
    <div class="flow-to-terminal">
        <div class="text-flow">
            <span>error: arr[0][50] out of bounds</span>
            <span>error: arr[1][50] out of bounds</span>
            <span>error: arr[2][50] out of bounds</span>
        </div>
    </div>
    <div class="terminal">
        Terminal
    </div>
</div>

By using both piping and redirection, we can chain multiple commands and file writing actions. In this command, we run the `problem` program, filter its output with `grep`, and output the filtered lines into a file. This file now contains the error messages from `problem`, and can serve as an error log. Does this output to the terminal as well?

```
$ ./problem | grep error > errors.txt
```

<div class="flowchart">
    <div class="program">
        ./problem
    </div>
    <div class="pipe">
        <div class="text-flow">
            <span>arr[0][0] = 0</span>
            <span>arr[0][1] = 1</span>
            <span>arr[0][2] = 2</span>
            <span>arr[0][3] = 3</span>
            <span>arr[0][4] = 4</span>
            <span>arr[0][5] = 5</span>
        </div>
    </div>
    <div class="program">
        <div class="text">grep error</div>
    </div>
    <div class="redirect">
        <div class="text-flow">
            <span>error: arr[0][50] out of bounds</span>
            <span>error: arr[1][50] out of bounds</span>
            <span>error: arr[2][50] out of bounds</span>
        </div>
    </div>
    <div class="file">
        <div class="text">errors.txt</div>
        <div class="folded-corner"></div>
    </div>
    <div class="terminal" style="margin-left: 30px">
        Terminal
    </div>
</div>

## Having some `tee` and drinking it, too

Redirection lets us write to a file. Not having redirection lets us directly see the output in the terminal. Why don’t we have both?

By using the `tee` command, we can simultaneously write output to a file and and continue flowing data rightward, usually to the terminal. `tee` is a command, not an operator like redirection and piping, so we must pipe into `tee` first. `tee` takes a filename as an argument, which it outputs to.

```
$ ./problem | tee problem.txt
```

<div class="flowchart">
    <div class="program">
        ./problem
    </div>
    <div class="pipe">
        <div class="text-flow">
            <span>arr[0][0] = 0</span>
            <span>arr[0][1] = 1</span>
            <span>arr[0][2] = 2</span>
            <span>arr[0][3] = 3</span>
            <span>arr[0][4] = 4</span>
            <span>arr[0][5] = 5</span>
        </div>
    </div>
    <div>
        <div class="program" style="height: 140px">
            <div class="text">tee problem.txt</div>
        </div>
    </div>
    <div>
        <div class="flowchart" style="margin-bottom: 5px">
            <div class="write">
                <div class="text-flow">
                    <span>arr[0][0] = 0</span>
                    <span>arr[0][1] = 1</span>
                    <span>arr[0][2] = 2</span>
                    <span>arr[0][3] = 3</span>
                    <span>arr[0][4] = 4</span>
                    <span>arr[0][5] = 5</span>
                </div>
            </div>
            <div class="file">
                <div class="text">problem.txt</div>
                <div class="folded-corner"></div>
            </div>
        </div>
        <div class="flowchart">
            <div class="flow-to-terminal">
                <div class="text-flow">
                    <span>arr[0][0] = 0</span>
                    <span>arr[0][1] = 1</span>
                    <span>arr[0][2] = 2</span>
                    <span>arr[0][3] = 3</span>
                    <span>arr[0][4] = 4</span>
                    <span>arr[0][5] = 5</span>
                </div>
            </div>
            <div class="terminal">
                Terminal
            </div>
        </div>
    </div>
</div>

<div class="note">

The tee command shares its name with the tee pipe in plumbing. Ironically, tee is not rendered as a tee pipe in this analogy. Did we really research plumbing terminology for this lab writeup? Yes.

</div>

We can continue to construct longer pipe systems to feed output through multiple commands. This command runs `problem`, filters its output with `grep`, then outputs to both a file and the terminal.

```
$ ./problem | grep error | tee errors.txt
```

<div class="flowchart">
    <div class="program">
        ./problem
    </div>
    <div class="pipe">
        <div class="text-flow">
            <span>arr[0][0] = 0</span>
            <span>arr[0][1] = 1</span>
            <span>arr[0][2] = 2</span>
            <span>arr[0][3] = 3</span>
            <span>arr[0][4] = 4</span>
            <span>arr[0][5] = 5</span>
        </div>
    </div>
    <div class="program">
        <div class="text">grep error</div>
    </div>
    <div class="pipe">
        <div class="text-flow">
            <span>error: arr[0][50] out of bounds</span>
            <span>error: arr[1][50] out of bounds</span>
            <span>error: arr[2][50] out of bounds</span>
        </div>
    </div>
    <div>
        <div class="program" style="height: 140px">
            <div class="text">tee errors.txt</div>
        </div>
    </div>
    <div>
        <div class="flowchart" style="margin-bottom: 5px">
            <div class="write">
                <div class="text-flow">
                    <span>error: arr[0][50] out of bounds</span>
                    <span>error: arr[1][50] out of bounds</span>
                    <span>error: arr[2][50] out of bounds</span>
                </div>
            </div>
            <div class="file">
                <div class="text">errors.txt</div>
                <div class="folded-corner"></div>
            </div>
        </div>
        <div class="flowchart">
            <div class="flow-to-terminal">
                <div class="text-flow">
                    <span>error: arr[0][50] out of bounds</span>
                    <span>error: arr[1][50] out of bounds</span>
                    <span>error: arr[2][50] out of bounds</span>
                </div>
            </div>
            <div class="terminal">
                Terminal
            </div>
        </div>
    </div>
</div>

In the starter code, we've given you a compiled `select` program and `lotr.txt`. We use this command to select specific columns from an input file that is in the form of a `csv`, which stands for **c**omma **s**eparated **v**alues and is commonly used for things like spreadsheets. `select`'s first argument is how many columns are in the provided `csv` and the following numbers are which columns it will print:

```
$ ./select -c 4 1 2 4 < lotr.txt
```
Notice that the indirection operator (`<`) goes after the command, rather than before it. While it would be very convenient for us to imagine data flowing from left to right, UNIX requires that the first word be a command or executable. So we comply and pretend that the input flows from right to left initially, then continues rightward into any redirects or pipes.

By using redirection and piping in conjunction with the `select` program we've developed previously, we can extend the abilities of program to not only print out a CSV file, but also to create new CSV files and files with rows that match some condition. Try using redirection and piping in addition to the example command above to achieve these results:
- Save the output to a file named `select_lotr.txt`
- Filter the output to rows that correspond to hobbits (i.e. lines that contain the string "Hobbit") and save this filtered output to a file named `hobbit_weapons.txt`. Optionally, also print out the filtered output to the terminal.
- Could you do both of the above in all one command?

## Output Streams

In the examples above, we use redirection and piping to manipulate the *standard output* (`stdout`) of a program. By default, `printf()` outputs to this `stdout` stream, which we illustrate above. What these diagrams do not show (and will not show, please don’t make me try drawing this) is that there actually exists another output stream for *standard error* (`stderr`).

To use `stderr`, we use an alternative to `printf()`, `fprintf()`, and specify that it should output to the `stderr` stream. In `problem.c`, this line is given to you and commented out. Uncomment this line, and comment the line above (the original print statement). Recompile and run the program.

```
$ gcc -g -o problem problem.c
$ ./problem
```

The output looks the same as before. The default destination for both `stdout` and `stderr` streams is the terminal, but this can be redirected. Try redirecting output to `problem.txt` as we did before. What’s different this time?

```
$ ./problem > problem.txt
```

By default, redirection only operates on `stdout`, leaving `stderr` to continue to output to the terminal. We modify the redirection to operate only on `stderr`, leaving `stdout` in the terminal:

```
$ ./problem 2> errors.txt
```

UNIX uses `1>` implicitly as the default redirection operator when we just use `>`. We can read this as "redirect to the stream with file descriptor 1", where the stream with file descriptor 1 is `stdout`.

We can also use two redirections in conjunction with each other to redirect different streams to different files in one command.

```
$ ./problem > problem.txt 2> errors.txt
```

<div class="checkoff">

> First, comment back out the `fprintf` statement and uncomment the `printf` statement, so that all output redirects to stdout.
> Write a command that outputs all lines that involve the first column of the 2D array into both the terminal display and a file called `out0.txt`.
> Write this command on your whiteboard, then ask a tutor or TA to check your work.

</div>

<div class="note" data-title="Hint">

The square brackets are special characters in grep, so to search for `[` and `]`, you must use the escape character. For example, if you wanted to search for `"[5]"`, you would use grep like so: `grep "\[5\]"`

</div>

<div class="gradescope">

Word on the street is that Column 42 isn't the only column in `message.txt` hiding a secret. Time to go find more secrets!

1. Open `message.txt` in Vim (`vim message.txt`) and scroll around. It's a wall of random capital letters, one per line. Quit with `:q!` when you've seen enough, so that nothing you typed by accident gets saved. If you think you changed `message.txt` by accident, run `git restore message.txt` to get the original back.
2. Pick a hint from the table below and work out which column number it points to.
3. `grep` for that number and read the letters from top to bottom. If they spell an English phrase, you found one! If it's garbage letters, try again.
   ```
   $ cat message.txt | grep 42
   ```
4. Once you find a phrase, save those lines into a file called `grep.txt`. Use `>` for your **first** phrase, then `>>` for every phrase after that. Remember, `>` overwrites the file, so using it again will erase the phrases you already saved!
5. Find **at least 5** phrases (42 doesn't count, since we already gave that one away). Feel free to find more if you'd like! `grep.txt` should contain **only** the lines for your phrases: don't include column 42, garbage columns, blank lines, or anything else, or the autograder will mark it wrong.
6. Run `cat grep.txt` to make sure all of your phrases made it in and nothing else snuck in, then submit `grep.txt` to Lab 4 on Gradescope.

</div>

### Hints

There are two kinds of hints:

* **Rows 1 to 5:** Each hint is a bitwise expression on hexadecimal numbers. Work out the result, then convert it to decimal to get the column number.
* **Rows 6 to 12:** Each hint describes a character. The column number is that character's ASCII value in decimal. Run `man ascii` in the terminal to see the ASCII table.

Check off each hint as you find its phrase. The checkboxes are only for you to keep track: nobody else can see them, and they reset when you reload the page.

| Hint | Found it? |
|------|:---------:|
| `0x10 \| 0x03` | <input type="checkbox" class="found-check" autocomplete="off" aria-label="Found it"> |
| `0x1F & 0x36` | <input type="checkbox" class="found-check" autocomplete="off" aria-label="Found it"> |
| `0x03 << 3` | <input type="checkbox" class="found-check" autocomplete="off" aria-label="Found it"> |
| `0x0F ^ 0x15` | <input type="checkbox" class="found-check" autocomplete="off" aria-label="Found it"> |
| `0x3A >> 1` | <input type="checkbox" class="found-check" autocomplete="off" aria-label="Found it"> |
| The C operator that turns `true` into `false` | <input type="checkbox" class="found-check" autocomplete="off" aria-label="Found it"> |
| The character that starts every `#include` | <input type="checkbox" class="found-check" autocomplete="off" aria-label="Found it"> |
| The operator that gives you a variable's address | <input type="checkbox" class="found-check" autocomplete="off" aria-label="Found it"> |
| The character that puts the "C" in CSV | <input type="checkbox" class="found-check" autocomplete="off" aria-label="Found it"> |
| The character that starts every absolute path (and every `//` comment) | <input type="checkbox" class="found-check" autocomplete="off" aria-label="Found it"> |
| The character that stands for the home directory | <input type="checkbox" class="found-check" autocomplete="off" aria-label="Found it"> |
| The character `'1'` (careful: the character, not the number!) | <input type="checkbox" class="found-check" autocomplete="off" aria-label="Found it"> |



<style>
    .flowchart {
        display: flex;
        flex-direction: row;
        align-items: center;
    }

    .program {
        padding: 16px;
        border-radius: 6px;
        background-color: #444;
        border: 2px solid #000;
        color: #fff;
        position: relative;
        text-align: center;
        font-size: 16px;
        font-weight: bold;
        font-family: monospace;
        display: flex;
        align-items: center;
    }

    .terminal {
        padding: 2px 40px 40px 2px;
        border: 2px solid #333;
        background-color: #ddd;
        font-size: 16px;
        font-family: monospace;
    }

    .file {
        padding: 20px;
        border: 2px solid #333;
        background-color: #c8bfa6;
        position: relative;
        text-align: center;
        font-size: 16px;
        font-weight: bold;
        font-family: monospace;
        clip-path: polygon(0 0, 0 100%, 100% 100%, 100% 14px, calc(100% - 14px) 0);
    }

    .folded-corner {
        position: absolute;
        top: 0;
        right: 0;
        width: 10px;
        height: 10px;
        background-color: #333;
        clip-path: polygon(0 0, 0 100%, 100% 100%);
        z-index: 1;
    }

    .folded-corner::after {
        content: '';
        position: absolute;
        top: 0;
        right: 0;
        width: 50px;
        height: 50px;
        background-color: #fff;
        clip-path: polygon(0 0, 0 100%, 100% 100%);
        transform: translate(-5px, 5px);
        z-index: 2;
    }

    .pipe {
        width: 180px;
        height: 42px;
        background-color: #333;
        overflow: hidden;
        position: relative;
        color: #fff;
    }

    .pipe::after {
        content: "pipe";
        position: absolute;
        bottom: 0;
        left: 4px;
        color: #bbb;
    }

    .flow-to-terminal {
        width: 180px;
        height: 32px;
        background-color: #ddd;
        overflow: hidden;
        position: relative;
        display: flex;
        align-items: center;
    }

    .redirect {
        width: 180px;
        height: 42px;
        background-color: #655d46;
        overflow: hidden;
        position: relative;
        color: #fff;
    }

    .redirect::after {
        content: "redirection";
        position: absolute;
        bottom: 0;
        left: 4px;
        color: #bbb;
    }

    .write {
        width: 180px;
        height: 42px;
        background-color: #655d46;
        overflow: hidden;
        position: relative;
        color: #fff;
    }

    .write::after {
        content: "direct file I/O";
        position: absolute;
        bottom: 0;
        left: 4px;
        color: #bbb;
    }

    .found-check {
        appearance: none;
        -webkit-appearance: none;
        width: 22px;
        height: 22px;
        margin: 0;
        border: 2px solid var(--links, #4183c4);
        border-radius: 4px;
        background-color: transparent;
        cursor: pointer;
        display: inline-grid;
        place-content: center;
        vertical-align: middle;
        transition: background-color 0.15s, transform 0.1s;
    }

    .found-check:hover {
        transform: scale(1.1);
    }

    .found-check:checked {
        background-color: var(--links, #4183c4);
    }

    .found-check:checked::after {
        content: "\2713";
        color: var(--bg, #fff);
        font-size: 16px;
        font-weight: bold;
        line-height: 1;
    }

    .found-check:focus-visible {
        outline: 2px solid var(--links, #4183c4);
        outline-offset: 2px;
    }

    .text-flow {
        position: absolute;
        white-space: nowrap;
        font-size: 16px;
        font-family: monospace;
        animation: flow 15s linear infinite;
        display: flex;
        flex-direction: row-reverse;
        gap: 2rem;
    }

    @keyframes flow {
        0% {
            transform: translateX(-100%);
        }
        100% {
            left: 100%;
        }
    }

</style>
