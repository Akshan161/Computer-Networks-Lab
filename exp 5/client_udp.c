/**
 * Experiment No. 5: Socket Programming for Transport Layer Packets (UDP Client)
 * Program: UDP Datagram Client
 * Description: An active UDP client that creates a SOCK_DGRAM socket, prompts
 *              the user for a message, transmits the packet to the server's IP
 *              and port via sendto(), receives the reply using recvfrom(), and
 *              displays the server's response.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_PORT 8080
#define SERVER_IP "127.0.0.1"   // Replace with server IP if on separate machine
#define BUF_SIZE 1024

int main() {
    int sockfd;
    char message[BUF_SIZE], buffer[BUF_SIZE];
    struct sockaddr_in serverAddr;
    socklen_t addr_size;

    // 1. Create UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        return 1;
    }

    // 2. Configure target server address
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(SERVER_PORT);
    serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);

    // 3. User input
    printf("Enter message: ");
    if (!fgets(message, sizeof(message), stdin)) {
        close(sockfd);
        return 0;
    }

    // Strip trailing newline
    message[strcspn(message, "\r\n")] = 0;

    // 4. Send datagram to server (no connect() call required)
    sendto(sockfd, message, strlen(message), 0,
           (struct sockaddr *)&serverAddr, sizeof(serverAddr));

    // 5. Receive response from server
    addr_size = sizeof(serverAddr);
    int n = recvfrom(sockfd, buffer, sizeof(buffer) - 1, 0,
                     (struct sockaddr *)&serverAddr, &addr_size);
    if (n < 0) {
        perror("recvfrom failed");
        close(sockfd);
        return 1;
    }
    buffer[n] = '\0';

    printf("Server Response: %s\n", buffer);

    // 6. Close socket
    close(sockfd);
    return 0;
}

