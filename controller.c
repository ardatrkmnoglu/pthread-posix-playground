#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
	int socket_fd;
	struct sockaddr_in server_addr, client_addr;
	char buf[BUFFER_SIZE];
	socklen_t addr_len = sizeof(client_addr);

	// define server socket
	// AF_INET: IPv4
	// SOCK_DGRAM: UDP (user datagram protocol)
	socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (socket_fd < 0) {
		perror("Failed to create the socket");
		return 1;
	}

	// server address info
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY; // establish connection from any interface
	server_addr.sin_port = htons(PORT); // host byte order -> network byte order

	// bind the socket to the server address
	if (bind(socket_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
		perror("Binding failed");
		return 1;
	}

	printf("[Controller] UDP server listening from the port %d...\n", PORT);

	// read data from network
	while (1) {
		// receive data from the client address
		int bytes_received = recvfrom(socket_fd, buf, BUFFER_SIZE, 0, (struct sockaddr*)&client_addr, &addr_len);

		if (bytes_received > 0) {
			buf[bytes_received] = '\0';  // end the string with the null terminator character

			if (strcmp(buf, "STOP") == 0) {
				printf("[Controller] %s\n", buf);
				break;
			}

			printf("[Controller] Speed: %s km/h\n", buf);
		}
	}

	close(socket_fd);

	return(EXIT_SUCCESS);
}
