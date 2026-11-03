# Lab 6: Automating compilation with Makefiles

<div class="note">

You may find our solutions to Lab 5 in our [solutions repository](https://github.com/ucsd-cse29-fall2026/lab_solutions). For now, let's focus on lab 6.

</div>

In this lab, you will review structs, fix a memory leak, learn about the syntax of Makefiles and write a couple Makefile rules.


## Lab 6 learning objectives

* Interpret and understand Makefile syntax
* Write a simple Makefile rule with dependencies and a recipe
* Review the behavior of bitwise operations

# Icebreaker

> What is your dream concert lineup?


<div class="important">

Please make sure that everyone in your group answers the icebreaker and writes their **first and last** name on the whiteboard\!

</div>


## Warmup

![warmup_slide](./assets/warmup_slide.png)

The warmup for this lab will be projected on the screen. The slides will be posted [HERE]() once all labs have concluded.  

[Here](https://classroom50.org/ucsd-cse29-fall2026/cse29-fa26/assignments/lab-6/accept) is the classroom 50 assignment for this lab.

# Part 1: Search and Makefiles

You are given a Makefile with the default set to compile the provided program. You should only need to run `make` to compile.  
To run `search`, you *must* provide an argument of the substring to search for, ie:  
`./search alpaca < rockyou_clean.txt` will search through the `rockyou_clean.txt` file line by line, printing out lines containing "alpaca". Note this file can be found at `/home/linux/ieng6/CSE029_FA26_001/public/rockyou_clean.txt`

The program prints "Malloc returned NULL" if it's malloc call ever returns NULL. 

As `ieng6` is a very large and powerful machine, the limit on how much of it you can use is very high --- but *not infinite*. Let us now test the limits of `ieng6`. 


<div class="exercise">

Using `rockyou_clean.txt`'s even longer cousin, `long_rock.txt` which can be found here `/home/linux/ieng6/CSE029_FA26_001/public/long_rock.txt`. Increase the requested size in the malloc call until you receive the message "Killed" when searching for a word in the file. Each team member should contribute one value which results in "Killed" and one which does not (Brownie points if you narrow in on the threshold) to your whiteboard.

![search_board](./assets/search_board.png)

Leave plenty of space for the next answers like this ^

</div>

We receive this "Killed" message when ieng6 determines we are demanding too much of it. It has the user limit (`ulimit`) set to unlimited. Run `ulimit -a` to see the data segment is set as such. We can set this to be more limited by running `ulimit -d 100000`. 

Restore your `search.c` to it's original state (recall [`git restore`](../week2/index.html#oops-undoing-destructive-changes)?).

Now if we run our search program on the long input again we should see Malloc return NULL. 

What does valgrind say if you run it on your search program now?

To reset your limit, reconnect to ieng6.

<div class="checkoff">

Have each person in your group search for a different string in `long_rock.txt` using `valgrind`, how many bytes does it report as being in use. Do your answers make sense?

Add this to your whiteboard as shown above and call over a staff member to check you off.

</div>


## Makefiles

### Part 0: Recipes and Dependencies

**Enter the `part0` directory.** We have given you an example `Makefile` that illustrates its basic structure. A Makefile mostly consists of "rules", which have the form:

```make
target: dependencies
    recipe
```

In a lot of ways, you can think of defining rules in Makefiles like defining functions in C, but there are important differences.

* The *target* could be thought of as the name of the rule. We use the target to tell `make` which rule should be used. Unlike functions, Makefiles expect targets to be the names of files.
* The *dependencies* are files or other targets that the creation of the target depends on. For C programs, these dependencies are usually source code and object files.
* The *recipe* contains the commands that are executed when `make` uses this rule. Recipes can have one or more different commands to be executed sequentially.

Use this explanation to understand the contents of the `Makefile` in `part0`. Try running `make` with the `cse100` target to ask Make to build `cse100` along with its dependencies:

```
$ make cse100
```

Pretty cool! It might also be useful to clean out and remove any files that got produced if we want to run `make` again, like all the `cse` files that we just made in this Makefile. We do that using: 

```
$ make clean
```

This will remove all the files that start with `cse`. Now, after running `make clean`, we can run: 
```
$ make cse30
$ make cse100
```
See what files get made at each step! Try out the other targets as well, like `cse12` and `cse29`.

### Part 1: Makefile for One

Exit the `part0` directory and enter the `part1` directory, where we are given a single, very simple source code file `program.c`. You can look at its contents, but there’s nothing there to see (or do).

It’s not necessary to define dependencies, but we often do because Makefile automatically checks if any of its dependencies have changed more recently than the target file. If not (and if the target file already exists), then `make` does not bother to execute the recipe, because the target file must already be up to date. This means that `make` will only execute the recipe if the target file doesn’t exist, or one of its dependencies is more recently updated than the target file.

A typical example of a rule for C is the one below:

```make
program: program.c
    gcc -Wall -g -o program program.c
```

In this rule, the target is `program`, which is the executable file we want to create with this rule. The recipe is a `gcc` command to produce `program`, which you would normally run manually in the terminal. Since we define `program.c` to be a dependency of this rule, this means that `program` will only be recompiled if `program.c` is more recently updated than `program`.

This rule example just so happens to work perfectly for the Makefile we want to write in this section, so fill in your Makefile with this rule. Please note you should create your Makefile, for example, using the command `touch Makefile`.

After writing this rule into the Makefile, you can then run `make` with the target to run the compilation command in the recipe:

```
$ make program
```

Notice that `make` prints out the recipe command, and, if you check the contents of the directory, executes that command to compile `program.c`. Try running `make program` again to see that `make` refuses to recompile `program`, because it’s already up to date. Then make a small change to `program.c`, and run `make program` again to see that it recompiles if `program.c` is changed.

This Makefile has already greatly simplified our workflow: instead of typing 33 characters to compile the program, you can type just 12 characters instead. But we can do even better\! Add the following rule to the top of the Makefile:

```make
default: program
```

This rule creates the `default` target with the `program` target as the sole dependency and no recipe. Since it is the first rule to appear in the Makefile, running `make` by itself will default to executing it, which in turns executes the "program" rule as needed. Technically, you could rename the target from `default` to something else, and the behavior of the `make` command by itself would stay the same.

#### Running and Cleaning

Although recipes typically contain commands used to create their corresponding target files, recipes can also contain any other commands you could run in the terminal. As such, some other common uses for Makefiles are to run a program and clean up after a program.

For this program, the rule for running `program` could be defined as:

```make
run: program
    ./program
```

This simple rule depends on the `program` target, meaning that it will automatically recompile `program` if necessary, and run the program. In this case, the target is not a file that we expect to compile, just a convenient name that we use to use this rule.

Similarly, we also often define a rule to clean up files that are produced from the build process. This specific example does not produce any, but sometimes it is also desirable to clean up the target file itself in order to recompile without changes to the source code.

```make
clean:
    rm program
```

In most cases, this will work without issue, but in the rare case that you create a file called “run” or “clean”, the corresponding rule won’t work properly anymore. This occurs because `make` does not recognize that “run” and “clean” are not supposed to be files. So when a file of that name is created, the standard behavior of `make` causes our intended functionality of these two rules to fail: `make` will not use these rules unless that file no longer exists or a dependency updates. If you want to, try making a file called “run” or “clean” to see this happen.

In order to account for this edge case, we can manually define `run` and `clean` to be phony targets. A phony target doesn't really refer to a file; rather it is just a recipe to be executed when requested.

```make
.PHONY: run clean
```

After defining these rules, your Makefile might look something like this:

```make
default: program

program: program.c
    gcc -Wall -g -o program program.c

.PHONY: run clean

run: program
    ./program

clean:
    rm program
```

All the rules (and phony target definition) can be defined in any order, except `default` must be placed at the top in order to be executed when you run `$ make` by itself.

### Part 2: Makefile for Many

In this section, we’ll show multiple valid Makefiles for the programs **in the `part2` directory**. As you follow along, pick one and use it to compile all three programs.

When we have multiple programs to be compiled in a single project, we could create a Makefile with rules for each:

```make
default: program1 program2 program3
program1: program1.c
    gcc -Wall -g -o program1 program1.c
program2: program2.c
    gcc -Wall -g -o program2 program2.c
program3: program3.c
    gcc -Wall -g -o program3 program3.c
```

Notice how much repetition there is between each rule here. In this case, the repetition is just mildly annoying, but if you have more independent programs (like I do when designing lab activities), mildly annoying becomes very annoying\! We’ll see how we can reduce repetition in two different ways that we’ll use together to create a very concise and flexible Makefile.

#### Variables

Like in C programs, you can also define variables in Makefiles. But unlike C programs, where defined variables are allocated in some memory when the program is run, variables in Makefiles just represent some string value. This lets us reduce the amount of repetition when we want to, for example, change the `gcc` flags to use in all rules. As such, some common values we can define as variables are the compiler command and its flags:

```make
CC = gcc
CFLAGS = -Wall -g

default: program1 program2 program3

program1: program1.c
    $(CC) $(CFLAGS) -o program1 program1.c
program2: program2.c
    $(CC) $(CFLAGS) -o program2 program2.c
program3: program3.c
    $(CC) $(CFLAGS) -o program3 program3.c
```

The variables `CC` and `CFLAGS` are defined with the values `gcc` and `-Wall -g`, respectively. Then we use these variables in each of the recipes. Note that there is a special syntax when we use the variables: `$(X)`, where `X` is the variable name. This syntax tells the Makefile to expand the variable `X` to use its value, instead of interpreting "X" as a literal string.

#### Pattern Rules

Each of these three rules have a similar pattern: each one is identical to the others except for a single number that changes. To eliminate this repetition, we can merge these rules into one *pattern rule*:

```make
CC = gcc
CFLAGS = -Wall -g

default: program1 program2 program3

program%: program%.c
    $(CC) $(CFLAGS) -o $@ $<
```

A couple of new symbols were introduced in this pattern rule:

* A target with a "%" character creates a pattern rule. The "%" in the target can match any non-empty string, then for each corresponding match, the "%" has that same value in the dependencies. For example, this rule matches `program1`, `program2`, and `program3` and defines their respective dependencies `program1.c`, `program2.c`, and `program3.c`. This will also define dependencies for any valid match to the target: `program4` depends on `program4.c`, `programaaa` depends on `programaaa.c`, etc.
* In a pattern rule, we use *automatic variables* to refer to the target and dependencies, since their exact value is not determined explicitly.
  * `$@` is an automatic variable which represents the target of the rule.
  * `$<` is an automatic variable which represents the first dependency of the rule.

  Other useful automatic variables are given [here](https://www.gnu.org/software/make/manual/html_node/Automatic-Variables.html).

If we were really bold (which we are), we could generalize this Makefile further:

```make
CC = gcc
CFLAGS = -Wall -g

default: program1 program2 program3

%: %.c
    $(CC) $(CFLAGS) -o $@ $<
```

This pattern rule now matches any name (not just names that begin with "program") to be a target, and defines its dependency to be a file with that name plus the ".c" suffix.

In this section, we’ve developed a Makefile to be increasingly more flexible, both in making future changes easier and expanding the scope of valid targets. An important point to make (pun intended?) is that each of these Makefiles is a valid Makefile for compiling the three programs given in this directory, and they have their own pros and cons. For example, a Makefile similar to the last one was used in last week’s lab to easily compile programs with different names, where the compilation process is the same across programs. However, it might be undesirable to enable the programmer to attempt compiling any file ending in “.c”. On the other hand, the first Makefile might be a good fit for a use case where we know we will customize the build process for each program, but this could lead to a very large Makefile.

### Part 3: Linking Object Files

When we use `gcc` to manually compile programs, we typically compile directly from the source file to the executable program. But, the build process involves multiple steps with intermediary files. One of these intermediary files are *object files*, which contain machine code from a particular *module* (.c and .h combo) and are linked into the eventual executable file. If `.class` files from Java sound familiar to you, object files are like `.class` files. To instruct `gcc` to compile a source file into an object file, we add the `-c` flag.

![Build Process](https://cf-assets.www.cloudflare.com/zkvhlag99gkb/3RNZmg4aDxjJOAjAmYxFk9/c1279a03f8962b5bb74f812b66a4a448/build.png)
(Credit: Cloudflare)

The linking process resolves symbol references between object files, meaning that functions defined in one file can be used in another. In `part3`, a long program with 50000 adder functions (each of which adds the integer in its name to the parameter and returns it) is given in `adders.c`. The corresponding header file, `adders.h`, contains function declarations to be shared between source files. Then, in `main.c`, we print the return value of `run_adders`, which calls all of the adder functions and sums their results.  


We can use the following `gcc` commands to create then link the object files (we will run the `time` command so it will tell us how long each of these commands took to run):

```
$ time gcc adders.c -o adders.o -c 
$ time gcc main.c -o main.o -c
$ time gcc adders.o main.o -o adders
```

We create `adders.o` from `adders.c`, create `main.o` from `main.c`, then link the two produce the executable `adders`. My fingers hurt from all that typing; I wish there was an easier way to *MAKE* all these files...


```make
CC = gcc
CFLAGS = -Wall -g
TARGET = adders
OBJS = adders.o main.o

default: $(TARGET)

adders.o: adders.c adders.h
    $(CC) $(CFLAGS) -c -o $@ $<

main.o: main.c
    $(CC) $(CFLAGS) -c -o $@ $<

$(TARGET): $(OBJS)
    $(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

run: $(TARGET)
    ./$(TARGET)

clean:
    rm $(TARGET) $(OBJS)
```

Here, we make extensive use of variables for the ultimate target (`adders`) and its prerequisite object files (`adders.o` and `main.o`) so that we can easily use these strings in multiple places, e.g. in both the compile command and in the `rm` command. Examine this Makefile and feel free to ask your groupmates, tutors, or TA about anything unclear.

Go to the `one_million_functions` directory and take a look at the `script.sh` file (a bash script, which we learned about last week).  
This runs very similar commands to the time commands you ran previously to compile the `adders` program. This example, however, has one million functions as opposed to the original fifty thousand.  
![](./assets/one-million-functions.png)  
To run a program in the background we can add a `&` immediately following it.
```bash
$ ./script.sh > out.txt &
```
for example, will write to our output file and do so in the background, meaning you can use your terminal in the meantime. You can check on this periodically by using `cat` to see `out.txt`, go ahead and see what it has immediately after starting your background process.


### Part 4: Makefile challenge 

Go to the `part4` directory and open the `Makefile` there, which is partially completed. Complete the `Makefile` according to the requirements listed inside it. Feel free to copy code segments from above. Once you're done, try `make` to see your Makefile in action\!

<div class="gradescope">

Submit your finished repository to Gradescope!
</div>


# Next steps

If you finish with the lab content above you may any do the following:
* Do the lab 7 preview below.
* Work on Project 3
* Learn something new about unix/ systems and share with people around you.

# Lab 7 Preview: Hacking

## 7.1. Background

Imagine that you're a less ethical student than I'm sure you actually are. You
overhear from some other students in lab that there's a binary available on the
pi-cluster that can show you your grades on assignments before we formally
release them. You hear quieter whispers that someone found a way to use it to
_change_ their grade. Given our less-than-ethical assumption about your state
of mind, you might be tempted to exploit this for yourself.  

## 7.2. The Plot Thickens

You see some code open on the professor's laptop during office hours.  You do
your best to commit it to memory and write it down (remember, you're acting
quite unethically in this story), because it strikes you that the code was
something regarding assignment scores.  
![gradebook source code](./assets/gradebook_src.png)

Using this information, you decide to give yourself and A with a score 
to match while maintaining a real due date.  
**HINT**
When important values are adjacent on the stack, overflowing an array with
values that you control can let you assign into other stack-allocated values.


GDB commands that may be useful for this activity:

-   `(gdb) info locals`

-   `(gdb) info args`

-   `(gdb) print VALUE (or p VALUE)` You can print any variable or expression, e.g.

-   `print x`, `p arr[5]`, `p ((x & 0b1111) << 3)`

-   You can also specify a format to print in

-   `print/t` (binary), `print/x` (hex), `print/d` (decimal)

-   `(gdb) x ADDRESS` This prints out memory at an address, e.g. strings / arrays / pointers

-   `(gdb) x/16cb str1` This prints the first 16 bytes of `str1` as characters

-   `(gdb) x/20xb str2` This prints 20 bytes of `str2` in hex

-   `(gdb) x/4dw  arr` This prints 4 "words" (i.e. `int32s`) of `arr`, as decimal numbers

-   You can use the following [reference card](https://darkdust.net/files/GDB%20Cheat%20Sheet.pdf) for reference on gdb commands, and format commands for x and print.


