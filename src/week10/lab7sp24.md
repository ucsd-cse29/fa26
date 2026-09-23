---
layout: default
title: Lab 7
parent: Labs
nav_order: 6
---

# Lab 7: More UNIX Commands
{: .no_toc}

#### Table of contents
{: .no_toc}

1. TOC
{:toc }

## Getting Started

With your partner, discuss:
- Pick a song as the soundtrack of your life! Why you did you choose this song?
- What's your favorite genre? Who's your favorite artist?

## Searching and Filtering Program Output

Accept the assignment on GitHub Classroom ([https://classroom.github.com/a/CqBPPmEw](https://classroom.github.com/a/CqBPPmEw)) to create a repo with the starter code for this lab. Clone this repo into your `cse29` folder on `ieng6`.

In this lab, we'll walk you through some helpful UNIX commands that are commonly used to save and filter program output. There are multiple ways to achieve the same result, and we'll demonstrate advantages and disadvantages of each.

In the starter code, you are given a `problem.c` source code file. This program creates a large 2-D array, fills it with numbers, and prints them out. Fortunately, whoever wrote this was thoughtful enough to write code to check for an out-of-bounds error. Unfortunately, whoever wrote this was not thoughtful enough to debug the program. Fortunately, you don't need to debug this program; we're going to use this program as an example of how the following UNIX commands can be used to parse a lot of program output easily.

Compile and run `problem` to see exactly what "a lot of program output" means.
```
$ make problem
$ ./problem
```
Every so often there's an error message, but it's separated by all the expected program output. For programs with more errors and more output, you could imagine how we wouldn't want to keep scrolling up the terminal to read. There are multiple ways in which we can filter out everything but the error messages.

### Say Less

In previous PAs, we've already used the *indirection* (`<`) and *redirection* (`>`) operators. These are used to feed input into a program, or redirect the output of a program into a file. Let's first save the output of the program to a text file:
```
$ ./problem > problem.txt
```
Redirection overwrites any content of the destination file with the output. There also exists the append (`>>`) operator, which works similarly to redirection, but appends the output to the end of the destination file instead of overwriting.
```
$ ./problem >> problem.txt
```

You can use `cat` to view the contents of the file, but this is no better than letting the program output directly to the terminal. Instead, we can say `less` to start a program to display a portion of the file and navigate freely through it. It's like `cat`, but shows less at a time.
```
$ less problem.txt
```

{: .note }
The `less` command succeeds the `more` command, which does the same thing but does not support backwards navigation. In this sense, `less` is like `more`, but also (as `man less` duly notes) `less` is the opposite of `more`.

The one subcommand you need to know is to type `h` while in this program to display a list of subcommands. Some especially helpful subcommands include `q` to quit and `f`/`b` to move forward/backward one window. The subcommand we want to use to filter out all lines that do not have an error is to type "&" followed by the word "error", then press Enter. `less` will insert a slash ("/") in between to indicate that what follows is a pattern to match. This method of filtering is convenient if you don't want to clutter the terminal interface, but requires that the output exists in a file already.

### grep

The `grep` command is most commonly used to search for lines of a file that match some string. `grep` takes in two arguments: the string to match and a file to read from.
```
$ grep error problem.txt
```

This command directly outputs to the terminal, which can be acceptable if you expect the output to be short, and helpful if you don't want to run the search as a subcommand within another program, as with `less`.

Try practicing filtering file contents with `message.txt`, using either `less` or `grep`. This file contains the output of another command, which created a large array, assigned random capital character values, and printed it out. For some strange reason, the output shows that some characters were written way out of bounds at column index 42, but it's hard to tell what's happened when each line is separated by all the other output. Use `less` or `grep` to search for all lines that contain the string "42". Are you [surprised](https://www.youtube.com/watch?v=dQw4w9WgXcQ) by what you find?

## Flow Like Water

### Piping

Both of these methods require you to create a file which contains the output of a file. This is generally pretty easy to do, but can be undesirable if you have a lot of output that you don't want to be saved into a really large file (or are indecisive about naming files). The solution to circumvent this is to use *pipes*.

~~Within industry, piping is a system of pipes used to convey fluids (liquids and gases) from one location to another.~~ Within UNIX, the pipe operator (`|`) is used to directly feed output from one program as input into another program. We can pipe directly from the `problem` program into either `less` or `grep` to accomplish the same result as running these commands on the `problem.txt` file.
```
$ ./problem | less
$ ./problem | grep error
```

We can compound indirection, redirection, and pipe operators to create helpful commands. Understanding how these operators work in conjunction with each other can be understood as an analogy to actual pipes, rendered below in immaculate ASCII art.

By default, print statements in programs output directly to the terminal interface. So this command:
```
$ ./problem
```
looks like this:
```
+-----------+
|           |==
| ./problem | ~ ~ ~ ~ ~> terminal
|           |==
+-----------+
```

By using the redirection operator, we install an elbow pipe to redirect the flow of output into a file. The output no longer flows into the terminal.
```
$ ./problem > problem.txt
```
```
+-----------+  redirect
|           |==------+    
| ./problem | ~ ~ ~  |   terminal
|           |==--+ $ +
+-----------+    | $ |
                 | v |
              problem.txt
```

By using the pipe operator, we install a coupling between the output and input of two programs. Without any other pipes at the end, the output of the second program flow into the terminal.
```
$ ./problem | grep error
```
```
+-----------+   pipe    +-----------+
|           |==-------==|           |==
| ./problem | ~ ~ ~ ~ ~>|   grep    | ~ ~ ~ ~ ~> terminal
|           |==-------==|           |==
+-----------+           +-----------+
```

By using both piping and redirection, we can chain multiple commands and file writing actions. In this command, we run the `problem` program, filter its output with `grep`, and output the filtered lines into a file. This file now contains the error messages from `problem`, and can serve as an error log. Does this output to the terminal as well?
```
$ ./problem | grep error > errors.txt
```
```
+-----------+   pipe    +-----------+  redirect
|           |==-------==|           |==------+
| ./problem | ~ ~ ~ ~ ~>|   grep    | ~ ~ ~  |   terminal
|           |==-------==|           |==--+ $ +
+-----------+           +-----------+    | $ |
                                         | v |
                                       errors.txt
```

### Having Your Tee and Drinking It Too

Redirection lets us write to a file. Not having redirection lets us directly see the output in the terminal. Why don't we have both?

By using the `tee` command, we can simultaneously write output to a file and and continue flowing data rightward, usually to the terminal. `tee` is a command, not an operator like redirection and piping, so we must pipe into `tee` first. `tee` takes a filename as an argument, which it outputs to.
```
$ ./problem | tee problem.txt
```
```
+-----------+   pipe    +-----------+
|           |==-------==|           |==
| ./problem | ~ ~ ~ ~ ~>|   tee     | ~ ~ ~ ~ ~> terminal
|           |==-------==|           |==
+-----------+           +-----------+
                            | $ |
                            | v |
                         problem.txt
```

{: .note }
The `tee` command shares its name with the tee pipe in plumbing. Ironically, `tee` is not rendered as a tee pipe in this analogy. Did I really research plumbing terminology for this lab writeup? Yes.

We can continue to construct longer pipe systems to feed output through multiple commands. This command runs `problem`, filters its output with `grep`, then outputs to both a file and the terminal.
```
$ ./problem | grep error | tee errors.txt
```
```
+-----------+   pipe    +-----------+   pipe    +-----------+
|           |==-------==|           |==-------==|           |==
| ./problem | ~ ~ ~ ~ ~>|   grep    | ~ ~ ~ ~ ~>|   tee     | ~ ~ ~ ~ ~> terminal
|           |==-------==|           |==-------==|           |==
+-----------+           +-----------+           +-----------+
                                                    | $ |
                                                    | v |
                                                  errors.txt
```

In the starter code, we've given you a compiled `select` program and `lotr.txt` from PA3. Remember that we use this command to select specific columns from an input file:
```
$ ./select -c 4 1 2 4 < lotr.txt
```
Notice that the indirection operator (`<`) goes after the command, rather than before it. While it would be very convenient for us to imagine data flowing from left to right, UNIX requires that the first word be a command or executable. So we comply and pretend that the input flows from right to left initially, then continues rightward into any redirects or pipes.

By using redirection and piping in conjunction with the `select` program we've developed previously, we can extend the abilities of program to not only print out a CSV file, but also to create new CSV files and files with rows that match some condition. Try using redirection and piping in addition to the example command above to achieve these results:
- Save the output to a file named `select_lotr.txt`
- Filter the output to rows that correspond to hobbits (i.e. lines that contain the string "Hobbit") and save this filtered output to a file named `hobbit_weapons.txt`. Optionally, also print out the filtered output to the terminal.
- Could you do both of the above in all one command?

### Output Streams

In the examples above, we use redirection and piping to manipulate the *standard output* (`stdout`) of a program. By default, `printf()` outputs to this `stdout` stream, which we illustrate above. What these diagrams do not show (and will not show, please don't make me try drawing this) is that there actually exists another output stream for *standard error* (`stderr`).

To use `stderr`, we use an alternative to `printf()`, `fprintf()`, and specify that it should output to the `stderr` stream. In `problem.c`, this line is given to you and commented out. Uncomment this line, and commend the line above (the original print statement). Recompile and run the program.
```
$ make problem
$ ./problem
```
The output looks the same as before. The default destination for both `stdout` and `stderr` streams is the terminal, but this can be redirected. Try redirecting output to `problem.txt` as we did before. What's different this time?
```
$ ./problem > problem.txt
```

By default, redirection only operates on `stdout`, leaving `stderr` to continue to output to the terminal. We modify the redirection to operate only on `stderr`, leaving `stdout` in the terminal:
```
$ ./problem 2> errors.txt
```
UNIX uses `1>` implicitly as the default redirection operator when we just use `>`. We can read this as "redirect to the stream with file descriptor 1", where the stream with file descriptor 1 is `stdout`.

We can also use two redirections in conjuction with each other to redirect different streams to different files in one command.
```
$ ./problem > problem.txt 2> errors.txt
```

## You Got Mail!

The `mail` command, unlike other commands we've taught you in this lab and previous ones, is especially unique: literally no one* uses this! As such, this section is not relevant to any course material. But the idea of sending each other mail via the terminal, all 1970s-core, is too appealing to pass up on.

{: .note }
*By "literally no one", I mean "literally no one, except for at least one person at this university", so I've been told.

### Sending Mail

Throughout this section, we'll use `myname` and `friendname` to refer to your and your partner's UCSD username, respectively. This is the username you use for your UCSD email, and the one you use to log into `ieng6`.

In order for mail to work, you and whoever you are mailing to must be on the same cluster on `ieng6`. You do not need to know what a cluster is, but you do need to know how to SSH into a specific one on `ieng6`. If each line of your command prompt starts with this: 

```
[myname@ieng6-203]:~:500$
```

then `ieng6-203` is the cluster you are logged into. In order to SSH into a specific cluster, exit out of your current SSH session, and in your *local machine terminal*, type:

```
$ ssh myname@ieng6-203.ucsd.edu
``` 

and enter your password as usual. You can choose between clusters `201`, `202`, and `203`, as long as you make sure you and your partner are in the same cluster. This writeup will continue using cluster `203` in the following instructions.

Once you and your partner are in the same cluster, try using the `mail` command to begin composing an e-mail (electronic mail). Either command below works:
```
$ mail friendname@ieng6-203.ucsd.edu
$ mail friendname@ieng6-203
```

This will prompt you with `Subject:` so you can type your email's subject. The subject is only one line of test, so when you press `Enter` you are now typing the contents of your mail. When done writing your message, press `Ctrl` + `D` to finish and send.

Now, your partner can use the `mail` command by itself to see that they have received mail! It will have a number next to it as it enumerates messages every time you open the mail shell. Type this number and press `Enter` to see the message.

Now that you have mail and therefore can enter the mail shell, you can type `?` to get a list of commands that you can use.

```
type <message list>             type messages
next                            goto and type next message
from <message list>             give head lines of messages
headers                         print out active message headers
delete <message list>           delete messages
undelete <message list>         undelete messages
save <message list> folder      append messages to folder and mark as saved
copy <message list> folder      append messages to folder without marking them
write <message list> file       append message texts to file, save attachments
preserve <message list>         keep incoming messages in mailbox even if saved
Reply <message list>            reply to message senders
reply <message list>            reply to message senders and all recipients
mail addresses                  mail to specific recipients
file folder                     change to another folder
quit                            quit and apply changes to folder
xit                             quit and discard changes made to folder
!                               shell escape
cd <directory>                  chdir to directory or home if none given
list                            list names of all available commands

A <message list> consists of integers, ranges of same, or other criteria
separated by spaces.  If omitted, Mail uses the last message typed.
```

Note that when the help dialog says "folder", this is a bit of a misnomer. The "folder" is actually the *filename* that the command will use. For the `save` and `copy` commands, you can give it a valid path to a file and it will save or copy the contents of the email into the file. The path is relative to wherever you opened the mail shell.

You will likely not need to use all of these commands but at least a few are worth noting:
- `type <message list>` can be used to print out the contents of selected messages. For example, `type 3 4` prints out the contents of messages 3 and 4.
- `headers` will print out the list of enumerated messages along with their senders, subjects, and statuses.
- You can respond to a message with `Reply <message list>`, which will open a response to the message to type in a reply. Again, you can finish and send with `Ctrl` + `D`. For example, `Reply 5` opens a response to message 5.

There also exists another method to send mail from outside the mail shell, using the pipe operator we learned earlier. This command also makes use of the `echo` command, which outputs its argument to `stdout`. Sounds redundant, but it's intended to be used in this way to input strings into other commands, or to be used as print statements in bash scripts.

```
$ echo “email body here” | mail -s “subject here” friendname@ieng6-203.ucsd.edu
```

### Trading Pokemon

We can also use email to send attachments in the form of files. In this section, we'll trade Pokemon with each other via mail. We will use the `pokeget.sh` script briefly showcased in last week's lab for fun to generate some files with Pokemon in them. First, let one person be the sender, and the other will be the receiver. After you can successfully send and receive Pokemon from one to the other, swap roles and try sending one the other way.

#### Sender

Use the below command to generate a ".pk" file with the name of the Pokemon you picked. For example, if you picked Pikachu, #25, you would call this file `pikachu.pk`. Alternatively, if you want the receiver to not know what the Pokemon is until they open the file, you can call it `mystery.pk`. Feel free to replace `25` with the National Dex number of any Pokemon.

```
./pokeget.sh 25 > pikachu.pk
```

{: .note }
If the `pokeget.sh` script seems to take more than a few seconds to finish running, try using `Ctrl` + `C` to interrupt the program and try running the same command again.

Once you have a ".pk" file, use the following command to send your it to your partner, using the `-a` option. Replace "pikachu.pk" with the name of your Pokemon file if it is different.

```
$ echo "email body here" | mail -s "subject here" -a pikachu.pk friendname@ieng6-203.ucsd.edu
```

#### Receiver

Open up your mail shell with the mail command. You should have a new email if the sender did their job properly. Type the following command to save the email you received as a file, with `n` replaced by the ID number of the email. Note that the "&" is the prompt, and does not need to be typed, just like "$" in the terminal.

```
& save n mail.pk
```

Extracting the attachment in a readable form from the email itself is quite involved, so please use the provided script to get the your Pokemon:

```
$ ./extract_pokemon.sh mail.pk > pokemon.pk
$ cat pokemon.pk
```

If everything went well, you should see get the Pokemon your partner sent you! Have a bit of fun with this and send each other some cool Pokemon.

## PA5 Supplement

If you haven't already and you're not too confident about bit manipulation, try the [PA5 preparation exercise](https://cse29sp24.github.io/docs/labs/lab6.html#pa5-preparation) from Lab 6. Otherwise, we strongly recommend you to work on PA5!

## Optional Feedback Form

If you'd like to give feedback on how labs are conducted and how they can be improved, please feel free to submit any comments in [this anonymous form](https://docs.google.com/forms/d/e/1FAIpQLSdVrEZvQNcd5nt5mfrI_eEVQHJCNNBFdSn07BJSCaastSVpXg/viewform?usp=sf_link). This is a space for you to drop any comments you have at the end of every lab!
