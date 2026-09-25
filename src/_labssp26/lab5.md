---
layout: default
title: Lab 5
parent: Labs
nav_order: 6
permalink: /lab5
---

# Lab 5: Shell scripting, .gitignore, and Mail
{: .no_toc}

{: .note }
You may find our solutions to Lab 3 and Lab 4 in our [solutions repository](https://github.com/CSE29Spring2026/lab-answer-keys). For now, let's focus on lab 5.

In this lab, you will organize some nostalgic files using shell scripting, write
your own `.gitignore`, and send mail messages with Pokemon. You have the entire lab period for this. Have fun!

## Lab 5 learning objectives
{: .no_toc}

* Understand the utility and overall mechanism of shell scripting
* Determine which files should not be tracked by Git and list them in `.gitignore`
* Trade Pokemon by sending and receiving mail on `ieng6`!

#### Table of contents
{: .no_toc}

1. TOC
{:toc }

# Icebreaker

This week you have the opportunity to write an icebreaker that may be used in
future labs\! Please write an icebreaker of your own for this lab. One icebreaker
from last quarter was: _What is your favorite letter?_ which I encourage you to also answer.

<img src="../../assets/labs/sp26/l5_icebreaker.png" alt="icebreaker" width="600">  

{: .important }
Please make sure that everyone in your group answers the icebreaker and writes their name on the whiteboard. We will come around to collect pictures for attendance soon\!

## Swap files
If you have ever gone to open your file and encountered the following:  
<img src="../../assets/labs/sp26/l5_swp.png" alt="swap" width="600">  
you may have wondered what is going on. This is the menu that appears when you try to open a file but your computer sees that it has an associated swap file. If your terminal crashes for some reason while you are editing it, you computer saves your work in a swap file named as follows: if you had `hello.c` it will create `.hello.c.swp` as the swap file (as seen in the picture above). In this file are the changes that it saved for you as it crashed. Reading through the options we find you can:

* Press `E` to open the last save you made. If you are ok with discarding the changes you made after you last `:w` you can choose this option.
* Press `R` to recover what is saved in the `.swp` file. If you haven't saved recently or simply would like to recover the changes you had made, choose this. After you choose this, you can type `:w` as normal in vim to save these recovered changes to your file.  

If you choose the latter option, you will see this menu.  
<img src="../../assets/labs/sp26/l5_recover.png" alt="swap_recover" width="600">  
As per it's suggestion, after you have saved the file and go back to the terminal, you can and should delete the swap file (`rm .hello.c.swp` for example).  
If you choose the former option, you should also make sure to delete the swap file, for fear of later recovering a now out-of-date file.

## Some More Vim!
Let's learn about just a few more Vim commands that might be helpful for the labs and programming assignments.

### Moving Up and Down
You may have noticed that moving up and down line by line in a Vim file can be relatively slow.  Scrolling up and down the file would be faster!

To scroll **d**own in the file, <u>hold</u> the `Ctrl` key and press `d`.

To scroll **u**p in the file, <u>hold</u> the `Ctrl` key and press `u`.

### Custom Configuration
So far, we have seen that Vim commands can be manually typed in an open Vim window, however this can quickly become repetitive if you commonly want to execute the same commands every time you open a new Vim window.

Alternatively, we can tell Vim to execute a certain set of commands automatically every time we open a Vim window in the future. For example, we can type a command to enable syntax highlighting in Vim, which will add syntax-specific coloring to your code and will vastly improve your experience reading through code in Vim.  Another Vim nicety we might want to enable is adding line numbers to the file. There are many, many different commands and settings that we can enable and configure to create our own personal Vim experience, which will make writing code in Vim much more enjoyable!

We will do this by putting these commands directly into a Vim runtime configuration file, called a `.vimrc` file.

{: .note }
> The `.` prefix means that it is a hidden file in UNIX, also commonly called a *dotfile*.  This means that these files will not display, by default, when listing the contents of a directory (using the `ls` command).

By convention, you will create the `.vimrc` file in your home directory:  `~/.vimrc`

{: .note }
> Remember: the tilde character `~` is a shorthand for the current user's (your) home directory in UNIX.

#### Create your .vimrc
Using Vim, create an empty `.vimrc` file in your home directory on your `ieng6` account:
```
$ vim ~/.vimrc
```

Then copy the following lines into your empty `.vimrc` file, as shown in the code snippet below:
```
syntax on
set number
set belloff=all
set showtabline=2   " always show buffer tabs
set tabstop=4
set noexpandtab   " ensures tabs do not expand to spaces
set autoindent
set smartindent
inoremap { {<CR>}<Esc>ko
set backspace=indent,eol,start
```

The effect of each of these commands is summarized briefly below:
- `syntax on`: enable syntax highlighting
- `set number`: display line numbers in Vim
- `set belloff=all`: disable Vim bell sounds
- `set showtabline=2`: always show buffer tabs
- `set tabstop=4`: set tabs to be four spaces
- `set noexpandtab`: does not expand tabs to space
- `set autoindent`: apply indentation to next line based on current line
- `set smartindent`: apply indentation with respect to code syntax
- `inoremap { {<CR>}<Esc>ko`: autocompletion of curly braces for ease of use

{: .note}
> If you find yourself ever working with python, you may want to switch `set noexpandtab` to `set expandtab`. Python cannot handle having mixed tabs and spaces and will error with the message [`TabError: inconsistent use of tabs and spaces in indentation`](../../assets/labs/sp26/l5_python.png).
If you have `set noexpandtab` set and edit a python file that uses spaces, this will occur. For our future purposes we need to have real tab characters for when we learn about Makefiles!

{: .warning }
> In general, you should not paste a command into your `.vimrc` if you are not sure what it is doing. But you can *definitely* trust us! :D

These are our suggestions for `.vimrc` settings that we think would be helpful for you in this class. If you feel like you don't like some of these features, feel free to remove the corresponding lines in the `.vimrc` file. These configuration files are usually customized to each programmer's preferences&mdash;figure out what works well for you!

# What the Shell?

> The other day, I was working on a class assignment that had me running a bunch
> of stress test diagnostics for a cloud system. Each test took about a minute
> to run, and I had to run a bunch of these.
>
> One of my partners asked “why not write a shell script?” And so I did. What
> would have been twenty-five times of typing the same command with different
> numbers turned into a single script I could run once and then go about my day.
> Now, that script probably took more than 25 minutes to write, but that's
> beside the point.

Today, you will use shell scripting to organize a messy file system.

Start by cloning our [starter repo](https://github.com/CSE29Spring2026/lab5-scripting)
into your ieng6 account, as usual. Next, **change into the `minihome` directory**
and take a look at its contents. This directory structure should hopefully look
familiar to you!

Before we get started though, let’s talk about shell scripting and the
executable bit.

A **shell script**, as its name suggests, is a script that runs a series of
shell commands that accomplishes some tasks. These scripts can get very
complicated depending on the task being automated, but even simple shell
scripts can save lots of time. In the coming weeks, you may want to *write a shell script that runs all the tests in PA 3*, for example.


## Task 0: Run a script

<div style="padding: 0 8px; border: 2px solid #cc0004; color: #cc0004" markdown="1">
💡 **KEY POINT**: Any command that you can run on the command line can be
an instruction in a shell script.
</div>

* Fill the provided `task_1.sh` file with some commands that you know like `echo`, `ls`, or `pwd`. Each command should be on a new line.
* To mark the file as executable, run `chmod +x task_1.sh`.
* Try running `./task_1.sh` in your command line, and you should see the output of each command in the order you added them to the shell script.

{: .note }
The `#!/bin/bash` at the top specifies that this script should be parsed using
the bash program at the directory `/bin/`. The leading `#!` is called a
"shebang" and signals the start of this directive. A Python script, for example,
could have `#!/usr/bin/python3` as its first line instead.

Here’s an example you can try. Put the following content in `task_1.sh`:

```bash
#!/bin/bash

echo "Hello!"
echo "Goodbye!"
```

And then, run it. If you see _Permission denied_ and don't know what to do, go
read the [executable bit](./lab2#aside-the-executable-bit) section from lab 2.

```
$ ./task_1.sh
Hello!
Goodbye!
```

As it turns out, all that is needed to complete the above task is to run a
couple of commands sequentially. Here are a couple of knowledge bits that could
be helpful:

{: .note }
> **The wildcard pattern `*`**
>
> In shell scripting, the `*` character acts as a way to target all files and directories. For example, if you ran `cat *`, you would print out the contents of all the files in your current working directory (you would likely also get error messages from trying to view the contents of folders in your directory).  Furthermore, the `*` character can also be used to match specific patterns. For example, if you ran `cat *.txt`, you would print out the contents of all the files in your working directory that have the `.txt` extension.

{: .note }
> **The `mv` command**
>
> The move command, as its name suggests, can be used to move files into directories. For example, you can use it like so:
>
> ```bash
> mv a.txt Books
> ```
>
> This will move a.txt into the Books directory. You can also move multiple files at once like so: `mv a.txt b.txt Books`, which will move a.txt and b.txt into the Books directory.

## Task 1: Books and Music

With these tidbits, you are now ready to write your (possibly) first ever shell script\! **Your first task will be to write a shell script to organize the text and mp3 files in `minihome` into the `Books` and `Music` directories.** Please work on this with your groupmates if you so wish. As a reminder, you can use the `ls -R` command you all discovered back in lab 1 to test if your files ended up in the right place. While testing your script, you may end up accidentally messing up your directory structure. If this happens, we have provided you with a `reset_task_1.sh` script in the **minihome** directory which you can run to reset the .txt and .mp3 files. This will leave your .sh files intact, however, so don’t worry about losing your progress.

{: .checkoff }
Please write what you did for `task_1.sh` on your whiteboard and check in with your teammates.

Our minihome is now looking a lot cleaner. But maybe we can go further. The length of these books seems a bit varied, no? It would be nice if we were able to sort these books into **short stories** and **novels**. This will be your next task. One requirement for your script is that you should be able to supply an **argument** for the cutoff between a novel and a short story. Before you begin the task, **first change into the `Books` directory**.

Here are some knowledge bits that could be useful:

## Shell scripting - variables
{: .no_toc}

You can declare and use variables like so in shell scripting:

```bash
# Contents of demo.sh
#!/bin/bash
num=5
fruit="apples"
echo $num $fruit
```

```
$ ./demo.sh
5 apples
```

To reference a variable, you simply put a dollar sign in front of it.
Note that this still works inside double-quoted strings, so `echo "$num $fruit"` would have achieved the same effect in the script above. To print out `$num $fruit` literally, you would need to either use single quotes (`'$num $fruit'`) or escape the dollar signs (`"\$num \$fruit"`).

## Shell scripting \- accessing command line arguments
{: .no_toc}

To access the `n`th command line argument, use `$n` in your script. For example, the 1st command line argument would be accessed with `$1`. Note that the 0th command line argument is the name of the command you executed. Here is a demonstration:

```bash
# Contents of demo.sh
#!/bin/bash
echo $1 $2
```

```
$ ./demo.sh 5 apples and more
5 apples
```

Note that a string wrapped in quotes counts as one argument. For example, in: `$ ./demo.sh 2 "PA 2"`  We have `$1` equal to `2` and `$2` equal to `PA 2`.

## Shell scripting \- if statements
{: .no_toc}

The basic structure of an if statement in shell scripting is as follows:

```bash
if [ condition ]; then
    # Commands if condition is true
else
    # Commands if condition is false
fi
```

Here is an example of a script that takes in a number from the user, and prints out whether or not it is greater than 5:

```bash
# Contents of demo.sh
if [ $1 -gt 5 ]; then
    echo "Number is greater than 5"
else
    echo "Number is 5 or less"
fi
```

```
$ ./demo.sh 10
Number is greater than 5
```

As you can see, most operators (save for string equality) in bash scripts are different from what you would see in most other programming languages; they look like a hyphen followed by an mnemonic string. Here, the `-gt` comparison operator checks if `$1` is greater than 5\. Though you likely won’t need them for this task, here is a decently comprehensive list of the different types of conditional operators you can find in shell scripting:

**File/directory existence:**

```bash
if [ -f filename ]; then   # Check if file exists
if [ -d directory ]; then  # Check if directory exists
if [ -e filename ]; then   # Check if file or directory exists
if [ -s filename ]; then   # Check if file exists and is not empty
if [ -x filename ]; then   # Check if file is executable
```

**String comparison:**

```bash
if [ "$str1" = "$str2" ]; then   # Strings are equal
if [ "$str1" != "$str2" ]; then  # Strings are not equal
if [ -z "$str1" ]; then          # String is empty
if [ -n "$str1" ]; then          # String is not empty
```

**Numerical comparison:**

```bash
if [ "$num1" -eq "$num2" ]; then   # Numbers are equal
if [ "$num1" -ne "$num2" ]; then   # Numbers are not equal
if [ "$num1" -gt "$num2" ]; then   # num1 is greater than num2
if [ "$num1" -lt "$num2" ]; then   # num1 is less than num2
if [ "$num1" -ge "$num2" ]; then   # num1 is greater than or equal to num2
if [ "$num1" -le "$num2" ]; then   # num1 is less than or equal to num2
```

## Shell scripting \- for loops
{: .no_toc}

In Bash, there are many different types of loops, each having their use cases. Here, we’ll introduce one of those loops: the for loop. The basic syntax is as follows:

```bash
for item in [list of items]; do
  # do something with $item
done
```

Here are some examples of how you can use a for loop:

* Looping through variables:

  ```bash
  for var in item1 item2 item3; do
    echo "$var"
  done
  ```

* Looping through a range of numbers:

  ```bash
  for i in {1..5}; do
    echo "Number: $i"
  done
  ```

* Looping through files in a directory:

  ```bash
  for file in *.txt; do
    echo "Processing $file"
  done
  ```

## The `wc` command
{: .no_toc}

Here, `wc` does not stand for water closet, but rather word count. Passing it a text file will print out the number of lines, words, and characters in that file followed by the name of that file. For example:
```
$ wc alice.txt
3757  29564 174357 alice.txt
```
To print out just the number of lines, words, and characters, You can use the `-l`, `-w`, and `-c` options respectively:

```
$ wc -l alice.txt
3757 alice.txt
$ wc -w alice.txt
29564 alice.txt
$ wc -c alice.txt
174357 alice.txt
```

If you don’t want the name of the file after, and only wanted the number for whatever reason, you can redirect the contents of the file in to the `wc` command like so:

```
$ wc < alice.txt
3757  29564 174357
$ wc -l < alice.txt
3757
```

Neat!

## Shell scripting - command substitution
{: .no_toc}
You can run a command and assign its output (as a string) to a variable using `var=$(command)`. For example:

```bash
lines=$(wc -l < sample.txt)
echo $lines
```

This would store the number of lines in `sample.txt` into `lines` and print it.

## Task 2: Novels and Short Stories

With the above knowledge, you can now write a script to sort text files into the `Novels` and `Short_Stories` folder based on their word length **from scratch**. In `task_2.sh`, we have provided you a base script to work off of, with blanks for you to fill. There is also a `reset_task_2.sh` script, should you wish to restart. To test if your script works, 20000 works well as an argument for differentiating between Novels and Short Stories. Good luck, and have fun\!


Once you have **made sure** that both of your scripts work, we may now proceed to the fun part. First change back to the `minihome` directory, run the `reset_task_3.sh` script to undo the changes from both task 1 and task 2\. Next, run the `task_3.sh` script. This is a pre-written script that will run your tasks 1 and 2 in succession. This means that in **one command**, you can sort all of your files into `Books`, `Novels`, `Short_Stories`, and `Music` folders\!

Confirm that all the text files are in the `Novel` folder (we used a lower threshold), and all the mp3 files are in the `Music` folder, and run the `reset_task_3.sh` script. **Make sure your script works before running the next step\!**

Let’s pretend our user has done a lot of internet browsing and downloaded a lot of files. Run the `simulate_downloads.sh` script.

That’s a lot of txt and mp3 files\! Normally it would take quite a while to sort these out, but luckily, we have our script\! Run `task_3.sh`, and hopefully you should see all of the files get sorted. What normally would have taken perhaps an hour can now be done in an instant\!

# What should Git ignore?

You may have used the `git add .` in the past. By default, this means Git should track everything it finds in your repository directory. **But you don't always want to track everything\!** Here are a few things you shouldn't track in Git in most cases:

1. **Machine code**, such as in object files (`.o` files) and executables

   There are three reasons why you shouldn't track machine code in Git:
   * Git is inefficient at handling large binary files
   * Machine code differs from machine to machine, so they are often useless to your collaborators
   * Binary file conflicts are cumbersome—there's no way to integrate conflicts together

   As a general rule, **you should never use Git to track the outputs of a compilation or transpilation process**. In C projects with Makefiles, the targets defined in the Makefile usually represent the outputs of a compilation process.

2. **Secret credentials**

   Many hosted services have public repositories for the source code of the server. The server needs to authenticate itself to get write access to the database, for example. But the keys for such authentication cannot be public or else anyone can tamper with the database\!

3. **Most hidden files** (files whose names start with `.`, like Vim swapfiles)

   Do not track your Vim swapfile\! Imagine this: You have a terminal prompt and Vim side-by-side. Because Vim is currently running, there is a swapfile in the repository directory. You then commit and push your swapfile to GitHub. Your collaborator pulls it from GitHub without Vim running and tries to edit it with Vim. Because there's a swapfile, Vim gives them a warning, thinking that another Vim process might be editing the file simultaneously even though they don't have Vim running. This is counterproductive\!

## How do we tell Git to ignore them?

`.gitignore` is the exact name of a special file that Git reads to determine which files to skip when looking for untracked files. If a file's name matches any line in `.gitignore`, it is ignored. For example, if a `.gitignore` file contains:

```
*.o
```

Then Git should ignore all files that end with `.o`. In this context, `*` is a wildcard that matches any sequence of characters.

{: .note}
It would be nice if we could write an expression that matches all executable files without an extension. As it turns out, we don't know of a neat way to do this. You could copy the list of targets from your Makefile as an alternative. You could also write a shell script that enumerates all the executable files and writes their names into `.gitignore`. Beware that the wildcard in Makefiles is `%`, while the wildcard in `.gitignore` files is `*`.

## What if they are already being tracked?

You may have committed and pushed these files to Git in the past. To fix this, you can have Git untrack them without removing the actual files themselves by running:

<code>
  $ git rm --cached
  <span contenteditable class="code-replace-me">path to file to untrack</span>
</code>

For example, if you have committed `stack.o` and want to untrack it without deleting it entirely, you would run `git rm --cached stack.o`.

## Write your own `.gitignore`

Some of the files in our starter repository should not have been tracked. First, **change back from `minihome` back to the root of your starter repo.** Run `ls -a` to list all the files (including hidden ones), use your best judgment to decide which ones shouldn't have been tracked, and instruct Git to untrack those files without removing them. Then, write an appropriate `.gitignore` file. To check your work, run `git status`. The files you untracked should not appear in the list of "untracked files", and when you run `git add .`, they should not become tracked again. Don't hesitate to work with your group and ask for help\!

{: .note }
> - Even though `.gitignore` is technically a hidden file, you should track `.gitignore` itself. This prevents your collaborators from tracking the files you don't want to track.
> - You might have noticed the `.git` directory. This is Git's hidden workspace,
>   where it stores your repository's commit history and branches. Git will
>   never track `.git` by default, as this would end up requiring infinite
>   space. Therefore, you don't need to put it in `.gitignore`.

{: .checkoff }
Please write what you added to your `.gitignore` on your whiteboard.

# [You've got Mail!](http://www.aolsucks.org/aolsound.htm){:target="_blank"}

The mail command, unlike other commands we’ve taught you in this lab and previous ones, is especially unique: literally no one\* uses this\! As such, this section is not relevant to any course material. But the idea of sending each other mail via the terminal, all 1970s-core, is too appealing to pass up on.

_\* By “literally no one”, I mean “literally no one, except for at least one person at this university”, so I’ve been told._

Throughout this section, we’ll use `myname` and `friendname` to refer to your and your partner’s UCSD username, respectively. This is the username you use for your UCSD email, and the one you use to log into ieng6.

In order for mail to work, you and whoever you are mailing to must be on the same cluster on ieng6. You do not need to know what a cluster is, but you do need to know how to SSH into a specific one on ieng6. If each line of your command prompt starts with this:

```
[myname@ieng6-640]:~:500$
```

Then `ieng6-640` is the cluster you are logged into. In order to SSH into a specific cluster, exit out of your current SSH session, and in your local machine terminal, type:

<code>
  $ ssh
  <span contenteditable class="code-replace-me">myname</span>@ieng6-640.ucsd.edu
</code>

And enter your password as usual. Make sure both you and your partner are on cluster 640\.

{: .important }
In the following instructions, you will use the `mail` command, but it is not
available on the `ieng6-2xx` servers. Please make sure to **log out of `ieng6`**
and **then** sign into **`ieng6-640.ucsd.edu`**! This specific cluster runs an older
operating system that still has the `mail` command.

Once you and your partner are in the same cluster, try using the mail command to begin composing an e-mail (electronic mail). Either command below works:

```
$ mail friendname@ieng6-640.ucsd.edu
$ mail friendname@ieng6-640
```

This will prompt you with `Subject:` so you can type your email’s subject. The subject is only one line of test, so when you press Enter you are now typing the contents of your mail. When done writing your message, press `Ctrl+D` to finish and send.

Now, your partner can use the `mail` command by itself to see that they have received mail\! It will have a number next to it as it enumerates messages every time you open the mail shell. Type this number and press `Enter` to see the message.

Now that you have mail and therefore can enter the mail shell, you can type `?` to get a list of commands that you can use.

```
type <message list>          type messages
next                         goto and type next message
from <message list>          give head lines of messages
headers                      print out active message headers
delete <message list>        delete messages
undelete <message list>      undelete messages
save <message list> folder   append messages to folder and mark as saved
copy <message list> folder   append messages to folder without marking them
write <message list> file    append message texts to file, save attachments
preserve <message list>      keep incoming messages in mailbox even if saved
Reply <message list>         reply to message senders
reply <message list>         reply to message senders and all recipients
mail addresses               mail to specific recipients
file folder                  change to another folder
quit                         quit and apply changes to folder
xit                          quit and discard changes made to folder
!                            shell escape
cd <directory>               chdir to directory or home if none given
list                         list names of all available commands

A <message list> consists of integers, ranges of same, or other criteria
separated by spaces.  If omitted, Mail uses the last message typed.
```

Note that when the help dialog says “folder”, this is a bit of a misnomer. The “folder” is actually the filename that the command will use. For the `save` and `copy` commands, you can give it a valid path to a file and it will save or copy the contents of the email into the file. The path is relative to wherever you opened the mail shell.

You will likely not need to use all of these commands but at least a few are worth noting:

* `type <message list>` can be used to print out the contents of selected messages. For example, `type 3 4` prints out the contents of messages 3 and 4\.
* `headers` will print out the list of enumerated messages along with their senders, subjects, and statuses.
* You can respond to a message with `Reply <message list>`, which will open a response to the message to type in a reply. Again, you can finish and send with `Ctrl+D`. For example, `Reply 5` opens a response to message 5\.

There also exists another method to send mail from outside the mail shell, using the pipe operator we learned earlier. This command also makes use of the `echo` command, which outputs its argument to stdout. Sounds redundant, but it’s intended to be used in this way to input strings into other commands, or to be used as print statements in bash scripts.

<code>
  $ echo
  <span contenteditable class="code-replace-me">"email body here"</span>
  | mail -s
  <span contenteditable class="code-replace-me">"subject here"</span>
  <span contenteditable class="code-replace-me">friendname</span>@ieng6-640.ucsd.edu
</code>

## Trading Pokemon

We can also use email to send attachments in the form of files. In this section, we’ll trade Pokemon with each other via mail. We will use the `pokeget.sh` script provided in your lab starter code for fun to generate some files with Pokemon in them. First, let one person be the sender, and the other will be the receiver. After you can successfully send and receive Pokemon from one to the other, swap roles and try sending one the other way.

### Sender

Use the below command to generate a ".pk" file with the name of the Pokemon you picked. For example, if you picked Pikachu, \#25, you would call this file `pikachu.pk`. Alternatively, if you want the receiver to not know what the Pokemon is until they open the file, you can call it `mystery.pk`. Feel free to replace `25` with the [National Dex number](https://www.pokemon.com/us/pokedex) of any Pokemon.

```
./pokeget.sh 25 > pikachu.pk
```

If the `pokeget.sh` script seems to take more than a few seconds to finish running, try using `Ctrl + C` to interrupt the program and try running the same command again.

Once you have a ".pk" file, use the following command to send it to your partner, using the `-a` option. Replace "pikachu.pk" with the name of your Pokemon file if it is different.

<code>
  $ echo
  <span contenteditable class="code-replace-me">"email body here"</span>
  |
  mail -s
  <span contenteditable class="code-replace-me">"subject here"</span>
  -a
  <span contenteditable class="code-replace-me">pikachu.pk</span>
  <span contenteditable class="code-replace-me">friendname</span>@ieng6-640.ucsd.edu
</code>

### Receiver

Open up your mail shell with the mail command. You should have a new email if the sender did their job properly. Type the following command to save the email you received as a file, with `n` replaced by the ID number of the email. Note that the “&” is the prompt, and does not need to be typed, just like “$” in the terminal.

```
& save n pokemon.mail
```

Extracting the attachment in a readable form from the email itself is quite involved, so please use the provided script to get your Pokemon:

```
./extract_pokemon.sh pokemon.mail > pokemon.pk
cat pokemon.pk
```
{: .note }
>
> If you get an error running `extract_pokemon.sh` that mentions something about a bad interpreter, this is likely because the file hasn't been formatted for unix correctly yet. Run `sed -i 's/\r$//' extract_pokemon.sh` to reformat the file and try again.


If everything went well, you should get the Pokemon your partner sent you\! Have a bit of fun with this and send each other some cool Pokemon.

{: .checkoff }
> Please spend a couple minutes drawing the pokemon you received from your neighbor.
> You can take turns drawing and reading through the next part.

#  HACKING 
{: style="color: #00ff41 !important; background-color: #0d0d0d; font-family: 'Courier New', Courier, monospace; padding: 10px 20px;text-shadow: 0 0 8px #00ff41, 0 0 20px #00ff41; border-radius: 4px; letter-spacing: 4px;"}

This is the same file you may or may not have started in lab 3 and can be found in [**this** github classroom](https://classroom.github.com/a/7dYavFbQ) in the `gradebook` directory.

## Background

Imagine that you're a less ethical student than I'm sure you actually are. You
overhear from some other students in lab that there's a binary available on the
pi-cluster that can show you your grades on assignments before we formally
release them. You hear quieter whispers that someone found a way to use it to
_change_ their grade. Given our less-than-ethical assumption about your state
of mind, you might be tempted to exploit this for yourself.  

## The Plot Thickens

You see some code open on the professor's laptop during office hours.  You do
your best to commit it to memory and write it down (remember, you're acting
quite unethically in this story), because it strikes you that the code was
something regarding assignment scores.  
![gradebook source code](../../assets/labs/sp26/gradebook_src.png)

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

## The Finale

There are now 2 fun optional activities you can complete:

* Mass mailing, where you send your pokemon to a mailing list of recipients who would be delighted to have your pokemon
* Pokemon `.bash_profile`, how to add pokemon to print whenever you open your terminal.

You can do either or neither in any order, they are here for your own practice and amusement.

## Mass mailing
{: .d-inline-block }

Optional
{: .label .label-purple }

Another useful function in scripting is the while loop. For example, running:

```bash
while read character; do
    echo "$character is a transformer"
done <transformers.txt
```

Given that `transformers.txt` contains:

```
Optimus Prime
Bumblebee
Grimlock
Kickback
Hardshell
Starscream
Megatron
Metroplex
Ironhide
```

Will print:

```
Optimus Prime is a transformer
Bumblebee is a transformer
Grimlock is a transformer
Kickback is a transformer
Hardshell is a transformer
Starscream is a transformer
Megatron is a transformer
Metroplex is a transformer
Ironhide is a transformer
```

Given this and the command to send mail:

<code>
  $ echo
  <span contenteditable class="code-replace-me">"email body here"</span>
  |
  mail -s
  <span contenteditable class="code-replace-me">"subject here"</span>
  -a
  <span contenteditable class="code-replace-me">filename</span>
  <span contenteditable class="code-replace-me">friendname</span>@ieng6-640.ucsd.edu
</code>

Where `-a filename` will attach the file with `filename` to the email, **send everyone in `recipients.txt` your Pokemon**. Please send this to the list in `recipients.txt` **no more than once**. To test your loop, you may want to make a file of your groupmates' emails in the same format of `recipients.txt`. Note that you may also send mail to yourself.

## Adding Pokemon to `.bash_profile`
{: .d-inline-block }

Optional
{: .label .label-purple }

If you would like your Pokemon to appear when you open ieng6, you may do the following.

If you would like 1 Pokemon, add the line <code>cat <span contenteditable class="code-replace-me">~/path/to/pokemon.pk</span></code> (replace the path with the entire path to your Pokemon file, starting with `~`) to the end of the `.bash_profile` file in your home directory.

If you would like 2 Pokemon, add the line <code>paste <span contenteditable class="code-replace-me">~/path/to/pokemon/bigPoke.pk</span> <span contenteditable class="code-replace-me">~/path/to/pokemon/smallPoke.pk</span></code> (replace the path with the actual path to your Pokemon file) to the end of the `.bash_profile` file in your home directory. Note that if you paste the smaller Pokemon first, the larger one will be cut in half. You are welcome to try to troubleshoot this.

If you want to do the same thing on your own computer, you can add this same line to your `.bash_profile` or `.bashrc` file. Just make sure to download the referenced `.pk` files using `pokeget.sh` and edit the paths as needed!

## Other Real world Script examples:

A [real life script](https://github.com/kizhikevich/violating_ripe_probes/blob/main/atlas_pipeline/run_atlas_pipeline.sh) by [Katherine Izhikevich](https://kizhikevich.github.io/) and [Ben Du](https://www.bencdu.com/)    which run several python scripts to retrieve and sort through data.

The script Elena made to print out pokemon randomly when she opens ieng6 [pokemon.sh](./pokemon.sh) (complete with commented out old path variables before she figured out how to pick randomly from an arbitrary amount of directories.)

The script Elena made to print out Joe quotes also upon opening ieng6. [juotes.sh](./juotes.sh) Note that the file is full of lines that look like 
```
Feb 10 -|Energy is priceless, but so is uninterrupted descriptions of structs.
Sept25 2025 @10:16? -|I'm thankful to the computer engineering wizards that provided the magic sand to do this
```

The script Brendan made to automatically zip and re-install python addons for the 3D software Blender. [blender_addon_updater.sh](./blender_addon_updater.sh)

> Note: Understanding scripts.  
> Bash scripting is no small undertaking to understand. It's basically a whole new programming language with it's own syntax and rules, and while this lab covers a ton of the basics, there is a whole truckload of other things. While you do not know everything there is to know about bash-scripting, you do have a foundation of knowledge and *internet access*. Both google searching and asking ChatGPT *can* be super helpful for 2 things: understanding a script, and making one.  
> Wonder what mapfile is? googling this gets an AI overview describing it *and* a link to a man page. This may lead you to the thought "oh right the man pages, maybe I should check it on my computer".  
> pokemon.sh was made with much help from ChatGPT. Elena had a starting point but was unfamiliar with how to get prefixes, suffixes, or how exactly to randomly pick between folders. So, she used ChatGPT how she might switch the file extension from .mail to .pk. Prompts included "how would I remove a prefix" and "how do i pick randomly from a list" to piece together the script.  
> It is also noteworthy that GenAI models will be good at things they have a lot of training on. Common things like what we find in pokemon.sh they will get correct a lot. **Things they are not as well trained on they may very well get wrong and they will do it confidently**. So, please do be careful.
