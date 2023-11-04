/*
Assignment No. 5: 
Implement the C program for Deadlock Avoidance Algorithm:  Bankers Algorithm.
*/

#include <stdio.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

// Function to check if a given sequence is safe
int CheckSafe(int n, int m, int alloc[MAX_PROCESSES][MAX_RESOURCES], int max[MAX_PROCESSES][MAX_RESOURCES], int avail[MAX_RESOURCES]) {
    int ans[MAX_PROCESSES], finish[MAX_PROCESSES] = {0};
    int work[MAX_RESOURCES];

    for (int i = 0; i < m; i++) {
        work[i] = avail[i];
    }

    int count = 0;
    while (count < n) {
        int found = 0;
        for (int i = 0; i < n; i++) {
            if (finish[i] == 0) {
                int canAllocate = 1;
                for (int j = 0; j < m; j++) {
                    if (max[i][j] - alloc[i][j] > work[j]) {
                        canAllocate = 0;
                        break;
                    }
                }
                if (canAllocate) {
                    for (int j = 0; j < m; j++) {
                        work[j] += alloc[i][j];
                    }
                    ans[count] = i;
                    finish[i] = 1;
                    count++;
                    found = 1;
                }
            }
        }
        if (!found) {
            printf("The given sequence is not safe\n");
            return 0;
        }
    }

    printf("Following is the SAFE Sequence\n");
    for (int i = 0; i < n - 1; i++) {
        printf(" P%d ->", ans[i]);
    }
    printf(" P%d\n", ans[n - 1]);
    return 1;
}

// Function to request and allocate resources
int ResourceRequest(int n, int m, int alloc[MAX_PROCESSES][MAX_RESOURCES], int max[MAX_PROCESSES][MAX_RESOURCES], int avail[MAX_RESOURCES], int process) {
    int Req[MAX_RESOURCES];

    printf("Enter the resource request for process P%d:\n", process);
    for (int i = 0; i < m; i++) {
        scanf("%d", &Req[i]);
    }

    // Check if the request is valid
    int valid = 1;
    for (int j = 0; j < m; j++) {
        if (Req[j] > (max[process][j] - alloc[process][j]) || Req[j] > avail[j]) {
            valid = 0;
            break;
        }
    }
    if (valid) {
        // Changing the actual allocation
        for (int j = 0; j < m; j++) {
            alloc[process][j] += Req[j];
            avail[j] -= Req[j];
        }
        // Checking if the updated state is safe
        if (CheckSafe(n, m, alloc, max, avail)) {
            printf("RESOURCE REQUEST GRANTED\n");
            printf("Updated allocation matrix:\n");
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    printf("%d ", alloc[i][j]);
                }
                printf("\n");
            }
            return 1;
        } else {
            // The request is not safe, revert the changes
            for (int j = 0; j < m; j++) {
                alloc[process][j] -= Req[j];
                avail[j] += Req[j];
            }
        }
    }

    printf("Resource request denied. The request may not be safe.\n");
    return 0;
}

int main() {
    printf("STARTING WITH BANKER'S ALGORITHM\n");
    int n, m;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter the number of resources: ");
    scanf("%d", &m);

    int alloc[MAX_PROCESSES][MAX_RESOURCES];
    int max[MAX_PROCESSES][MAX_RESOURCES];
    int avail[MAX_RESOURCES];

    printf("Taking input allocation matrix for each process from the user:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("Enter for P%d, Resource R%d: ", i, j);
            scanf("%d", &alloc[i][j]);
        }
    }

    printf("Taking input max matrix for each process from the user:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("Enter for P%d, Resource R%d: ", i, j);
            scanf("%d", &max[i][j]);
        }
    }
    printf("Enter the number of available resources:\n");
    for (int i = 0; i < m; i++) {
        scanf("%d", &avail[i]); // Available Resources
    }

    CheckSafe(n, m, alloc, max, avail);

    while (1) {
        int process;
        printf("Enter the process that wants a resource request (0 to %d or -1 to exit): ", n - 1);
        scanf("%d", &process);

        if (process == -1) {
            break;
        }

        if (process < 0 || process >= n) {
            printf("Invalid process number.\n");
            continue;
        }

        if (ResourceRequest(n, m, alloc, max, avail, process)) {
            printf("Resource request granted.\n");
        } else {
            printf("Resource request denied.\n");
        }
    }

    return 0;
}
