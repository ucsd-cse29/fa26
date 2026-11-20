
#include "http-server.h"


void start_server(void(*handler)(char*, int), int port) {
    int server_sock, client_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    

    // Create a socket
    if ((server_sock = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    int enable = 1; 
    if (setsockopt(server_sock, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)  
        perror("setsockopt(SO_REUSEADDR) failed");                                


    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);  
    socklen_t addr_len = sizeof(server_addr);
    if (bind(server_sock, (struct sockaddr *)&server_addr, addr_len) < 0) {
        perror("bind failed");
        close(server_sock);
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_sock, 10) < 0) {
        perror("listen failed");
        close(server_sock);
        exit(EXIT_FAILURE);
    }
    // get port number
    if (getsockname(server_sock, (struct sockaddr *)&server_addr, &addr_len) == -1) {
        perror("getsockname failed");
        exit(EXIT_FAILURE);
    }

    printf("Server started on port %d\n", ntohs(server_addr.sin_port));
    char buffer[BUFFER_SIZE];
    // Main server loop
    while (1) {
        if ((client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &client_len)) < 0) {
            perror("accept failed");
            close(server_sock);
            exit(EXIT_FAILURE);
        }

        // Receive the request
        int bytes = recv(client_sock, buffer, BUFFER_SIZE - 1, 0);
        if(bytes < 0) {printf("error receiving\n");close(client_sock);continue;}
        buffer[bytes] = '\0';  

        (*handler)(buffer, client_sock);

        // Close the connection with the client
        close(client_sock);
    }

    close(server_sock);
}
