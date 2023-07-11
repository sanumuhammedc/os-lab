#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 10

int main() {
    int n;
    int pipefd[2];
    int numbers[BUFFER_SIZE];

    printf("Enter the number of values to send: ");
    scanf("%d", &n);

    if (pipe(pipefd) == -1) {
        perror("Pipe creation failed");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();

    if (pid == -1) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Child process
        close(pipefd[1]);  // Close the write end of the pipe in the child process

        printf("Child process receiving numbers:\n");

        int received_numbers[BUFFER_SIZE];
        int num_received = 0;

        // Read numbers from the pipe until the end
        while (read(pipefd[0], &received_numbers[num_received], sizeof(int)) > 0) {
            printf("%d ", received_numbers[num_received]);
            num_received++;
        }

        printf("\nChild process received %d numbers.\n", num_received);

        close(pipefd[0]);  // Close the read end of the pipe in the child process
    } else {
        // Parent process
        close(pipefd[0]);  // Close the read end of the pipe in the parent process

        printf("Enter %d numbers to send:\n", n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &numbers[i]);
            write(pipefd[1], &numbers[i], sizeof(int));
        }

        close(pipefd[1]);  // Close the write end of the pipe in the parent process
    }

    return 0;
}
