#include "http-server.h"
#include <string.h>

char *HTTP_200 = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n";
char *HTTP_404 = "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\n";

void send_404(int client, char *message) {
    write(client, HTTP_404, strlen(HTTP_404));
    write(client, message, strlen(message));
}

#define MAX_STRINGS 100

char *strings[MAX_STRINGS];
int num_strings = 0;

void add_string(char *s) {
    if (num_strings >= MAX_STRINGS) { return; }
    strings[num_strings] = malloc(strlen(s) + 1);
    strcpy(strings[num_strings], s);
    num_strings++;
}

void respond_with_list(int client) {
    write(client, HTTP_200, strlen(HTTP_200));
    for (int i = 0; i < num_strings; i++) {
        write(client, strings[i], strlen(strings[i]));
        write(client, "\n", 1);
    }
}

void handle(char *request, int client) {
    char path[256];
    sscanf(request, "GET %s", path);

    if (strncmp(path, "/add", 4) == 0) {
        char *query_start = strstr(path, "?s=");
        if (query_start) {
            char *string_start = query_start + 3;
            add_string(string_start);
            respond_with_list(client);
        } else {
            send_404(client, "Missing ?s= parameter");
        }
    } else {
        send_404(client, "Unknown path");
    }
}

int main() { start_server(&handle, 2900); }
