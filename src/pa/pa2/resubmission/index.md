# PA2 - Hashing and Passwords: Resubmission Due 2/12 at 11:59pm

### If you want to resubmit PA2, please read this section carefully. You need to pass all the tests in the original PA2, while also implementing an extra functionality.

Implement `pwcrack` as originally described below. Also update `pwcrack` to check if the SHA256 hash of the potential password with each of its numeric digits `'0'-'9'` replaced by all possible numberic digits `'0'-'9'` (considering only single digit changes) matches the given hash.

As before, only one character change at a time is tested, so if `Secret111` is a potential password:

- This does NOT check `secret101` as it would combine changing the case of a character and replacing a digit
- `SeCreT111` is NOT a valid variation to check as it modifies the case of two characters at the same time
- `Secret123` is NOT a valid variation to check as it modifies two digits at the same time
- `secret111`, `Secret112`, `SecreT111`, etc. are some valid variations to hash and check for a match

For example,
`Secret112` has a SHA256 hash of `b54051d1abdba8656126f85f96d9270283d34b1cb8787b78c50646d9eb4a502d`

```
$ ./pwcrack b54051d1abdba8656126f85f96d9270283d34b1cb8787b78c50646d9eb4a502d
NeverGuessMe!!
Secret
Secret111
Found password: SHA256(Secret112) = b54051d1abdba8656126f85f96d9270283d34b1cb8787b78c50646d9eb4a502d
$ ./pwcrack b54051d1abdba8656126f85f96d9270283d34b1cb8787b78c50646d9eb4a502d
NeverGuessMe!!
secret
secret222
<Press Ctrl-D for end of input>
Did not find a matching password
```

### Design Question Resubmission

If you want to resubmit the design questions, we will be asking this updated design question in a new Gradescope assignment. Please submit a PDF or a Markdown file containing your answer to the following question:

Consider the following run of an updated `pwcrack` that follows the new requirements:

```
$ ./pwcrack b54051d1abdba8656126f85f96d9270283d34b1cb8787b78c50646d9eb4a502d
secret118
secret111
<Press Ctrl-D for end of input>
Did not find a matching password
```

Assume that it processes each potential password without any optimizations and does not store information from previous passwords it has checked. Answer the following questions:

- How many password variations were hashed and tested for a match?
- How many duplicate password variations were hashed and checked?
- What are ways you might change the implementation to avoid this repeated and redundant work?
