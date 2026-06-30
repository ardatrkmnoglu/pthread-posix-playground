#include <stdio.h>
#include <string.h>
#include <sys/types.h> // pid_t description
#include <unistd.h>    // POSIX syscalls (pipe, fork, read, write)

int main() {
	int pipe_fd[2]; // Two ends of the pipe: [0] read, [1] write
	pid_t pid;
	char write_msg[] = "SANSAR SALVO YERINDE DURAMAYAN ADAM";
	char read_msg[100]; // The buffer where the child process will read data

	// create pipe
	int pipe1 = pipe(pipe_fd);
	if (pipe1 < 0) {
		perror("Could not create the pipe");
		return 1;
	}

	// fork the process
	pid_t m_fork = fork();
	pid = m_fork;

	if (pid < 0) {
		perror("Fork failed");
		return 1;
	}

	if (pid > 0) {
		// ----- parent process -----
		close(pipe_fd[0]);

		// write message to pipe
		write(pipe_fd[1] , write_msg, strlen(write_msg) + 1);
		close(pipe_fd[1]);
		printf("[Parent] Message sent to the child process.\n");
	} else {
		// ----- child process -----
		close(pipe_fd[1]);

		// read message from pipe
		read(pipe_fd[0] , read_msg, sizeof(read_msg));
		printf("[Child] Received message from the pipe: %s\n", read_msg);
		close(pipe_fd[0]);
	}

	return 0;
}
