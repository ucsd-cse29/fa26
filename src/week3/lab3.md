# Part 1:  SSH Keys to ieng6
Note: if you have a personal laptop you can set up ssh keys on it to be able to ssh to ieng6. If you're on windows, you’ll need a linux-like terminal, so use [the terminal in VSCode](https://code.visualstudio.com/docs/terminal/getting-started), a program like [git bash](https://gitforwindows.org/), or [WSL](https://ubuntu.com/desktop/wsl) for this.

If you don’t have a laptop or it isn’t set up with a linux terminal, work from your lab computer for today. You can set up ssh keys on your laptop at home on your own time.

1. Generate a new pair of ssh keys (on your laptop, or on your lab computer)
- `cd` to your `.ssh` directory, (if it doesn’t exist, first create it with `mkdir ~/.ssh`)
- **IF YOU ALREADY HAVE AN 'id_rsa', SKIP THIS STEP** (otherwise you'll overwrite your github keys)
- If you don't have an id_rsa, run: `ssh-keygen -t rsa -b 4096 -C YOUR_EMAIL_ADDRESS`
  - You'll be using the default filename and no password, so just press enter twice
- Copy the contents of your new public key (you can print out the contents with `cat`)
2. Copy your public key onto ieng6, into the file `~/.ssh/authorized_keys`
- On `ieng6`, in your `.ssh` directory, create a file called `authorized_keys` (or open it if it exists already)
- Use `vim` to paste in the contents of the new public key into the `authorized_keys` file
  - (if your `authorized_keys` already existed, paste the new key on a new line at the end)
3. Log out from `ieng6` (use `exit`), and make sure you can ssh into it without typing your password
- If you used a different name than `id_rsa`, you have to ssh with a `-i [private key path]` flag

## Color ls
1. Use vim to edit the following file in your home directory: `vim .bash_profile`
2. Add a line to the end of this file (you can scroll to the bottom of the file, and press ‘o’ to enter insert mode on a new line): `alias ls="ls --color"`
- if you have file permission issues, you can use `sudo chmod u+rwx ~/.bash_profile` (or search up ways to fix permission issues for your `.bash_profile`)



# Part 2: Debugging with -Wall 
Clone the repository we’ll be using for this lab (you’ll need to get the ssh URL). You’ll be working with one of the three programs, depending on your group: 
[https://classroom.github.com/a/tYCFrrGl](https://classroom.github.com/a/tYCFrrGl)

Many common errors can be caught by the compiler, but a lot of these checks aren't enabled by default. We can ask the compiler to warn us by adding the `-Wall` flag ("- W(arn) all") when you compile:
```
$ gcc -Wall YOUR_CODE.c -o YOUR_CODE
```


# Part 3: Debugging with `gdb`

### Intro to gdb commands:
- To use gdb, make sure you’ve compiled your program with “debug symbols”
```
$ gcc -g YOUR_CODE.c 
```
- Run your compiled code in gdb 
```
$ gdb YOUR_BINARY
```
- This puts you into a gdb prompt: normal terminal commands don’t work here, and you can instead run gdb-specific commands
```
(gdb) run     # starts running your program
```
- If your program stops running or segfaults in gdb, print out the backtrace (also called a “stack trace”)
```
(gdb) backtrace    
```
or    
```
(gdb) bt
```

### Use the following commands to print out values at the point the program stopped: 
- `(gdb) info locals`
- `(gdb) info args`
- `(gdb) print VALUE (or p VALUE)`
  - You can print any variable or expression, e.g.
    - `print x`,  `p arr[5]`, `p ((x & 0b1111) << 3)`
  - You can also specify a format to print in
    - `print/t` (binary), `print/x` (hex), `print/d` (decimal)
- `(gdb) x ADDRESS`    
  - This prints out memory at an address, e.g. strings / arrays / pointers
- `(gdb) x/16cb str1`      
  - This prints the first 16 bytes of `str1` as characters
- `(gdb) x/20xb str2`      
  - This prints 20 bytes of `str2` in hex
- `(gdb) x/4dw  arr`       
  - This prints 4 “words” (i.e. int32s) of `arr`, as decimal numbers 
- You can use the following [reference card](https://darkdust.net/files/GDB%20Cheat%20Sheet.pdf) for reference on gdb commands, and format commands for x and print.

If you’re done early, use the reference card to try exploring other gdb commands!


# Lab 3 Work Check-Off (due before next Tuesday lecture):
In your copy of the [lab3-buggy repo](https://classroom.github.com/a/tYCFrrGl): fix the bugs in your assigned program, then commit and push your changes so they show up on GitHub.


