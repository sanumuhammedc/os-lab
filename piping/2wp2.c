/*Shifna P
cs B
20220091*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 100

int is_palindrome(const char *str) {
int len = strlen(str);
int i, j;

for (i = 0, j = len - 1; i < j; i++, j--) {
	if (str[i] != str[j]) {
	return 0;
	}
}
	return 1;
 }

int main() {
char input_string[BUFFER_SIZE];
int pipefd[2];
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
	close(pipefd[1]); // Close the write end of the pipe in the child process
	char received_string[BUFFER_SIZE];
	read(pipefd[0], received_string, sizeof(received_string));
	close(pipefd[0]); // Close the read end of the pipe in the child process
	printf("Child process received string: %s\n", received_string);
	if (is_palindrome(received_string)) {
		printf("The string is a palindrome.\n");
	} else {
		printf("The string is not a palindrome.\n");
	}
} else {
// Parent process
	close(pipefd[0]); // Close the read end of the pipe in the parent process
	printf("Enter a string: ");
	fgets(input_string, sizeof(input_string), stdin);
	input_string[strcspn(input_string, "\n")] = '\0'; // Remove the newline character
	write(pipefd[1], input_string, strlen(input_string) + 1);
	close(pipefd[1]); // Close the write end of the pipe in the parent process
}
return 0;
}

/*output
Enter a string: malayalam
Child process received string: malayalam
The string is a palindrome.

Enter a string: english
Child process received string: english
The string is not a palindrome.*/


