/**
 * Experiment No. 3: Socket Programming for Transport Layer Packets (TCP Client)
 * Program: TCP Echo Client
 * Description: An active TCP client that creates a socket, initiates the TCP 3-way
 *              handshake using connect(), sends user-entered strings to the server,
 *              reads the echoed response, and displays it on the terminal.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 10276      // Must match the server port
#define BUF_SIZE 1024
#define SERVER_IP "127.0.0.1"   // Replace with server IP (e.g., 10.17.60.51) if running across nodes

int main() {
    int sock;
    struct sockaddr_in server_addr;
    char buffer[BUF_SIZE];

    // 1. Create client socket (IPv4, TCP Stream)
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // 2. Prepare server address configuration
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);

    // Convert IPv4 address from text to binary form
    if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) <= 0) {
        perror("Invalid address or address not supported");
        close(sock);
        exit(EXIT_FAILURE);
    }

    // 3. Connect to server (initiates TCP 3-way handshake: SYN -> SYN-ACK -> ACK)
    printf("Connecting to TCP Server at %s:%d...\n", SERVER_IP, PORT);
    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection to server failed");
        close(sock);
        exit(EXIT_FAILURE);
    }
    printf("Successfully connected to TCP Server!\nType 'exit' to terminate.\n\n");

    // 4. Data Transfer Loop
    while (1) {
        printf("Enter message: ");
        if (!fgets(buffer, BUF_SIZE, stdin)) {
            break;
        }

        // Check if user requested termination
        if (strncmp(buffer, "exit", 4) == 0) {
            printf("Closing client connection...\n");
            break;
        }

        // Send message to server
        send(sock, buffer, strlen(buffer), 0);

        // Receive echoed message back from server
        memset(buffer, 0, BUF_SIZE);
        int bytes = read(sock, buffer, BUF_SIZE - 1);
        if (bytes <= 0) {
            printf("Server closed connection.\n");
            break;
        }

        printf("Echo from server: %s", buffer);
    }

    // 5. Gracefully close socket descriptor
    close(sock);
    return 0;
}

