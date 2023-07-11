#include<stdio.h>

struct Process {
    int processID;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
};

void calculateTimes(struct Process* processes, int n, int timeQuantum) {
    int currentTime = 0;
    int remainingProcesses = n;

    while (remainingProcesses > 0) {
        int completedProcesses = 0; // Keep track of completed processes in each iteration

        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0) {
                // Execute the process for the time quantum or until it completes
                int executionTime = (processes[i].remainingTime <= timeQuantum) ? processes[i].remainingTime : timeQuantum;
                processes[i].remainingTime -= executionTime;
                currentTime += executionTime;

                if (processes[i].remainingTime == 0) {
                    // Process completed
                    processes[i].completionTime = currentTime;
                    processes[i].turnaroundTime = processes[i].completionTime - processes[i].arrivalTime;
                    processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;
                    remainingProcesses--;
                    completedProcesses++;
                }
            }
        }

        if (completedProcesses == 0) {
            // If no process completed in this iteration, increment the current time
            currentTime++;
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
        processes[i].remainingTime = processes[i].burstTime;
    }

    int timeQuantum;
    printf("Enter time quantum: ");
    scanf("%d", &timeQuantum);

    calculateTimes(processes, n, timeQuantum);
    displayResults(processes, n);

    return 0;
}

