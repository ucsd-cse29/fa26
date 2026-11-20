#include "http-server.h"
#include <string.h>

char *HTTP_200 = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n";

void handle(char *request, int client) {
    printf("Received request:\n%s\n", request);
    write(client, HTTP_200, strlen(HTTP_200));
    write(client, "Hello!", 6);
}

int main() { start_server(&handle, 2900); }
