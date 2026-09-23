# Lab 5 Reference Document


Part 1: `.swp`
--------------------------------
`rm .my_program.c.swp`  
Press `E` for last save you made and  
Press `R` to recover if you didn't save and it is in the `.swp` file

Part 2: Writing a Search Program
--------------------------------

(clone the github classroom repo from here: <https://classroom.github.com/a/tRWujWB3>)

For this lab, you'll be testing your program on the "rockyou" password list from your PA2, you can copy it over from this path on ieng6:

`/home/linux/ieng6/CSE29_WI26_A00/public/pa2/rockyou_clean.txt`

You'll be writing "mysearch.c". Your program should take 1 argument (the string to search for). It should read lines from standard input, and print out all of the input lines that contain the search string.

```
./mysearch PATTERN
```

You can use the `strstr()` function to search for a string within another string.

Part 3: Extra Options
---------------------

Expand your program to handle extra flags: 

`./mysearch -n PATTERN` : print line numbers before each line

`./mysearch -v PATTERN` : print only lines that don't contain PATTERN

`./mysearch -c PATTERN` : don't print pattern matches, just print out the count of matching lines at the end

Each person in your group should implement a different one of these; you'll need all three to do the whiteboard activity.

You can use the `strcmp()` function to check whether two strings are equal.

Make sure you keep the original functionality of the program without flags!!

Work Check-off
--------------

Commit and push your code. You should have at least one of `-n`, `-c`, or `-v` implemented.

Sample Test Cases
--------------

```
$ ./mysearch -n alpaca < /home/linux/ieng6/CSE29_WI26_A00/public/pa2/rockyou_clean.txt
49372: alpaca
261400: alpacas
646255: englandalpaca
2388349: hugoalpaca
2413735: hildaalpaca
3132574: babyalpaca
3253313: alpacast
$ ./mysearch -v a < /home/linux/ieng6/CSE29_WI26_A00/public/pa2/rockyou_clean.txt | head -n 10
iloveyou
princess
nicole
monkey
lovely
qwerty
iloveu
tigger
sunshine
soccer
$ ./mysearch -c alpaca < /home/linux/ieng6/CSE29_WI26_A00/public/pa2/rockyou_clean.txt
7
```


If done early, implement some of the following (in no particular order)
------------------------------------------------------------------------------

-   Make your program handle all 3 of `-n`, `-v`, and `-c`.

-   Add the option `-i`, for case-insensitive search (i.e. `search -i pattern` should match lines containing "Pattern" or "PATTERN")

-   Use [ANSI Escape Codes](https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797) to make your program bold or highlight the matches in every matching line, either always or with a `--color` option. (more info on [Wikipedia](https://en.wikipedia.org/wiki/ANSI_escape_code))

-   Add the option `-A` to print extra context after a match, so e.g. `search -A 2 pattern` would print an extra 2 lines after every match.

-   Add the option `-B` to print extra context before a match (`search -B 2 pattern` would print an extra 2 lines before every match.) (Note: to be able to do this in C with the tools we've seen so far, you might need to set an upper limit on how many lines back your program will be able to support)

-   Make your program handle options more flexibly, e.g. it could:

    -   be able to handle multiple options simultaneously 

    -   accept arguments in any order

    -   exit with a help message for unrecognized options (e.g. -f, -o) instead of treating them as search patterns. (Or if you pass it the -h or --help options) 

    -   if it sees the option "--",  treat all following arguments as search patterns, even if they start with a "-". (This is how actual command line programs allow you to search for the string "-n" instead of specifying the "-n" option.)

    -   allow long versions of options, e.g. `--invert-match`, `--line-number`, `--count`, etc
    

