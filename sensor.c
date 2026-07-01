#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"
#define PORT 8080

int main() {
	int socket_fd;
	struct sockaddr_in server_addr;
	char msg[] = "20";
	char msg2[] = "40";
	char msg3[] = "70";
	char msg4[] = "120";
	const char* msg_arr[] = {msg, msg2, msg3, msg4};
	char stop_msg[] = "STOP";

	// define client socket
	socket_fd = socket(AF_INET , SOCK_DGRAM, 0);
	if (socket_fd < 0) {
		perror("Failed creating socket");
		return 1;
	}

	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);
	server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

	printf("[Server] Sending data to UDP server...\n");

	// send message over server
	for (int i = 0; i < 4; i++) {
		sendto(socket_fd, msg_arr[i], strlen(msg_arr[i]), 0, (struct sockaddr*)&server_addr, sizeof(server_addr));
		printf("[Sensor] Sent data %d.\n", i);

		sleep(2);
	}

	sendto(socket_fd, stop_msg, strlen(stop_msg), 0, (struct sockaddr*)&server_addr, sizeof(server_addr));
	printf("[Sensor] Sent STOP signal.\n");

	close(socket_fd);

	return 0;
}
