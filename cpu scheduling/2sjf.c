#include<stdio.h>
#include<limits.h>

struct Process {
    int processID;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
};

void calculateTimes(struct Process* processes, int n) {
    int currentTime = 0;

    for (int i = 0; i < n; i++) {
        // Find the process with the shortest burst time
        int shortestIndex = -1;
        int shortestBurst = INT_MAX;

        for (int j = 0; j < n; j++) {
            if (processes[j].arrivalTime <= currentTime && processes[j].burstTime < shortestBurst && processes[j].completionTime == 0) {
                shortestIndex = j;
                shortestBurst = processes[j].burstTime;
            }
        }

        if (shortestIndex == -1) {
            currentTime++;
            i--; // No process found, continue to the next time unit
            continue;
        }

        // Update completion time
        currentTime += processes[shortestIndex].burstTime;
        processes[shortestIndex].completionTime = currentTime;

        // Calculate turnaround time and waiting time
        processes[shortestIndex].turnaroundTime = processes[shortestIndex].completionTime - processes[shortestIndex].arrivalTime;
        processes[shortestIndex].waitingTime = processes[shortestIndex].turnaroundTime - processes[shortestIndex].burstTime;
    }
}

void sortByBurstTime(struct Process* processes, int n) {
    // Bubble sort based on burst time
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].burstTime > processes[j + 1].burstTime) {
                // Swap processes
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}

void displayResults(struct Process* processes, int n) {
    printf("Process\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");

	float turnaround_avg = 0;
	float waiting_avg = 0;

    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].processID, processes[i].arrivalTime,
               processes[i].burstTime, processes[i].completionTime, processes[i].turnaroundTime,
               processes[i].waitingTime);
	turnaround_avg +=processes[i].turnaroundTime;
		waiting_avg +=processes[i].waitingTime;
    }

	turnaround_avg /=n;
		waiting_avg /=n;
		printf("\nAverage Turnaround Time: %.2f\n", turnaround_avg);
		printf("Average Waiting Time: %.2f\n", waiting_avg);
}

int main() {
    int n; // Number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    // Input process details
    for (int i = 0; i < n; i++) {
        printf("Enter arrival time for process %d: ", i + 1);
        scanf("%d", &processes[i].arrivalTime);

        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].burstTime);

        processes[i].processID = i + 1;
    }

    calculateTimes(processes, n);
    sortByBurstTime(processes, n);
    displayResults(processes, n);

    return 0;
}

