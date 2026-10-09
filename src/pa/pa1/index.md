# PA1 - UTF-8: Due Monday 10/12

Representing text is straightforward using ASCII: one byte per character fits well within `char[]` and it represents most English text. However, there are many more than 256 characters in the text we use, from non-Latin alphabets (Cyrillic, Arabic, and Chinese character sets, etc.) to emojis and other symbols like €, to accented characters like é and ü.

The [UTF-8 encoding](https://en.wikipedia.org/wiki/UTF-8#Encoding) is the default encoding of text in the majority of software today.
If you've opened a web page, read a text message, or sent an email [in the past 15 years](https://en.wikipedia.org/wiki/UTF-8#/media/File:Unicode_Web_growth.svg) that had any special characters, the text was probably UTF-8 encoded.

Not all software handles UTF-8 correctly! For example, Joe got a marketing email recently with a header “Take your notes further with Connectâ€‹” We're guessing that was supposed to be an ellipsis (…), [UTF-8 encoded as the three bytes 0x11100010 0x10000000 0x10100110](https://www.compart.com/en/unicode/U+2026), and likely the software used to author the email mishandled the encoding and treated it as [three extended ASCII characters](https://en.wikipedia.org/wiki/Extended_ASCII).

This can cause serious problems for real people. For example, people with accented letters in their names can run into issues with sign-in forms (check out [@yournameisinvalid](https://mas.to/@yournameisinvalid) for some examples). People with names best written in an alphabet other than Latin can have their names mangled in official documents, and need to have a "Latinized" version of their name for business in the US. Joe had trouble [writing lecture notes](https://x.com/JoePolitz/status/1841175066845069552) because LaTeX does not support UTF-8 by default.

UTF-8 bugs can and do cause security vulnerabities in products we use every day. A simple search for UTF-8 in the CVE database of security vulnerabilities turns up [hundreds of results](https://www.cve.org/CVERecord/SearchResults?query=utf-8).

It's useful to get some experience with UTF-8 so you understand how it's supposed to work and can recognize when it doesn't.
To that end, you'll write several functions that work with UTF-8 encoded text, and use them to analyze some example texts.

## Getting Started
### Step 1: Do the Prairielearn Problem Set #1
Before you start coding or doing the project, you need to do the Prairielearn: [Problem Set 1](https://us.prairielearn.com/pl/course_instance/221911/assessment_instance/15146553). You will incrementally build your full UTF-8 analyzer by doing this problem set. Then you will put everything together you built in the Problem Set into one complete program that will analyze UTF-8 strings.

### Step 2: Make your Git repository and begin coding

Visit this link to create your project Git repository: [Classroom50](https://classroom50.org/ucsd-cse29-fall2026/cse29-fa26/assignments/pa1/accept)

**Note:** Git is a command line tool used for managing source code that we will teach you to use in lab 2. You should commit and push all your code and changes to this repository.

## Milestones, Working Process, and Definitions


The functions described below are organized into milestones; you should definitely finish the functions in a milestone set before moving onto the next.

In general, you should work one function at a time, and earlier functions may be useful in implementing later functions.

A good first task is to implement *only* `is_ascii` and the corresponding part of `main` needed to read input and print the result for `is_ascii`, and make sure you can test that. Then move onto `capitalize_ascii`, and so on.

You can and should save your work by using `git` commits (if you're comfortable with that), or even just saving copies of your `.c` file when you hit important milestones. We may ask to see your work from an earlier milestone if you ask us for help on a function from a later one.

Some reminders and information about the function signatures:

- Your functions must have *exactly* the names and signatures shown below; we will test each of them individually. Incorrect function headers will lead to failed tests.
- `int8_t` and `int32_t` are 8-bit (1-byte) and 32-bit (4-byte) integers. You can think of `int32_t` like `int` in Java, we just want to be explicit about sizes of things when we program in C, and `int` can mean different things on different systems. These types are defined in `stdint.h`, so `#include <stdint.h>` at the top of a program will make them usable.
- Some functions take a *code point index* (which character, counting from 0) and some take a *byte index* (which byte in the `char[]`, counting from 0). For ASCII text these are the same, but for other text they are not! Pay attention to which one each function takes.

## Functions - Milestone 1


### `int8_t is_ascii(char string[])`

Takes a UTF-8 encoded string and returns if it is valid ASCII (e.g. all bytes are 127 or less). The empty string is valid ASCII.

#### Example Usage:
```
printf("Is 🔥 ASCII? %d\n", is_ascii("🔥"));

=== Output ===
Is 🔥 ASCII? 0

printf("Is abcd ASCII? %d\n", is_ascii("abcd"));

=== Output ===
Is abcd ASCII? 1
```

### `int32_t capitalize_ascii(char str[])`

Takes a UTF-8 encoded string and *changes* it in-place so that any ASCII lowercase characters `a`-`z` are changed to their uppercase versions. Leaves all other characters unchanged. It returns the number of characters updated from lowercase to uppercase.

#### Example Usage:
```
int32_t ret = 0;
char str[] = "abcd";
ret = capitalize_ascii(str);
printf("Capitalized String: %s\nCharacters updated: %d\n", str, ret);

=== Output ===
Capitalized String: ABCD
Characters updated: 4
```

## Functions - Milestone 2

### `int8_t codepoint_size(char string[])`

Takes a UTF-8 encoded string and returns how many bytes the *first* code point in it takes (start byte + continuation bytes): 1, 2, 3, or 4.

Returns 0 if the string is empty, and -1 if the first byte is not a valid start byte.

#### Example Usage:
```
printf("Size: %d bytes\n", codepoint_size("éclair")); // é is start byte 0xC3 + 1 cont. byte

=== Output ===
Size: 2 bytes

char s[] = "Héy"; // same as { 'H', 0xC3, 0xA9, 'y', 0 }
printf("Size: %d\n", codepoint_size(&s[2])); // the string starting at byte 2 starts with 0xA9, a continuation byte, not a start byte

=== Output ===
Size: -1
```

### `int32_t utf8_strlen(char str[])`

Takes a UTF-8 encoded string and returns the number of UTF-8 codepoints it represents.

Returns -1 if there are any errors encountered in processing the UTF-8 string.

#### Example Usage:
```
char str[] = "Joséph";
printf("Length of string %s is %d\n", str, utf8_strlen(str));  // 6 codepoints, (even though 7 bytes)

=== Output ===
Length of string Joséph is 6
```

### `void utf8_substring(const char str[], int start, int end, char result[])`

Takes a UTF-8 encoded string and start (inclusive) and end (exclusive) *code point* indices, and writes the substring between those indices to `result`, with a null terminator. Assumes that `result` has sufficient bytes of space available. (Hint: `result` will be created beforehand with a given size and passed as input here. Can any of the above functions be used to determine what the size of `result` should be?)

If the end index is larger than the `utf8_strlen` of the string, it should act as if the end index was exactly `utf8_strlen` of the string.

If `start` is negative, or `start` is greater than or equal to `end`, `result` should be the empty string.

#### Example Usage:
```
char str[] = "🦀🦮🦮🦀🦀🦮🦮"; // these emoji are 4 bytes long
char result[17];
utf8_substring(str, 3, 7, result);
printf("String: %s\nSubstring: %s\n", str, result);

=== Output ===
String: 🦀🦮🦮🦀🦀🦮🦮
Substring: 🦀🦀🦮🦮
```

## Functions - Milestone 3

### `int32_t codepoint_at(char str[], int32_t byte_index)`

Takes a UTF-8 encoded string and a *byte* index, and returns a decimal representing the codepoint of the character that starts at that byte.

Returns -1 if the byte at that index is not a valid start byte (for example, if it is a continuation byte) or is past the end of the string.

#### Example Usage:
```
char str[] = "Joséph"; // J o s é é p h
                       // 0 1 2 3 4 5 6  <- byte indices; é takes bytes 3 and 4
printf("Codepoint at byte 5 in %s is %d\n", str, codepoint_at(str, 5)); // 'p' starts at byte 5
printf("Codepoint at byte 3 in %s is %d\n", str, codepoint_at(str, 3)); // 'é' starts at byte 3
printf("Codepoint at byte 4 in %s is %d\n", str, codepoint_at(str, 4)); // byte 4 is the middle of 'é'

=== Output ===
Codepoint at byte 5 in Joséph is 112
Codepoint at byte 3 in Joséph is 233
Codepoint at byte 4 in Joséph is -1
```

### `int is_animal_emoji_at(const char str[], int index)`

Takes a UTF-8 encoded string and a *code point* index, and returns 1 if the code point at that index is an animal emoji, and 0 otherwise (including if the index is out of range).

For simplicity for this question, we will define that that the “animal emojii” are in two ranges: from 🐀 to 🐿️ and from 🦀 to 🦮. (Yes, this technically includes things like 🐽 which are only related to or part of an animal, and excludes a few things like 🙊, 😸, which are animal faces.). You may find the [wikipedia page on Unicode emoji](https://en.wikipedia.org/wiki/List_of_emojis) helpful here.

#### Example Usage:
```
char str[] = "I 🐶 you";
printf("%d %d\n", is_animal_emoji_at(str, 2), is_animal_emoji_at(str, 0)); // 🐶 is code point 2

=== Output ===
1 0
```



## UTF-8 Analyzer

You'll also write a program that reads UTF-8 input and prints out some information about it.

Here's what the output of a sample run of your program should look like:

```
$ ./utf8analyzer
Enter a UTF-8 encoded string: My 🐩’s name is Erdős.
Valid ASCII: false
Uppercased ASCII: "MY 🐩’S NAME IS ERDőS."
Length in bytes: 27
Number of code points: 21
Bytes per code point: 1 1 1 4 3 1 1 1 1 1 1 1 1 1 1 1 1 1 2 1 1
Substring of the first 6 code points: "My 🐩’s"
Code points as decimal numbers: 77 121 32 128041 8217 115 32 110 97 109 101 32 105 115 32 69 114 100 337 115 46
Animal emojis: 🐩
```

You can also test the contents of _files_ by using the `<` operator:

```
$ cat utf8test.txt
My 🐩’s name is Erdős.
$ ./utf8analyzer < utf8test.txt
Enter a UTF-8 encoded string: 
Valid ASCII: false
Uppercased ASCII: "MY 🐩’S NAME IS ERDőS."
Length in bytes: 27
Number of code points: 21
Bytes per code point: 1 1 1 4 3 1 1 1 1 1 1 1 1 1 1 1 1 1 2 1 1
Substring of the first 6 code points: "My 🐩’s"
Code points as decimal numbers: 77 121 32 128041 8217 115 32 110 97 109 101 32 105 115 32 69 114 100 337 115 46
Animal emojis: 🐩
```

## Testing

We provide 3 basic tests in the `tests` folder of your Classroom50 repository. These contain simple tests for identifying valid ASCII and converting ASCII lowercase characters to uppercase.

You can see the result for a single test by using:

```
./utf8analyzer < tests/utf8test.txt
```

Here are some other ideas for tests you should write. They aren't necessarily comprehensive (you should design your own!) but they should get you started. For each of these kinds of strings, you should check how UTF-8 analyzer handles them:

- Strings with a single UTF-8 character that is 1, 2, 3, 4 bytes
- Strings with two UTF-8 characters in all combinations of 1/2/3/4 bytes. (e.g. `"aa"`, `"aá"`, `"áa"`, `"áá"`, and so on)
- Strings with and without animal emojii, including at the beginning, middle, and end of the string, and at the beginning, middle, and end of the range
- Strings of exactly 5 characters

We recommend *saving your input in files* in the `tests` folder and using redirection (`<`) to test, so you don't have to figure out how to type the same UTF-8 characters over and over. Commit and push these test files to your repository along with your code.

## Design Questions

**The design questions are submitted separately from your code.** 

Answer each of these with a few sentences or paragraphs; don't write a whole essay, but use good writing practice to communicate the essence of the idea. A good response doesn't need to be long, but it needs to have attention to detail and be clear. Examples help!

**Question 1**

Consider these two bytes: `11000001 10000001`

Based on the definition of UTF-8 we used in PA1, what code point does it encode? What are 1-byte, 3-byte, and 4-byte encodings of the same code point? Which of these are valid UTF-8 encodings of this code point? Why are they valid or not valid? (This requires some outside research – "valid" is a technical term here)

Describe how you would write a function that detects if a UTF-8 string has any invalid code points like these.

**Question 2**

Consider a comparison of UTF-8 with the alternate encoding [UTF-32](https://en.wikipedia.org/wiki/UTF-32).

For a string `s` that is n+1 bytes long (n bytes of data with a 1-byte null terminator), `strlen(s)` must be equal to n.

- Is this property true for UTF-8? Explain why or give a counterexample.
- Is this property true for UTF-32? Explain why or give a counterexample.

For a string `s` that is n+1 bytes long (n bytes of data with a 1-byte null terminator) with the n bytes encoding 2c code points (that is, it is even length in terms of unicode characters), there is a valid code point starting at byte `s[n / 2]`.

- Is this property true for UTF-8? Explain why or give a counterexample.
- Is this property true for UTF-32? Explain why or give a counterexample.

*HINT*: Write out the UTF-8 and UTF-32 encoding of a few short strings, including characters in the ASCII range and outside it.

## Resources and Policy

Refer to [the policies on assignments](https://ucsd-cse29.github.io/fa26/#assignments-and-academic-integrity) for working with others or appropriate use of tools like ChatGPT or Github Copilot.

You can use any code from class, lab, or discussion in your work.

## What to Hand In

PA1 has **two separate Gradescope submissions**. You must complete both.

### 1. Code: the `Project 1 - Code` assignment on Gradescope

Your submission should contain:

- Any `.c` files you wrote (can be one file or many; it's totally reasonable to only have one). We will run `gcc *.c -o utf8analyzer` to compile your code, so you should make sure it works when we do that.
- Your tests in files `tests/*.txt`

To submit:

1. Make sure all of your work is committed and pushed to your Classroom50 repository (`git status` should show nothing left to commit, and your latest changes should be visible on GitHub).
2. Open the `Project 1 - Code` assignment on Gradescope and choose **GitHub** as the submission method. (The first time, you will need to connect your GitHub account to Gradescope.)
3. Select your repository, `ucsd-cse29-fall2026/cse29-fa26-pa1-<your GitHub username>`, and the `main` branch, then upload.

If your repository doesn't appear in the list on Gradescope, choose **Upload** instead and upload your `.c` files and your `tests` folder.

Pushing to your repository does **not** submit your assignment, even if Classroom50 shows the assignment as **Submitted**. Only what you submit on Gradescope before the deadline will be graded, so if you push more changes, submit again on Gradescope.

The submission system will show you the output of compiling and running your program on the provided tests to make sure the baseline format of your submission works. You will not get feedback about your overall grade before the deadline.

### 2. Design Questions: the `Project 1 - Design Questions` assignment on Gradescope

Type your answers to the [design questions](#design-questions) directly into the `Project 1 - Design Questions` assignment on Gradescope. Do **not** put them in your repository or your code submission; answers submitted there will not be graded.


===
