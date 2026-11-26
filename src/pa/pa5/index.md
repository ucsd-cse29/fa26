# PA5 – Web Server Due Friday 12/4 10pm

- **Due Friday 12/4 10pm**
- [Classroom50](https://classroom50.org/ucsd-cse29-fall2026/cse29-fa26/assignments/pa5-web-server/accept)
<div class="important">

There is no resubmission available for PA5 (including the Design Questions) or Problem Set 5. Please plan your development and testing accordingly.

</div>

## Web Servers and HTTP

[HTTP](https://en.wikipedia.org/wiki/HTTP) is one of the most common protocols for communicating across computers. At the systems programming level, this means using system calls (usually in C) to tell the operating system to send bytes over a network.

One nice feature of HTTP is that it is a primarily text-based protocol, which makes it more straightforward for humans to read and debug. It is also well-understood by web browsers and programs like `curl`, making it easy to test and connect to user-facing devices.

It's useful to get experience with the format of HTTP, and with using system calls in C to manipulate HTTP requests.

Specifically, we will practice the following concepts in C:

- string manipulation,
- structs and memory management,
- process management using fork(), _exit(), and waitpid(), and of course,
- using the terminal and vim.

## Getting Started

The starter code for this assignment is hosted on Classroom50: TODO.
Just like on previous PAs, clone the repository to the ieng6 server. It's best to complete the PA on `ieng6`, because it gives a consistent testing environment for the live server.

- `http-server.c` and `http-server.h` are a library that handles the networking for you. It provides `start_server`, which listens on a port and calls a function you write once for every request. Treat it as a library: don't change it.
- `chat-server.c` has a `main` that starts the server on the port given on the command line, and an empty `handle_request` function where you start writing your server.
- The `Makefile` builds `chat-server.c` and `http-server.c` into `chat-server`. Run `make chat-server` to compile. The grader compiles with this `Makefile`, so put all of your server code in `chat-server.c`.
- `CREDITS.txt` is where you list the sources you used, such as people you discussed the PA with, websites, and AI tools.

## Task Specification

In this programming assignment, you'll write a C program to implement a chat room (think a plain-text version of [Slack](https://slack.com/) or [Discord](https://discord.com/)).

Your programs should compile and run with:

```bash
make chat-server
./chat-server <optional port number>
```

When the server starts with `./chat-server`, it should print a single message:

```bash
$ ./chat-server
Server started on port PPPPP
```

If a port number was provided, it should use that port, otherwise it should print an open port that was selected.

It should continue running, listening for requests on that port, until shutdown with Ctrl-c. After startup, it can print any other logging messages or other output needed to the terminal.

The requests the chat server listens for are described in this section:

### /chats

A request to `/chats` responds with the plain text rendering of all the chats.

The rendered chat format is

```
[#N 20XX-MM-DD HH:MM:SS] <username>: <message>
(<rusername>) <reaction>
... [more reactions] ...
... [more chats] ...
```

Chats must be rendered properly, as in Problem Set 5. You can put in whatever effort you like into lining things up nicely within these constraints, but these are the requirements.

Example chats rendering might look like:

```
[#1 2026-11-25 09:01:00]      harsha: hi aaron
[#2 2026-11-25 09:02:00]       aaron: whats up dude
[#3 2026-11-25 09:04:00]      harsha: working on the example chat for the PA
[#4 2026-11-25 09:06:00]       aaron: dude this is gonna be sick
[#5 2026-11-25 09:07:00]       aaron: what are you making it say?
[#6 2026-11-25 09:10:00]      harsha: idk we could go pretty meta with it? like an edited version of the chat about the chat?
[#7 2026-11-25 09:11:00]       aaron: eh at least the students will know this is not clanker generated
[#8 2026-11-25 09:12:00]      harsha: aight bet
[#9 2026-11-25 09:12:05]       aaron: dude this is lowkey gonna be fire this is so meta
                         (harsha)  🥀
[#10 2026-11-25 09:12:25]      harsha: sonion
```

### /post

A `post` request looks like this:

`/post?user=<username>&message=<message>`

This creates a new chat with the given username and message string with a timestamp given by the time the request is received by the server. It must respond with the list of all chats (including the new one).

Limits and constraints:

- If a parameter (username or message) is missing, respond with HTTP code 400 (Bad Request)
- If username is longer than 15 bytes, respond with HTTP code 400 (Bad Request)
- If message is longer than 255 bytes, respond with HTTP code 400 (Bad Request)
- If a post would make there be more than 100000 (one hundred thousand) chats, respond with HTTP code 500 (Internal Server Error)

[You might find this page useful here](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Status#client_error_responses).

### /react

`/react?user=<username>&message=<reaction>&id=<id>`

Creates a _new reaction_ to a chat by the given username with the given message string, reacting to the post with the given id (the ids are the `#N` at the beginning of posts). It must respond with the list of all chats (including the new one).

Limits and constraints:

- If the id is not the ID of some existing chat, respond with HTTP code 400 (Bad Request).
- If a parameter (username or message or id) is missing, respond with HTTP code 400 (Bad Request)
- If username is longer than 15 bytes, respond with HTTP code 400 (Bad Request)
- If message is longer than 15 bytes, respond with HTTP code 400 (Bad Request) – reactions are intended to be short!
- If a reaction would make a chat have more than 100 reactions, respond with HTTP code 500 (Internal Server Error)

### Other paths

A request for any other path (for example `/` or `/favicon.ico`) responds with HTTP code 404 (Not Found).

## Handling Requests in Child Processes

**Your server must send every response from a forked child process.** For each request:

1. The server process (the parent) parses the request and makes any change to the chats and reactions.
2. The parent then forks. The child writes the whole response to the client (the list of chats, or an error) and then calls `_exit()`. The child must not change the chats, and must never return from the handler.
3. The parent does not wait for the child. It returns from the handler right away so the server can accept the next request, which means several children can be sending responses at the same time.
4. Each time a new request comes in, before handling it, the parent reaps every child that has already finished, using `waitpid()`. It must not wait for children that are still running.

If `fork()` fails, print an error with `perror("fork")`, have the parent send the response itself, and keep running.

## Implementation Guide

This page is the entire _specification_ for the assignment; it's what you need to implement. You are free to make whatever choices you like in your code within these constraints. To help you on your way, we have some _implementation notes_ below with suggestions and ideas for how to get started and what to think about. These are not requirements, just suggestions!

First, make sure to do **Problem Set 5** first if you haven't already! While completing it you will create helper functions you can use as well as help you develop an understanding of your task.

Then, one way to break down the work the server needs to do is:

- Parsing and interpreting requests (is the request a new post, a reaction, etc)
- Updating the current data (chats and reactions) based on the parameters in the request
- Responding to requests based on the current state of the data (chats and reactions)

One way to work incrementally is to separate the _data handling_ and the
_request handling_ parts into different functions.

The _data handling_ functions can be tested by writing a `main` and using `printf` or `assert`, and the _request
handling_ can be tested with `curl` or a client.

We think the following functions might be useful for you to implement. In your
program you might have slightly different signatures or ideas, but these are a
useful starting point. Also, our staff is more familiar with this approach, so
it will take us less time to help you in office hours!

### Data Handling Functions

These functions can be written and tested without starting a server at all. You
could consider having a separate `main` function in its own file that just tests
these!

#### `add_chat`

A function `add_chat` can add a single chat.

```c
uint8_t add_chat(char* username, char* message)
```

This function might have several tasks:

1. Update the current `id`
2. Get the current timestamp
3. Create a new chat and fill in its username and message fields
4. As needed, allocate new space, put the new chat in heap memory, store a
   reference to it in an array, etc. depending on your specific representation of
   chats

This is testable by setting up initial states of chats and reactions, running
the function, and then using `assert` or `printf` on the results.

#### `add_reaction`

Similar to `add_chat`, this adds a single reaction:

```c
uint8_t add_reaction(char* username, char* message, char* id)
```

This function might have several tasks:

- Use the id to locate the chat that this reaction is for (and maybe return
  early with an error if the id is invalid/out of range)
- Create a new reaction and fill in its username and message fields
- Add the reaction to the chat struct somehow, maybe with newly allocated space,
  an added element or reference in an array, etc. depending on your specific representation of chats and reactions
- Update the count of reactions on the referenced chat

This is testable by setting up initial states of chats and reactions, running
the function, and then using `assert` or `printf` on the results.

### Request and Response Handling Functions

You will definitely need to write a function for handling responses. But the
work of handling individual responses can be broken up. One approach could be to
get the path and query parameter string from the request and check if its path
is `/post`, `/chats`, etc, then pass the string to other functions

#### `respond_with_chats`

```c
void respond_with_chats(int client)
```

This function is responsible for using `write` or `send` to send the response to
the client that made the request. It might include:

- Using `snprintf` to format strings with data from the timestamp or ids
- Calling `write(client, str, size)` on various strings (with the appropriate size) to directly send the data to the client

#### `handle_post`

```c
// path is a string like "/post?user=joe&message=hi"
void handle_post(char* path, int client)
```

This function can have several tasks:

- Use string functions to extract the username and message from the path
- Call `add_chat` to do the data update
- Fork a child that calls `respond_with_chats` to send the response, then `_exit()`s

#### `handle_reaction`

```c
// path is a string like "/react?user=joe&message=hi&id=3"
void handle_reaction(char* path, int client)
```

This function can have several tasks:

- Use string functions to extract the username, message, and id from the path
- Call `add_reaction` to do the data update
- Fork a child that calls `respond_with_chats` to send the response, then `_exit()`s

### Forking a Child to Respond

It may help to get your server working without `fork()` first, and add forking once requests and responses work.

When a process forks, the child gets its own _copy_ of the parent's memory. If the child added a chat, it would add it to its own copy, and the chat would be gone when the child exits; the parent would never see it. That's why all changes to the chats happen in the parent, before the fork. The child's copy holds exactly the chats that existed when it was forked, so it can take its time sending them while the parent goes on to handle new requests.

The child should never return from the handler. If it does, it goes back into the loop inside `start_server` and starts accepting requests too. Now there are two servers, each of which forks on the next request, and the number of processes keeps growing.

<div class="note">

`_exit()` is a syscall and works differently than `exit()`. While `_exit()` simply exits the program immediately, `exit()` on the other hand will both kill the process and flush the `stdout` buffer. What this means is, every child that has been forked will print the output that the parent printed but hasn't yet been flushed. If none of this makes sense, don't worry. Simply use `_exit()` and you will be okay.

</div>

After the parent forks, it returns from the handler, and `start_server` closes the parent's copy of the client socket. The child's copy stays open until the child exits.

In PA3, finished background programs were left as zombies. A server handles many requests, so here the children have to be reaped: each zombie takes up an entry in the process table, and once you reach your limit of processes on ieng6, `fork()` fails.

Calling `waitpid(pid, NULL, 0)` on the child right after forking would make the parent wait for every response to finish, which is what forking is meant to avoid. Instead, when the next request comes in, the parent can reap every child that has already finished before it handles the request:

```c
while (waitpid(-1, NULL, WNOHANG) > 0);
```

- `-1` means _any_ child, not one particular child.
- The `WNOHANG` option makes `waitpid` return right away instead of waiting: it reaps a child that has already finished and returns its pid, or returns 0 if none has finished yet. See `man 2 waitpid`.
- Several children may have finished since the last request, so the loop keeps calling `waitpid` until there are no more finished children to reap.

Children that finish after this are reaped when the following request comes in, so a few zombies may be left between requests. That's expected.

If you end up with stray servers, `ps -u $USER` lists your processes and `pkill chat-server` stops them.

## Representing Chats and Reactions

Chats and reactions both have multiple fields, so a natural choice is to
represent both chats and reactions as structs.

A chat has several components, which may be good candidates for struct fields:

- The message
- The username
- The timestamp
- The reactions to the message

A reaction has the message content and the user who posted it (no timestamp or
reactions-to-reactions), both of which are fixed-size.

You should make `struct`s to hold the `Chat`s and `Reaction`s in your server, and use the constraints above
about the lengths of usernames, messages, and so on to help you decide what data to store.

## Other Helpful Functions

This PA explores several features that are straightforward to use, but there are _many_ of them. We might add more to this list as the PA goes on! Here are a few functions you'll probably find useful; try `man` on them, or follow the links, or do your own searching and research. Don't forget all the functions from class (e.g. `malloc` and other allocation functions, `strstr` and other string manipulation functions, and so on).

- [`atoi`](https://cplusplus.com/reference/cstdlib/atoi/?kw=atoi): convert `char*` to integer

- **Time functions:**
  - [`time`](https://en.cppreference.com/w/c/chrono/time): get the current time
  - [`localtime`](https://en.cppreference.com/w/c/chrono/localtime): convert the time to the current local time zone
  - [`strftime`](https://en.cppreference.com/w/c/chrono/strftime): print the time in a given format

- **Process functions:** `fork` (`man 2 fork`), `_exit` (`man 2 _exit`), and `waitpid` (`man 2 waitpid`)

## Design Questions

We know from [Lab 7](https://ucsd-cse29.github.io/fa26/week7/index.html) that we can write `bash` scripts to automate running commands in loops. We know from this PA and the [Week 8 discussion](https://ucsd-cse29.github.io/fa26/disc/week8/cse-29-discussion-week-8.pdf) that we can use `curl` to make requests to our chat server from the command line. We also hear in the news that AI agents are pretty good at writing code.

Choose an AI agent (ChatGPT, Claude Code, Github Copilot, etc) and use it to generate a bash script for testing your chat server. Give it enough information about the specification to generate meaningful requests, and make sure it makes at least 1000 requests to your server.

In your response:

- Include relevant prompts and responses from the chat agent
- Include the bash script generated
- Show an example run of the bash script
- Discuss if it found any bugs in your implementation
- Discuss if you are more confident in your implementation as a result
- Discuss anything else you learned about bash scripting, programming, or URLs/servers as a result

## Submission

You'll submit your code to Gradescope as usual and submit your Design Question Answers on Gradescope. Refer to the [policies on collaboration](https://ucsd-cse29.github.io/fa26/#policies-and-perspective) if you need to
refresh your memory.

Fill in `CREDITS.txt` with attributions for the sources you used, such as people you discussed the PA with, websites, and AI tools.

**Important:** We will compile your program using the provided `Makefile`, which if you do change will not be used by the grader. 
