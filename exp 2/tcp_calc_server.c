/**
 * Experiment No. 2 (Extra Code): TCP Arithmetic Server
 * Description: Server receives two numbers from client, computes their sum
 *              using a helper function, and sends the result back.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 10279
#define BUF_SIZE 1024

// Parameterized calculation function
int add(int a, int b) {
    return a + b;
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUF_SIZE];
    int num1, num2;

    // 1. Create socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // 2. Prepare server address
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // 3. Bind
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // 4. Listen
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    printf("Server listening on port %d...\n", PORT);

    // 5. Accept connection
    new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
    if (new_socket < 0) {
        perror("Accept failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    while (1) {
        memset(buffer, 0, BUF_SIZE);
        int bytes = read(new_socket, buffer, BUF_SIZE - 1);
        if (bytes <= 0)
            break;

        sscanf(buffer, "%d %d", &num1, &num2);
        printf("Received Numbers: %d %d\n", num1, num2);

        int result = add(num1, num2);
        sprintf(buffer, "Sum = %d\n", result);

        send(new_socket, buffer, strlen(buffer), 0);
    }

    close(new_socket);
    close(server_fd);
    return 0;
}

