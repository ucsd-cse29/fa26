# PA1 Resubmission: Due Date 1/29 at 11:59pm

## If you want to resubmit PA1, please read this section carefully. You need to pass all the tests in the original PA1, while also implementing an extra function described below

### `void next_utf8_char(char str[], int32_t cpi, char result[])`

Takes a UTF-8 encoded string and a code point index. Calculates the code point at that index. Then, calculates the code point with value one higher (so e.g. for ”é“ U+00E9 that would be “ê” (U+00EA), and for “🐩” (U+1F429) that would be “🐪” (U+1F42A)). Saves the encoding of that code point in the `result` array starting at index `0`.

#### Example Usage:

``` c
char str[] = "Joséph";
char result[100];
int32_t idx = 3;
next_utf8_char(str, idx, result);
printf("Next character of code point at index 3: %s\n",result);
// 'é' is the 4th codepoint represented by the bytes 0xC3 0xA9
// 'ê' in UTF-8 hex bytes is represented as 0xC3 0xAA

=== Output ===
Next character of code point at index 3: ê
```

Now, Your final output on running the `utfanalyzer` code that will be graded should contain this extra line:

```
Next character of code point at index 3: <FILL>
```

**Note:** If the number of codepoints in the input string _is less than 4_, this added line would only have the prompt _without any character_ as follows:

```
Next character of code point at index 3: 
```

The complete program output for example, should look like:

```
$ ./utf8analyzer
Enter a UTF-8 encoded string: My 🐩’s name is Erdős.
Valid ASCII: false
Uppercased ASCII: "MY 🐩’S NAME IS ERDőS."
Length in bytes: 27
Number of code points: 21
Bytes per code point: 1 1 1 4 3 1 1 1 1 1 1 1 1 1 1 1 1 1 2 1 1
Substring of the first 6 code points: My 🐩’s
Code points as decimal numbers: 77 121 32 128041 8217 115 32 110 97 109 101 32 105 115 32 69 114 100 337 115 46
Animal emojis: 🐩
Next character of code point at index 3: 🐪
```

(All our tests will check for this newly added line, in addition to lines from the original PA)

### Design Question Resubmission

If you want to resubmit the design questions, we will be asking this updated design question in a new Gradescope assignment:

- UTF-8 has a leading `10` on all the bytes past the first for multi-byte code points. This seems wasteful – if the encoding for 3 bytes were instead `1110XXXX XXXXXXXX XXXXXXXX` (where `X` can be any bit), that would fit 20 bits, which is over a million code points worth of space, removing the need for a 4-byte encoding. What are some tradeoffs or reasons the leading `10` might be useful? Can you think of anything that could go wrong with some programs if the encoding didn't include this restriction on multi-byte code points?
