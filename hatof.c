#include <stdio.h>

// Structure for a process
struct Process {
    int pid;    // Process ID
    int bt;     // Burst Time
    int art;    // Arrival Time
    int wt;     // Waiting Time
    int tat;    // Turnaround Time
    int rt;     // Remaining Time
};

// Function to calculate waiting time and turnaround time of each process
void findWaitingTime(struct Process proc[], int n) {
    int currentTime = 0, complete = 0, shortest = 0;
    int minRemTime = 9999, check = 0;

    while (complete != n) {
        // Find process with minimum remaining time at current time
        minRemTime = 9999;
        check = 0;
        for (int i = 0; i < n; i++) {
            if (proc[i].art <= currentTime && proc[i].rt < minRemTime && proc[i].rt > 0) {
                shortest = i;
                minRemTime = proc[i].rt;
                check = 1;
            }
        }

        // If no process found, move to next second
        if (check == 0) {
            currentTime++;
            continue;
        }

        // Decrement remaining time of the selected process
        proc[shortest].rt--;

        // If process is completed
        if (proc[shortest].rt == 0) {
            complete++;

            // Calculate waiting time and turnaround time
            proc[shortest].wt = currentTime - proc[shortest].bt - proc[shortest].art;
            if (proc[shortest].wt < 0) {
                proc[shortest].wt = 0;
            }
            proc[shortest].tat = currentTime - proc[shortest].art;

        }

        // Move to next second
        currentTime++;
    }
}

// Function to calculate average waiting time and average turnaround time of all processes
void findAvgTime(struct Process proc[], int n) {
    int totalWt = 0, totalTat = 0;

    // Calculate waiting time and turnaround time
    findWaitingTime(proc, n);

    // Calculate total waiting time and total turnaround time
    for (int i = 0; i < n; i++) {
        totalWt += proc[i].wt;
        totalTat += proc[i].tat;
    }

    // Print results
    printf("Processes  Burst time  Arrival time  Waiting time  Turnaround time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", proc[i].pid, proc[i].bt, proc[i].art, proc[i].wt, proc[i].tat);
    }

    printf("Average waiting time = %f\nAverage turnaround time = %f", (float)totalWt / (float)n, (float)totalTat / (float)n);
}

// Main function
int main() {
    struct Process proc[] = { { 6, 16, 26 }, { 5, 5, 5 }, { 7, 4, 8 }, { 9, 3, 2 } };
    int n = sizeof(proc) / sizeof(proc[0]);

    findAvgTime(proc, n);

    return 0;
}
