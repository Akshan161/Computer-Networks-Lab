/**
 * Experiment No. 3 (Extra Code): TCP Arithmetic Client
 * Description: Client connects to arithmetic server, prompts user for two numbers,
 *              sends them to the server, and receives the computed sum.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 10279
#define BUF_SIZE 1024
#define SERVER_IP "127.0.0.1"   // Replace with server IP if on separate machine

int main() {
    int sock;
    struct sockaddr_in server_addr;
    char buffer[BUF_SIZE];
    int num1, num2;

    // 1. Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // 2. Prepare server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

    // 3. Connect to server
    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection to arithmetic server failed");
        close(sock);
        exit(EXIT_FAILURE);
    }
    printf("Connected to TCP Arithmetic Server.\n");

    while (1) {
        printf("Enter two numbers (or -1 -1 to quit): ");
        if (scanf("%d %d", &num1, &num2) != 2)
            break;

        if (num1 == -1 && num2 == -1)
            break;

        sprintf(buffer, "%d %d", num1, num2);
        send(sock, buffer, strlen(buffer), 0);

        memset(buffer, 0, BUF_SIZE);
        int bytes = read(sock, buffer, BUF_SIZE - 1);
        if (bytes <= 0) {
            printf("Server closed connection.\n");
            break;
        }

        printf("Server Response: %s", buffer);
    }

    close(sock);
    return 0;
}

