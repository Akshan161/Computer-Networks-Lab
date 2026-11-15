/**
 * Experiment No. 4: Socket Programming for Transport Layer Packets (UDP Server)
 * Program: UDP Datagram Server
 * Description: A connectionless UDP server that binds to port 8080, receives
 *              datagram packets using recvfrom(), extracts client IP and port,
 *              and sends a datagram response back using sendto().
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define BUF_SIZE 1024

int main() {
    int server_socket;
    char buffer[BUF_SIZE];
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);

    // 1. Create UDP socket (SOCK_DGRAM)
    server_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (server_socket < 0) {
        perror("Socket creation failed");
        return 1;
    }

    // 2. Configure server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;   // Bind to any local IP
    server_addr.sin_port = htons(PORT);

    // 3. Bind socket to designated port
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(server_socket);
        return 1;
    }

    printf("UDP Server is running on port %d...\n", PORT);

    // 4. Receive datagram from client
    int n = recvfrom(server_socket, buffer, sizeof(buffer) - 1, 0,
                     (struct sockaddr *)&client_addr, &client_len);
    if (n < 0) {
        perror("Receive failed");
        close(server_socket);
        return 1;
    }
    buffer[n] = '\0';

    char client_ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &client_addr.sin_addr, client_ip, INET_ADDRSTRLEN);
    printf("Received datagram from %s:%d\n", client_ip, ntohs(client_addr.sin_port));
    printf("Message from Client: %s\n", buffer);

    // 5. Send datagram response back to client
    const char *response = "Hello from UDP Server";
    sendto(server_socket, response, strlen(response), 0,
           (struct sockaddr *)&client_addr, client_len);

    printf("Response sent back to client.\n");

    // 6. Close socket
    close(server_socket);
    return 0;
}

