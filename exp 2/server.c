/**
 * Experiment No. 2: Socket Programming for Transport Layer Packets (TCP Server)
 * Program: TCP Echo Server
 * Description: A TCP server that performs passive open, binds to a designated port,
 *              listens for incoming client connections, accepts a connection,
 *              receives messages from the client, and echoes them back.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 10276      // Port number (10000 + last digits of roll/PRN or custom port)
#define BUF_SIZE 1024

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    char buffer[BUF_SIZE];
    int addrlen = sizeof(address);

    // 1. Create TCP socket (IPv4, Stream-based TCP)
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // 2. Prepare server address structure
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;   // Bind to all local interfaces
    address.sin_port = htons(PORT);         // Convert host byte order to network byte order

    // 3. Bind socket to the specified IP address and port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // 4. Listen for incoming client connections
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    printf("TCP Echo Server listening on port %d...\n", PORT);

    // 5. Accept client connection (completes 3-way handshake)
    new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
    if (new_socket < 0) {
        perror("Accept failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    char client_ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &address.sin_addr, client_ip, INET_ADDRSTRLEN);
    printf("Client connected from %s:%d\n", client_ip, ntohs(address.sin_port));

    // 6. Data Transfer: Read incoming stream and echo back
    while (1) {
        memset(buffer, 0, BUF_SIZE);
        int bytes = read(new_socket, buffer, BUF_SIZE - 1);
        if (bytes <= 0) {
            printf("Client disconnected or EOF reached.\n");
            break;
        }

        printf("Received: %s", buffer);

        // Echo the received message back to client
        send(new_socket, buffer, bytes, 0);
    }

    // 7. Close connected socket and listening socket
    close(new_socket);
    close(server_fd);
    printf("Server terminated gracefully.\n");

    return 0;
}

