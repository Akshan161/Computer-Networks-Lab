/**
 * Experiment No. 9: Traffic Shaping Algorithms
 * Program B: Token Bucket Algorithm Simulation in C
 * Description: Simulates token-based traffic shaping where tokens accumulate
 *              at a fixed generation rate up to a maximum bucket capacity.
 *              Unlike Leaky Bucket, Token Bucket permits controlled bursts:
 *              packets can be transmitted immediately as long as tokens are available.
 */

#include <stdio.h>

int main() {
    int bucket_size, n, rate, tokens = 0, incoming, i;

    printf("=========================================\n");
    printf("     Token Bucket Algorithm Simulation   \n");
    printf("=========================================\n");

    printf("Enter bucket size (maximum token capacity): ");
    if (scanf("%d", &bucket_size) != 1 || bucket_size <= 0) {
        printf("Invalid bucket size.\n");
        return 0;
    }

    printf("Enter token generation rate (tokens/time unit): ");
    if (scanf("%d", &rate) != 1 || rate <= 0) {
        printf("Invalid token rate.\n");
        return 0;
    }

    printf("Enter number of time units: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid number of time units.\n");
        return 0;
    }

    for (i = 0; i < n; i++) {
        printf("\nTime unit %d:\n", i + 1);

        // Generate tokens at the fixed rate
        tokens += rate;
        if (tokens > bucket_size) {
            tokens = bucket_size; // Cap at bucket capacity
        }

        printf("Enter number of packets to send: ");
        scanf("%d", &incoming);

        // Check token availability to accommodate packet burst
        if (tokens >= incoming) {
            printf("Packets sent: %d\n", incoming);
            tokens -= incoming;
        } else {
            int sent = tokens;
            int dropped = incoming - tokens;
            printf("Only %d tokens available, packets sent: %d, packets dropped: %d\n",
                   tokens, sent, dropped);
            tokens = 0;
        }

        printf("Tokens left: %d\n", tokens);
    }

    printf("\nSimulation complete.\n");
    return 0;
}

