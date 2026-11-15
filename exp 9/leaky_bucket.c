/**
 * Experiment No. 9: Traffic Shaping Algorithms
 * Program A: Leaky Bucket Algorithm Simulation in C
 * Description: Simulates open-loop congestion control via traffic shaping.
 *              Bursty incoming traffic is held in a finite-capacity buffer (bucket).
 *              Packets exceeding bucket capacity are discarded (overflow/loss).
 *              Packets are transmitted onto the network at a constant, uniform rate.
 */

#include <stdio.h>

int main() {
    int bucket_size, n, i, incoming, outgoing, stored = 0;

    printf("=========================================\n");
    printf("     Leaky Bucket Algorithm Simulation   \n");
    printf("=========================================\n");

    printf("Enter bucket size (capacity): ");
    if (scanf("%d", &bucket_size) != 1 || bucket_size <= 0) {
        printf("Invalid bucket size.\n");
        return 0;
    }

    printf("Enter outgoing rate (leak rate): ");
    if (scanf("%d", &outgoing) != 1 || outgoing <= 0) {
        printf("Invalid outgoing rate.\n");
        return 0;
    }

    printf("Enter number of time units: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid number of time units.\n");
        return 0;
    }

    for (i = 0; i < n; i++) {
        printf("\nTime unit %d:\n", i + 1);
        printf("Enter number of incoming packets: ");
        scanf("%d", &incoming);

        // Check for buffer overflow
        if (incoming + stored > bucket_size) {
            int dropped = incoming + stored - bucket_size;
            printf("Bucket overflow! Packet loss = %d\n", dropped);
            stored = bucket_size;
        } else {
            stored += incoming;
        }

        // Leak packets at a constant rate
        if (stored <= outgoing) {
            printf("Packets sent: %d\n", stored);
            stored = 0;
        } else {
            printf("Packets sent: %d\n", outgoing);
            stored -= outgoing;
        }

        printf("Packets remaining in bucket: %d\n", stored);
    }

    // Drain remaining packets in the bucket after incoming burst stops
    while (stored > 0) {
        printf("\nDraining remaining packets...\n");
        if (stored <= outgoing) {
            printf("Packets sent: %d\n", stored);
            stored = 0;
        } else {
            printf("Packets sent: %d\n", outgoing);
            stored -= outgoing;
        }
        printf("Packets left in bucket: %d\n", stored);
    }

    printf("\nSimulation complete.\n");
    return 0;
}

