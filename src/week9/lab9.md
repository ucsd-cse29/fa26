# Lab 9 Reference Document

(Accept and clone the github classroom assignment at [this link](https://classroom.github.com/a/ZmTX8Qt7))

## Part 1 - Connecting to the chat server

Run `./chat-client NAME HOST PORT`

Connect to the host and port of the chat server being run by your lab TA. Try sending some chats, and reacting to some messages.

Try sending HTTP requests directly by putting the following urls into your browser (after changing the uppercased portions)

- http://ieng6-201.ucsd.edu:PORT/chats
- http://ieng6-201.ucsd.edu:PORT/post?user=NAME&message=MESSAGE
- http://ieng6-201.ucsd.edu:PORT/react?user=NAME&message=MESSAGE&id=ID

You can also make requests from the terminal using `curl “URL”`

- you may need to put quotes around the url if it contains special characters like = or &
- using the -v option will show extra info like request and response headers.
- Connecting to the special hostname “localhost” will connect to the computer you are currently on, useful for testing your own servers

## Part 2: Basic Server

### Basic Server

- Modify handle_request in main.c to print incoming requests to the terminal,
- Connect to your and your groupmates server using curl and your browser (does a phone browser work?)

### Responses

- Send a response back to whoever made the request by using the send function on the client_socket that was given to you.
  `send(client_socket, message, size, 0);`

You’ll have to first send an appropriate HTTP response header, then send the body of the response.

```
HTTP/1.1 200 OK
Content-Type: text/plain

... body of response ...
```

(remember, the ends of lines in HTTP are `"\r\n"`, not just `"\n"`, and there has to be one blank line before the body of the response to mark that the headers have ended)

### Some useful string methods

`snprintf(buffer, sizeof(buffer), “format string %d”, 5);`
like printf, but writes the formatted string to buffer, useful for formatting responses before you send them

`sscanf(str, “number=%d”, &x);`
uses similar format strings to printf, but can parse numbers out of a string like “number=12”.

`strstr(s, substr)`
find substring in a larger string

## Part 3 - Number Server

Add a global variable int num to your server.

Make your server handle the following paths:
(You can also make the responses fancier if you like)

- `/shownum`

  - responds with the current value of num.

- `/increment`

  - adds one to num, responds with the new value of num.

- `/add?value=NNN`
  - adds value encoded in NNN (a decimal integer) to num
    responds with the new value of num

## Pokemon Mailtime
If you would like to finish the week8 lab on bash scripting, which includes Pokemon mailtime, you are welcome to do that.

Your lab checkoff will be due Tuesday week 10 @11am.

### Work Check-Off

Commit and push your number server  
Fill out the [Lab Survey](https://forms.gle/Jn6pEr2MPxGbaB8w8)

### Bonus

If you’re done early, you can use curl to add custom headers to your http request with `curl -H “SomeHeader: SomeValue” ... `. Modify your number server to detect the custom header “SetNumber: NN” and set the number accordingly. (NOTE: this isn’t a defined HTTP header, but it should work fine for this lab)
