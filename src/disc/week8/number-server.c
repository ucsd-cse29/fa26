#include "http-server.h"
#include <string.h>

char const* HTTP_200_OK = "HTTP/1.1 200 OK\nContent-Type: text/plain\n\n";
char const* HTTP_404_NOT_FOUND = "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\n404 Not Found\n";

int num = 0;

// Function to parse the HTTP request
// Returns 1 if the request is valid, 0 otherwise
uint8_t parse_http_request(char *request, char *url) {
    char method[10], version[10], host[256];
    char content_type[50];
    int content_length = 0;

    // Parse the request line (method, URL, HTTP version)
    if (sscanf(request, "%s %s %s", method, url, version) != 3) {
        printf("Invalid request line\n");
        return 0;
    }

    // printf("Method: %s\n", method);
    // printf("URL: %s\n", url);
    // printf("Version: %s\n", version);

    // Move the pointer to start parsing the headers
    char *headers = strstr(request, "\r\n") + 2;

    // Parse headers
    while (strncmp(headers, "\r\n", 2) != 0) {
        if (sscanf(headers, "Host: %s", host) == 1) {
            printf("Host: %s\n", host);
        } else if (sscanf(headers, "Content-Type: %s", content_type) == 1) {
            printf("Content-Type: %s\n", content_type);
        } else if (sscanf(headers, "Content-Length: %d", &content_length) == 1) {
            printf("Content-Length: %d\n", content_length);
        }

        // next header
        headers = strstr(headers, "\r\n") + 2;
    }

    // Validate the method (only GET)
    if (strcmp(method, "GET") != 0) {
        printf("Invalid HTTP method: %s\n", method);
        return 0;
    }

    // Check if Host header is present
    if (strlen(host) == 0) {
        printf("Missing Host header\n");
        return 0;
    }

    // If Content-Length is provided, validate the body
    if (content_length > 0) {
        char *body = strstr(headers, "\r\n\r\n") + 4; // Move past headers
        if ((int)strlen(body) < content_length) {
            printf("Content-Length does not match body size\n");
            return 0;
        }
        printf("Body: %s\n", body);
    }

    return 1;
}

void handle_shownum(int client_sock) {
    char response[BUFFER_SIZE];
    strncpy(response, HTTP_200_OK, sizeof(response)-1);
    char line[BUFFER_SIZE];
    snprintf(line, sizeof(line), "Number: %d\n", num);
    strcat(response, line);
    printf("%s", response);
    write(client_sock, response, strlen(response));
}

void handle_increment(int client_sock) {
    char response[BUFFER_SIZE];
    strncpy(response, HTTP_200_OK, sizeof(response)-1);
    num += 1;
    char line[BUFFER_SIZE];
    snprintf(line, sizeof(line), "Number incremented!\n");
    strcat(response, line);
    write(client_sock, response, strlen(response));
}

void handle_add(int client_sock, char *query) {
    char response[BUFFER_SIZE];

    // check whether query param is present
    if (strstr(query, "value=") == NULL) {
        fprintf(stderr, "Error: Missing value parameter.\n");
        send(client_sock, HTTP_404_NOT_FOUND, strlen(HTTP_404_NOT_FOUND), 0);
    }
    strncpy(response, HTTP_200_OK, sizeof(response)-1);
    int add_num;
    sscanf(query, "value=%d", &add_num);
    num += add_num;
    char line[BUFFER_SIZE];
    snprintf(line, sizeof(line), "Adding %d to the number. The number is now %d\n", add_num, num);
    strcat(response, line);
    write(client_sock, response, strlen(response));
}

void handle_response(char *request, int client_sock) {
    char url[256], query[256];

    if (!parse_http_request(request, url)) {
        printf("Invalid request header\n");
        return;
    }

    // show number path
    if (strncmp(url, "/shownum", 8) == 0) {
        handle_shownum(client_sock);
    } else if (strncmp(url, "/increment", 10) == 0) {
        handle_increment(client_sock);
    } else if (strncmp(url, "/add", 4) == 0) {
        strcpy(query, strchr(url, '?') + 1);
        handle_add(client_sock, query);
    } else {
        send(client_sock, HTTP_404_NOT_FOUND, strlen(HTTP_404_NOT_FOUND), 0);
    }
}

int main(int argc, char *argv[]) {
    int port = 0;
    if(argc >= 2) {
        port = atoi(argv[1]);
    }
    printf("FLAG = \"Networking is cool!\"\n");
    start_server(&handle_response, port);
}
