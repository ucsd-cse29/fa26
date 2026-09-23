#include "http-server.h"
#include <string.h>

void handle(char *request, int client) {
    printf("Received request:\n%s\n", request);
}

int main() { start_server(&handle, 2900); }
