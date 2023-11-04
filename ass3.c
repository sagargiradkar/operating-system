#include <stdio.h>

struct Table {
    int pid;
    int arrival_time;
    int burst_time;
    int temp_burst;
};

void BubbleSort(struct Table t[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (t[j].arrival_time > t[j + 1].arrival_time) {
                struct Table temp = t[j];
                t[j] = t[j + 1];
                t[j + 1] = temp;
            }
        }
    }
}

// Function for CPU Scheduling Algorithm: Round Robin
void roundRobin() {
    int n, time_quantum, ready_queue[50], g = 0, pick = 0;
    struct Table t[50];
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the information about process:-\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d:\nArrival Time: ", i + 1);
        scanf("%d", &t[i].arrival_time);
        printf("Burst Time: ");
        scanf("%d", &t[i].burst_time);
        t[i].temp_burst = t[i].burst_time;
        t[i].pid = i + 1;
    }
    printf("Enter the time quantum: ");
    scanf("%d", &time_quantum);
    int time = 0, p = n;
    float wait_time = 0, ta_time = 0;

    BubbleSort(t, n);

    int count = 0;
    while (t[count].arrival_time == t[0].arrival_time) {
        ready_queue[g] = count;
        g++;
        count++;
    }

    while (p > 0) {
        if (t[ready_queue[pick]].temp_burst <= time_quantum) {
            time = time + t[ready_queue[pick]].temp_burst;
            t[ready_queue[pick]].temp_burst = 0;
            ta_time = ta_time + time - t[ready_queue[pick]].arrival_time;
            wait_time = wait_time + time - t[ready_queue[pick]].arrival_time - t[ready_queue[pick]].burst_time;
            pick++;
            p--;
        } else {
            time = time + time_quantum;
            t[ready_queue[pick]].temp_burst = t[ready_queue[pick]].temp_burst - time_quantum;
            pick++;
        }
        while (count < n) {
            if (t[count].arrival_time <= time) {
                ready_queue[g] = count;
                g++;
                count++;
            } else {
                break;
            }
        }
        if (t[ready_queue[pick - 1]].temp_burst > 0) {
            ready_queue[g] = ready_queue[pick - 1];
            g++;
        }
    }

    printf("\nReady Queue:\n");
    for (int i = 0; i < g; i++) {
        printf("%d ", ready_queue[i]);
    }
    printf("\nAverage waiting time : %f\n", wait_time / n);
    printf("Average turn around time : %f\n", ta_time / n);
}

// Function for CPU Scheduling Algorithm: Shortest Job First
void shortestJobFirst() {
    int arrival_time[10], burst_time[10], temp[10];
    int i, smallest, count = 0, time, limit;
    double wait_time = 0, turnaround_time = 0, end;
    float average_waiting_time, average_turnaround_time;
    printf("Enter the Total Number of Processes: ");
    scanf("%d", &limit);
    printf("Enter Details of %d Processes:\n", limit);
    for (i = 0; i < limit; i++) {
        printf("Enter Arrival Time for Process %d: ", i + 1);
        scanf("%d", &arrival_time[i]);
        printf("Enter Burst Time for Process %d: ", i + 1);
        scanf("%d", &burst_time[i]);
        temp[i] = burst_time[i];
    }
    burst_time[9] = 9999;
    for (time = 0; count != limit; time++) {
        smallest = 9;
        for (i = 0; i < limit; i++) {
            if (arrival_time[i] <= time && burst_time[i] < burst_time[smallest] && burst_time[i] > 0) {
                smallest = i;
            }
        }
        burst_time[smallest]--;
        if (burst_time[smallest] == 0) {
            count++;
            end = time + 1;
            wait_time = wait_time + end - arrival_time[smallest] - temp[smallest];
            turnaround_time = turnaround_time + end - arrival_time[smallest];
        }
    }
    average_waiting_time = wait_time / limit;
    average_turnaround_time = turnaround_time / limit;
    printf("Average Waiting Time: %lf\n", average_waiting_time);
    printf("Average Turnaround Time: %lf\n", average_turnaround_time);
}

int main() {
    int choice;

    while (1) {
        printf("Menu:\n");
        printf("1. CPU Scheduling: Round Robin\n");
        printf("2. CPU Scheduling: Shortest Job First\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                roundRobin();
                break;
            case 2:
                shortestJobFirst();
                break;
            case 3:
                printf("Exiting the program. Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    }

    return 0;
}
