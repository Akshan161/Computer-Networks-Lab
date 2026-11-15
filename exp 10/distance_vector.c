/**
 * Experiment No. 10: Distance Vector Routing Algorithm
 * Program: Simulation of Distance Vector Routing Algorithm in C
 * Description: Uses the distributed Bellman-Ford algorithm to compute the shortest
 *              paths across network nodes. Each node maintains its routing table
 *              (Destination, Next Hop, Distance) and dynamically updates costs
 *              via neighbor vector exchange until full network convergence.
 */

#include <stdio.h>

#define MAX_NODES 10
#define INF 9999

struct Node {
    int dist[MAX_NODES];
    int from[MAX_NODES];
} rt[MAX_NODES];

int main() {
    int cost[MAX_NODES][MAX_NODES];
    int nodes, i, j, k;
    int updated, iteration;

    printf("=========================================\n");
    printf("   Distance Vector Routing Algorithm     \n");
    printf("=========================================\n");

    printf("Enter number of nodes: ");
    if (scanf("%d", &nodes) != 1 || nodes <= 0 || nodes > MAX_NODES) {
        printf("Invalid number of nodes.\n");
        return 0;
    }

    printf("Enter cost matrix row by row (use 999 for INF/no connection):\n");
    for (i = 0; i < nodes; i++) {
        for (j = 0; j < nodes; j++) {
            int v;
            scanf("%d", &v);
            if (v == 999) {
                cost[i][j] = INF;
            } else {
                cost[i][j] = v;
            }
        }
    }

    // 1. Initialize routing tables
    for (i = 0; i < nodes; i++) {
        cost[i][i] = 0;
        for (j = 0; j < nodes; j++) {
            rt[i].dist[j] = cost[i][j];
            if (cost[i][j] < INF && i != j) {
                rt[i].from[j] = j;  // Direct neighbor is next hop
            } else {
                rt[i].from[j] = (i == j) ? -1 : -1; // -1 for self or unreachable
            }
        }
    }

    // 2. Bellman-Ford Distance Vector Relaxation: repeat at most (nodes - 1) times
    for (iteration = 0; iteration < nodes - 1; iteration++) {
        updated = 0;
        for (i = 0; i < nodes; i++) {           // Source router i
            for (j = 0; j < nodes; j++) {       // Destination router j
                for (k = 0; k < nodes; k++) {   // Intermediate neighbor k
                    if (cost[i][k] >= INF) continue;       // No direct link from i to k
                    if (rt[k].dist[j] >= INF) continue;   // Node k has no route to j

                    // Bellman-Ford equation: D_x(y) = min_v { c(x,v) + D_v(y) }
                    int newdist = cost[i][k] + rt[k].dist[j];
                    if (newdist < rt[i].dist[j]) {
                        rt[i].dist[j] = newdist;
                        rt[i].from[j] = (rt[i].from[k] != -1) ? rt[i].from[k] : k;
                        updated = 1;
                    }
                }
            }
        }
        if (!updated) {
            break; // Convergence reached
        }
    }

    // 3. Display final converged routing tables
    for (i = 0; i < nodes; i++) {
        printf("\nRouting table for Node %d:\n", i);
        printf("Destination\tNext Hop\tDistance\n");
        printf("----------------------------------------\n");
        for (j = 0; j < nodes; j++) {
            if (rt[i].dist[j] >= INF) {
                printf("%d\t\t-\t\tINF\n", j);
            } else {
                printf("%d\t\t%d\t\t%d\n", j, rt[i].from[j], rt[i].dist[j]);
            }
        }
    }

    return 0;
}

