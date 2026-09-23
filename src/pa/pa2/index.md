# PA2 - Hashing and Passwords: Due 1/29 at 11:59pm - [Github Classroom Link](https://classroom.github.com/a/m9ZLT8wD)

[Cryptographic hash functions](https://en.wikipedia.org/wiki/Cryptographic_hash_function) take an input of arbitrary length and produces a fixed length output. The special features are that the outputs are _deterministic_ (the same input always generates the same output) and yet the outputs are apparently “random” – two similar inputs are likely to produce very different outputs, and it's difficult to determine the input by looking at the ouput.

A common application of hashing is in storing passwords. Many systems store only the hash of a user's password along with their username. This ensures that even if someone gains access to the stored data, users' actual passwords are not exposed. When a user types in a password on such a system, the password handling software grants access if the hash value generated from the user's entry matches the hash stored in the password database.

We said above that it is _difficult_ to determine an input given an output. [Password cracking](https://en.wikipedia.org/wiki/Password_cracking) is a family of techniques for accomplishing this difficult (but possible!) task.
That is, let's say we have access to a user's password _hash_ only. Can we figure out their password? We could then use it to log in, and it may also be shared across their accounts which we could also access.

In some cases, password cracking can [exploit the structure](https://en.wikipedia.org/wiki/MD5#Security) of a hash function; this is a topic for a cryptography class. In our case, we will take a more brute-force approach: trying variations on existing known passwords, under the assumption that [many passwords are easy to guess](https://en.wikipedia.org/wiki/List_of_the_most_common_passwords).

## Getting Started

To get started, visit the [Github Classroom](https://classroom.github.com/a/m9ZLT8wD) assignment link. Select your username from the list (or if you don't see it, you can skip and use your Github username). A repository will be created for you to use for your work. This PA should be completed on the `ieng6` server. Refer [this](https://ucsd-cse29.github.io/wi26/week1/lab1.html#logging-into-ieng6) section in Week 1's Lab for instructions on logging in to your account on `ieng6` and working with files on the server.

**Note** - The autograder uses the C11 standard of the C programming language.

## Overall Task

We'll start by describing the overall task and goal so it's clear where you're going.
However, don't start by trying to implement this exactly – use the milestones below to get there.

### `pwcrack`, a Password Cracker

Write a program `pwcrack` that takes one command-line argument, the `SHA256` hash of a password in hex format.

The program then reads from `stdin` potential passwords, one per line (assumed to be in UTF-8 format).

The program should, for each password:

- Check if the SHA256 hash of the potential password matches the given hash
- Check if the SHA256 hash of the potential password with each of its ASCII characters
  uppercased or lowercased matches the given hash

If a matching password is found, the program should print the message below and then exit:

```
Found password: SHA256(<matching password>) = <hash>
```

If a matching password is _not_ found, the program should print:

```
Did not find a matching password
```

### Compiling Your Code

**On ieng6**

Because the OpenSSL libraries on ieng6 are not in the default library search path, you need to use this command:

```bash
gcc -L/usr/lib/x86_64-linux-gnu/ *.c -o pwcrack -lcrypto -lssl
```

The `-L` flag tells the compiler where to find the crypto libraries during linking.

**On Other Systems**

On most other Linux systems or macOS, you can compile with:

```bash
gcc *.c -o pwcrack -lcrypto
```

### Examples

`seCret` has a SHA256 hash of `a2c3b02cb22af83d6d1ead1d4e18d916599be7c2ef2f017169327df1f7c844fd`, and `notinlist`
has a SHA256 hash of `21d3162352fdd45e05d052398c1ddb2ca5e9fc0a13e534f3c183f9f5b2f4a041`

```
$ ./pwcrack a2c3b02cb22af83d6d1ead1d4e18d916599be7c2ef2f017169327df1f7c844fd
Password
NeverGuessMe!!
secret
Found password: SHA256(seCret) = a2c3b02cb22af83d6d1ead1d4e18d916599be7c2ef2f017169327df1f7c844fd
$ ./pwcrack 21d3162352fdd45e05d052398c1ddb2ca5e9fc0a13e534f3c183f9f5b2f4a041
Password
NeverGuessMe!!
secret
<Press Ctrl-D for end of input>
Did not find a matching password
```

We could also put the potential passwords in a file:

```
$ cat guesses.txt
Password
NeverGuessMe!!
secret
$ ./pwcrack a2c3b02cb22af83d6d1ead1d4e18d916599be7c2ef2f017169327df1f7c844fd < guesses.txt
Found password: SHA256(seCret) = a2c3b02cb22af83d6d1ead1d4e18d916599be7c2ef2f017169327df1f7c844fd
```

Note that we only consider single-character changes when trying
uppercase/lowercase variants of the guesses (i.e. we DON'T try all possible
capitalizations of the string): In the example below, the correct password is
NOT found because going from `SECRET` to `seCret` would require 5 characters to be changed.

```
$ ./pwcrack a2c3b02cb22af83d6d1ead1d4e18d916599be7c2ef2f017169327df1f7c844fd
SECRET
<Press Ctrl-D for end of input>
Did not find a matching password
```

## Design Questions

### Problem 1

The time command takes another command and reports how long it took to run. Use the time command on your password cracker for a password that will not match anything in the rockyou file (so it tests all of the passwords).

Show the output of the time command for your ./pwcrack on that input
Calculate (or use your program to count) the total number of times you called the SHA256 function and checked a hash against the input
How many password variants, on average, does your password cracker check per second?

### Problem 2

Consider this run of your password cracker:

```
$ ./pwcrack 5118f76d9067edc593d6946b88693cefa6604c7e613111193db118166d4af589
apple
alpaca
backpack
Found SHA256(Backpack) = 5118f76d9067edc593d6946b88693cefa6604c7e613111193db118166d4af589
```

At some point in the run, your password cracker should hash and check the string alPaca .

For that moment in the program, right when your program would call SHA256 on that string:

- Copy/paste your code into your answer
- What function calls are active in your program? That is, which function is currently executing? Which function was it called from? And so on, up to main .
- For each of those function calls, what are the values of the arguments?
- For each of those function calls, what are the values of all the local variables?

## What to Hand In

- Any .c files you wrote (can be one file or many; it's totally reasonable to only have one). We will compile your code, so you should make sure it works when we do that.
  You will hand in your code to the `pa2` assignment on Gradescope. An autograder will give you information about if your code compiles and works on some simple examples like the ones from this writeup.

- Submit your answers to the design questions on Gradescope under the assignment `PA2 Design Questions`.

## Fun (and Authentic!) Testing

To help testing your PA, we are providing you with a file containing 3 million real plaintext passwords famously found a data breach of the [RockYou
social network](https://en.wikipedia.org/wiki/RockYou) in 2009. You can use the password file present in the `ieng6` servers by reading it into `pwcrack` using
the following commandline:

```
$./pwcrack a2c3b02cb22af83d6d1ead1d4e18d916599be7c2ef2f017169327df1f7c844fd < /home/linux/ieng6/CSE29_WI26_A00/public/pa2/rockyou_clean.txt
```

Note: these are real human-generated passwords, so they may contain profane words (and offensive concepts). We are providing a
censored version of the RockYou password list. Our filtering methodology was to remove any passwords that matched a widely-used 2,800 profane
word list. If you read the contents of the password file, note that you are doing so at your own risk, as we can not guarantee that we removed
all offensive passwords from the list.

### Staff Passwords Scenario

You see in the news and on social media that there was a “data breach” of PrairieLearn, and the passwords of all instructors and TAs were exposed on the “dark web”. A classmate sends you a mysterious link that clearly contains usernames for the CSE29 staff and gibberish after each name.

[PrairieLearn Password Dump](https://raw.githubusercontent.com/ucsd-cse29/fa25/refs/heads/main/src/private/data/raw/sha/pw.txt)

Can you figure out the passwords of each of the staff members using your `pwcrack` program, the data at that link, and the rockyou dataset shared above?

Cracking these is ungraded, and just provided for fun and to get your attention with a provocative scenario where password cracking would be interesting (if unethical). They aren't our real passwords.

It also gives us a moment to discuss something important: just because you _can_ crack passwords doesn't mean you _should_. There are plenty of laws prohibiting the use of passwords that aren't yours to access data that isn't yours, regardless of how you obtained the password. Responsibility and ethics are another – it may simply be wrong to reverse-engineer (access to) someone else's private data, even if it happens to be legal. Of course, there are good uses for doing this – cracking can recover a lost password needed for access to critical data, for example, if the hash is available. Like any powerful tool, your knowledge of C programming and passwords should be used with care and appropriately in context!

In many cases, finding and reporting security issues is possible to do _responsibly_ – there's an entire theory and practice of [responsible disclosure](https://cheatsheetseries.owasp.org/cheatsheets/Vulnerability_Disclosure_Cheat_Sheet.html). [Researchers like Professor Aaron Schulman](https://www.wired.com/story/satellites-are-leaking-the-worlds-secrets-calls-texts-military-and-corporate-data/) do work on responsibly informing companies, governments, and the public about vulnerabilities in real-world systems. So it's critical to learn about how systems work, how secure systems fail, and how to navigate the surrounding ethical, legal, and social issues!

## Resources and Policy

Refer to [the policies on assignments](https://ucsd-cse29.github.io/wi26/#assignments-and-academic-integrity) for working with others or appropriate use of tools like ChatGPT or Github Copilot.

You can use any code from class, lab, or discussion in your work.
