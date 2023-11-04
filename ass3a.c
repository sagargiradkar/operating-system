/*
Assignment No.3 A
Implement the C program for CPU Scheduling Algorithms:Round Robin with different arrival time.
*/
#include <stdio.h>
struct Table
{
    int pid;
    int arrival_time;
    int burst_time;
    int temp_burst;
};

void BubbleSort(struct Table t[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (t[j].arrival_time > t[j + 1].arrival_time)
            {
                struct Table temp = t[j];
                t[j] = t[j + 1];
                t[j + 1] = temp;
            }
        }
    }
}

int main()
{
    int n, time_quantum, ready_queue[50], g = 0, pick = 0;
    struct Table t[50];
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the information about process:-\n");
    for (int i = 0; i < n; i++)
    {
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
    while (t[count].arrival_time == t[0].arrival_time)
    {
        ready_queue[g] = count;
        g++;
        count++;
    }

    while (p > 0)
    {
        if (t[ready_queue[pick]].temp_burst <= time_quantum)
        {
            time = time + t[ready_queue[pick]].temp_burst;
            t[ready_queue[pick]].temp_burst = 0;
            ta_time = ta_time + time - t[ready_queue[pick]].arrival_time;
            wait_time = wait_time + time - t[ready_queue[pick]].arrival_time - t[ready_queue[pick]].burst_time;
            pick++;
            p--;
        }
        else
        {
            time = time + time_quantum;
            t[ready_queue[pick]].temp_burst = t[ready_queue[pick]].temp_burst - time_quantum;
            pick++;
        }
        while (count < n)
        {
            if (t[count].arrival_time <= time)
            {
                ready_queue[g] = count;
                g++;
                count++;
            }
            else
            {
                break;
            }
        }
        if (t[ready_queue[pick - 1]].temp_burst > 0)
        {
            ready_queue[g] = ready_queue[pick - 1];
            g++;
        }
    }

    printf("\nReady Queue:\n");
    for (int i = 0; i < g; i++)
    {
        printf("%d ", ready_queue[i]);
    }
    printf("\nAverage waiting time : %f", wait_time / n);
    printf("\nAverage turn around time : %f", ta_time / n);
    printf("\n");
}