/*SHIFNA P
CS B
20220091*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define BUFFER_SIZE 10

int is_prime(int num) {
    if (num <= 1) {
        return 0;
    }

    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) {
            return 0;
        }
    }

    return 1;
}

int main() {
    int N;
    int pipefd[2];
    int numbers[BUFFER_SIZE];

    printf("Enter the number of values to send: ");
    scanf("%d", &N);

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

        int received_numbers[BUFFER_SIZE];
        int num_received = 0;

        // Read numbers from the pipe until the end
        while (read(pipefd[0], &received_numbers[num_received], sizeof(int)) > 0) {
            num_received++;
        }

        close(pipefd[0]);  // Close the read end of the pipe in the child process

        printf("Child process received %d numbers. Calculating prime numbers...\n", num_received);

        printf("Prime numbers: ");
        for (int i = 0; i < num_received; i++) {
            if (is_prime(received_numbers[i])) {
                printf("%d ", received_numbers[i]);
            }
        }
        printf("\n");
    } else {
        // Parent process
        close(pipefd[0]);  // Close the read end of the pipe in the parent process

        printf("Enter %d numbers to send:\n", N);
        for (int i = 0; i < N; i++) {
            scanf("%d", &numbers[i]);
            write(pipefd[1], &numbers[i], sizeof(int));
        }

        close(pipefd[1]);  // Close the write end of the pipe in the parent process
    }

    return 0;
}

/*output
Enter the number of values to send: 5
Enter 5 numbers to send:
1
2
3
4
5
Child process received 5 numbers. Calculating prime numbers...
Prime numbers: 2 3 5 */
