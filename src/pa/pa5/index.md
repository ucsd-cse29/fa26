# PA5 - Web Server

**Due Friday, March 13th, 11:59PM**

Github Classroom Assignment: [https://classroom.github.com/a/exV5tX-2](https://classroom.github.com/a/exV5tX-2)

**Important**: There is no resubmission available for Assignment 5 (Problem Set, Design Questions, and Programming Assignment). Please plan your development and testing accordingly. There will also be no hidden tests for PA5, so you will receive immediate feedback on your code.

## Web Servers and HTTP

[HTTP](https://en.wikipedia.org/wiki/HTTP) is one of the most common protocols for communicating across computers. At the systems programming level, this means using system calls (usually in C) to tell the operating system to send bytes over a network.

One nice feature of HTTP is that it is a primarily text-based protocol, which makes it more straightforward for humans to read and debug. It is also well-understood by web browsers and programs like `curl`, making it easy to test and connect to user-facing devices.

It's useful to get experience with the format of HTTP, and with using system calls in C to manipulate HTTP requests.

## Task – Chat Server

In this programming assignment, you'll write a C program to implement a chat room (think a plain-text version of [Slack](https://slack.com/) or [Discord](https://discord.com/)).

It's best to complete the PA on `ieng6`, because it gives a consistent testing environment for the live server.

Your programs should compile and run with:

```bash
make chat-server
./chat-server <optional port number>
```

The server should start with ./chat-server and print a single message:

```bash
$./chat-server
Server started on port PPPPP
```

If a port number was provided, it should use that port, otherwise it should print an open port that was selected.

It should continue running, listening for requests on that port, until shutdown with Ctrl-c. It can print any other logging messages or other output needed to the terminal.

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

Chats must be rendered properly, as in HW5.5. You can put in whatever effort you like into lining things up nicely within these constraints, but these are the requirements.

Example chats rendering might look like:

```
[#1 2025-11-06 09:01:00]         joe: hi aaron
[#2 2025-11-06 09:02:00]       aaron: sup
[#3 2025-11-06 09:04:00]         joe: working on the example chat for the PA
[#4 2025-11-06 09:06:00]       aaron: oh cool what should it say
[#5 2025-11-06 09:07:00]         joe: I dunno we could go pretty meta with it? like a chat about the chat
[#6 2025-11-06 09:10:00]       aaron: eh kinda lame tbh
[#7 2025-11-06 09:11:00]         joe: whatever I already wrote it, going with it as-is
[#8 2025-11-06 09:12:00]       aaron: ok but make sure we don't look like jerks
[#9 2025-11-06 09:12:05]       aaron: or at least not me
                            (joe)  👍🏻
[#10 2025-11-06 09:12:25]         joe: good talk
```

### /post

A `post` request looks like this:

`/post?user=<username>&message=<message>`

This creates a new chat with the given username and message string with a timestamp given by the time the request is received by the server. It must respond with the list of all chats (including the new one).

Limits and constraints:

- If a parameter (username or message) is missing, respond with some kind of error (HTTP code 400 or 500)
- If username is longer than 15 bytes, respond with some kind of error (HTTP code 400 or 500)
- If message is longer than 255 bytes, respond with some kind of error (HTTP code 400 or 500)
- If a post would make there be more than 100000 (one hundred thousand) chats, the server should respond with an error (HTTP code 404 or 500)

### /react

`/react?user=<username>&message=<reaction>&id=<id>`

Creates a _new reaction_ to a chat by the given username with the given message string, reacting to the post with the given id (the ids are the `#N` at the beginning of posts). It must respond with the list of all chats (including the new one).

Limits and constraints:

- If the id is not the ID of some existing chat, respond with some kind of error (HTTP code 400 or 500).
- If a parameter (username or message or id) is missing, respond with some kind of error (HTTP code 400 or 500)
- If username is longer than 15 bytes, respond with some kind of error (HTTP code 400 or 500)
- If message is longer than 15 bytes, respond with some kind of error (HTTP code 400 or 500) – reactions are intended to be short!
- If a reaction would make a chat have more than 100 reactions, the server should respond with an error (HTTP code 404 or 500)

## **Implementation Guide**

This page is the entire _specification_ for the assignment; it's what you need to implement. You are free to make whatever choices you like in your code within these constraints. To help you on your way, we have some _implementation notes_ below with suggestions and ideas for how to get started and what to think about. These are not requirements, just suggestions!

First, make sure to do **Problem Set 5** first if you haven't already! While completing it you will create helper functions you can use as well as help you develop an understanding of your task.

Then, one way to break down the work the server needs to do is:

- Parsing and interpreting requests (is the request a new post, a reaction, etc)
- Updating the current data (chats and reactions) based on the parameters in the request
- Responding to requests based on the current state of the data (chats and requests)

One way to work incrementally is to separate the _data handling_ and the
_request handling_ parts into different functions.

The _data handling_ functions can be tested with by writing a `main` and using `printf` or `assert`, and the _request
handling_ can be tested with `curl` or a client.

We think the following functions might be useful for you to implement. In your
program you might have slightly different signatures or ideas, but these are a
useful starting point. Also, our staff is more familiar with this approach, so
it will take us less time to help you in office hours!

### Data Handling Functions

These functions can be written and tested without starting a server at all. You
could consider having a separate `main` function in its own file that just tests
these!

#### **`add_chat`**

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

#### **`add_reaction`**

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
get the path and query parameter string from the request and check if it's path
is `/post`, `/chats`, etc, then pass the string to other functions

#### **`respond_with_chats`**

```c
void respond_with_chats(int client)
```

This function is reponsible for using `write` or `send` to send the response to
the client that made the request. It might include:

- Using `snprintf` to format strings with data from the timestamp or ids
- Calling `write(client, str, size)` on various strings (with the appropirate size) to directly send the data to the client

#### **`handle_post`**

```c
// path is a string like "/post?user=joe&message=hi"
void handle_post(char* path, int client)
```

This function can have several tasks:

- Use string functions to extract the username and message from the path
- Call `add_chat` to do the data update
- Call `respond_with_chats` to send the response

#### **`handle_reaction`**

```c
// path is a string like "/react?user=joe&message=hi&id=3"
void handle_reaction(char* path, int client)
```

This function can have several tasks:

- Use string functions to extract the username, message, and id from the path
- Call `add_reaction` to do the data update
- Call `respond_with_chats` to send the response

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

You should make `struct`s to hold the `Chat`s and `Reaction`s in your server, and use the constrains above
about the lengths of usernames, messages, and so on to help you decide what data to store.

## Other Helpful Functions

This PA explores several features that are straightforward to use, but there are _many_ of them. We might add more to this list as the PA goes on! Here are a few functions you'll probably find useful; try `man` on them, or follow the links, or do your own searching and research. Don't forget all the functions from class (e.g. `malloc` and other allocation functions, `strstr` and other string manipulation functions, and so on). This list is mainly focused on things we haven't tried in class.

- [`atoi`](https://cplusplus.com/reference/cstdlib/atoi/?kw=atoi): convert `char*` to integer

- **Time functions:**
  - [`time`](https://en.cppreference.com/w/c/chrono/time): get the current time
  - [`localtime`](https://en.cppreference.com/w/c/chrono/localtime): convert the time to the current local time zone
  - [`strftime`](https://en.cppreference.com/w/c/chrono/strftime): print the time in a given format

## Design Questions

We know from [lab 8](https://ucsd-cse29.github.io/wi26/week8/lab8.html) that we can write `bash` scripts to automate running commands in loops. We know from this PA and lab 9 that we can use `wget` and `curl` to make requests to our chat server from the command line. We also hear in the news that AI agents are pretty good at writing code.

Choose an AI agent (ChatGPT, Claude Code, Github Copilot, etc) and use it to generate a bash script for testing your chat server. Give it enough information about the specification to generate meaningful requests, and make sure it makes at least 1000 requests to your server.

In your response:

- Include relevant prompts and responses from the chat agent
- Include the bash script generated
- Show an example run of the bash script
- Discuss if it found any bugs in your implementation
- Discuss if you are more confident in your implementation as a result
- Discuss anything else you learned about bash scripting, programming, or URLs/servers as a result

## Handin

- Be sure to complete your Problem Set on PrairieLearn
- Submit a **PDF** with your Design Question Answers on Gradescope
- Submit your PA5 repository on Gradescope
- Make sure make chat-server builds your server (that's the command we will run), and the server runs on a predictable port with, for example, ./chat-server 8000
- Don't forget CREDITS.txt
- **Important**: There is no resubmission for this Assignment
- There are no hidden tests for this PA, so you can get immediate feedback on your code.
- Make sure to keep following good coding practices, including comments and style.
