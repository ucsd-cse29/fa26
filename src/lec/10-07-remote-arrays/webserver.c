/*
 * A tiny HTTP server for Linux.
 *
 * Compile: cc -Wall -Wextra -O2 webserver.c -o webserver
 * Run:     sudo ./webserver     (port 80 normally requires root privileges)
 */

#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

static const char PAGE[] =
    "<!doctype html>\n"
    "<html>\n"
    "  <head><title>Tiny C Web Server</title></head>\n"
    "  <body><h1>Hello from my C web server!</h1></body>\n"
    "</html>\n";

static int send_all(int socket_fd, const char *data, size_t length)
{
    while (length > 0) {
        ssize_t sent = send(socket_fd, data, length, 0);

        if (sent < 0) {
            if (errno == EINTR)
                continue;
            return -1;
        }

        data += sent;
        length -= (size_t)sent;
    }

    return 0;
}

int main(void)
{
    const int port = 80;
    int server_fd;
    int reuse_address = 1;
    struct sockaddr_in address;

    /* Do not terminate if a browser disconnects while we are responding. */
    signal(SIGPIPE, SIG_IGN);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("socket");
        return 1;
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR,
                   &reuse_address, sizeof(reuse_address)) < 0) {
        perror("setsockopt");
        close(server_fd);
        return 1;
    }

    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port = htons((unsigned short)port);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind");
        close(server_fd);
        return 1;
    }

    if (listen(server_fd, 10) < 0) {
        perror("listen");
        close(server_fd);
        return 1;
    }

    printf("Listening on http://localhost:%d\n", port);

    for (;;) {
        struct sockaddr_in client_address;
        socklen_t client_address_length = sizeof(client_address);
        char client_ip[INET_ADDRSTRLEN];
        int client_fd = accept(server_fd, (struct sockaddr *)&client_address,
                               &client_address_length);
        char request[1024];
        char header[256];
        int header_length;

        if (client_fd < 0) {
            if (errno == EINTR)
                continue;
            perror("accept");
            break;
        }

        if (inet_ntop(AF_INET, &client_address.sin_addr,
                      client_ip, sizeof(client_ip)) != NULL) {
            printf("Client connected: %s\n", client_ip);
            fflush(stdout);
        } else {
            perror("inet_ntop");
        }

        /* Read enough to consume the browser's initial request. */
        if (recv(client_fd, request, sizeof(request), 0) < 0)
            perror("recv");

        header_length = snprintf(
            header, sizeof(header),
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/html; charset=utf-8\r\n"
            "Content-Length: %zu\r\n"
            "Connection: close\r\n"
            "\r\n",
            strlen(PAGE));

        if (header_length > 0 && (size_t)header_length < sizeof(header)) {
            if (send_all(client_fd, header, (size_t)header_length) == 0)
                send_all(client_fd, PAGE, strlen(PAGE));
        }

        close(client_fd);
    }

    close(server_fd);
    return 1;
}

