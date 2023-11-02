/*
Assignment No 5
Implement the C program for Deadlock Avoidance Algorithm: Bankers Algorithm.
*/
#include <iostream>
using namespace std;

bool CheckSafe(int n, int m, int alloc[10][10], int max[10][10], int avail[10]) {//SAFETY ALGORITHM
    int ans[n], finish[n];
    for (int i = 0; i < n; i++) {
        finish[i] = 0;
    }

    int work[3];
    for (int i = 0; i < 3; i++) {
        work[i] = avail[i];
    }

    int count = 0;
    while (count < n) {
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (finish[i] == 0) {
                bool canAllocate = true;
                for (int j = 0; j < m; j++) {
                    if (max[i][j] - alloc[i][j] > work[j]) {
                        canAllocate = false;
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
                    found = true;
                }
            }
        }
        if (!found) {
            cout << "The given sequence is not safe" << endl;
            return false;
        }
    }

    cout << "Following is the SAFE Sequence" << endl;
    for (int i = 0; i < n - 1; i++) {
        cout << " P" << ans[i] << " ->";
    }
    cout << " P" << ans[n - 1] << endl;
    return true;
}

bool ResourceRequest(int n, int m, int alloc[10][10], int max[10][10], int avail[10], int process) {// Resource Request Function
    int Req[3];
    cout << "Enter the resource request for process P" << process << ":\n";
    for (int i = 0; i < m; i++) {
        cin >> Req[i];
    }

    // Check if the request is valid
    bool valid = true;
    for (int j = 0; j < m; j++) {
        if (Req[j] > (max[process][j] - alloc[process][j]) || Req[j] > avail[j]) {
            valid = false;
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
            cout << "RESOURCE REQUEST GRANTED\n";
            cout << "Updated allocation matrix:\n";
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    cout << alloc[i][j] << " ";
                }
                cout << endl;
            }
            return true;
        } else {
            // The request is not safe, revert the changes
            for (int j = 0; j < m; j++) {
                alloc[process][j] -= Req[j];
                avail[j] += Req[j];
            }
        }
    }

    cout << "Resource request denied. The request may not be safe.\n";
    return false;
}

int main() {
    cout << "STARTING WITH BANKER'S ALGORITHM\n";
    int n, m, i, j, k, alloc[10][10], max[10][10], avail[10];

    n = 5; // Number of processes
    m = 3; // Number of resources

    cout << "Taking input allocation matrix for each process from the user:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << "Enter for [" << i << "][" << j << "]=";
            cin >> alloc[i][j];
            cout << "\n";
        }
    }

    cout << "Taking input max matrix for each process from the user:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << "Enter for [" << i << "][" << j << "]=";
            cin >> max[i][j];
            cout << "\n";
        }
    }
    cout << "Enter the number of available resources:\n";
    for (int i = 0; i < m; i++) {
        cin >> avail[i]; // Available Resources
    }

    CheckSafe(n, m, alloc, max, avail);

    while (true) {//Till user wants to enter the text
        int process;
        cout << "Enter the process that wants a resource request (0 to " << n - 1 << " or -1 to exit): ";
        cin >> process;

        if (process == -1) {
            break;
        }

        if (process < 0 || process >= n) {
            cout << "Invalid process number." << endl;
            continue;
        }

        if (ResourceRequest(n, m, alloc, max, avail, process)) {
            cout << "Resource request granted." << endl;
        } else {
            cout << "Resource request denied." << endl;
        }
    }

    return 0;
}

