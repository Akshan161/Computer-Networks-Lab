/**
 * Experiment No. 8: Sliding Window Protocol (Go-Back-N)
 * Program: Simulation of the Sliding Window Protocol (Go-Back-N ARQ) using C
 * Description: Simulates flow and error control in data link / transport layer.
 *              The sender transmits up to window_size frames without waiting for ACKs.
 *              If an acknowledgment is received successfully (y), the window slides forward.
 *              If an error/loss occurs (n), the sender retransmits all frames starting
 *              from the unacknowledged base frame (Go-Back-N).
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_FRAMES 50

void sender(int frames[], int size, int window_size);
void receiver(int frames[], int start, int count);

int main() {
    int n, window_size;
    int frames[MAX_FRAMES];

    printf("========================================\n");
    printf("  Sliding Window Protocol (Go-Back-N)  \n");
    printf("========================================\n");

    printf("Enter number of frames to send (max %d): ", MAX_FRAMES);
    if (scanf("%d", &n) != 1 || n <= 0 || n > MAX_FRAMES) {
        printf("Invalid number of frames!\n");
        return 0;
    }

    printf("Enter window size: ");
    if (scanf("%d", &window_size) != 1 || window_size <= 0 || window_size > n) {
        printf("Invalid window size!\n");
        return 0;
    }

    // Initialize frame sequence numbers
    for (int i = 0; i < n; i++) {
        frames[i] = i; // Frame 0, 1, 2, ... (or i + 1)
    }

    printf("\nExperiment: Sliding Window Protocol\n");
    printf("Go-Back-N Protocol Simulation Started\n");

    sender(frames, n, window_size);

    return 0;
}

void sender(int frames[], int size, int window_size) {
    int base = 0;
    char choice;
    srand((unsigned int)time(NULL));

    while (base < size) {
        // Calculate number of frames in current window
        int current_window = window_size;
        if (base + current_window > size) {
            current_window = size - base;
        }

        // Display current sender window
        printf("\nSender window: ");
        for (int i = base; i < base + current_window; i++) {
            printf("[%d] ", frames[i]);
        }
        printf("\nSending frames...\n");
        for (int i = base; i < base + current_window; i++) {
            printf("Sent frame: %d\n", frames[i]);
        }

        // Simulate receiver
        printf("\nSimulating receiver...\n");
        receiver(frames, base, current_window);

        // Prompt user for ACK status (simulation of channel noise/error)
        printf("\nDid all frames receive correctly? (y/n): ");
        scanf(" %c", &choice);

        if (choice == 'y' || choice == 'Y') {
            // Window slides forward by the number of acknowledged frames
            base += current_window;
        } else {
            // Error occurred: Go-Back-N retransmission from base
            printf("Error detected! Resending from frame %d (Go-Back-N)...\n", frames[base]);
        }
    }

    printf("\nAll frames sent successfully!\n");
}

void receiver(int frames[], int start, int count) {
    for (int i = start; i < start + count; i++) {
        printf("Received frame: %d, sending ACK: %d\n", frames[i], frames[i] + 1);
    }
}

