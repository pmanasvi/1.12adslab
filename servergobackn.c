#include <stdio.h>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#define PORT 8080
#define WINDOW_SIZE 4
int main() {
WSADATA wsaData;
SOCKET serverSocket;
struct sockaddr_in serverAddr, clientAddr;
int addr_size = sizeof(clientAddr);
char buffer[1024];
if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
printf("WSAStartup failed.\n");
return 1;
}
serverSocket = socket(AF_INET, SOCK_DGRAM, 0);
if (serverSocket == INVALID_SOCKET) {
printf("Error in socket creation.\n");
return 1;
}
serverAddr.sin_family = AF_INET;
serverAddr.sin_port = htons(PORT);
serverAddr.sin_addr.s_addr = INADDR_ANY;
if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) 
== SOCKET_ERROR) {
printf("Error in binding.\n");
return 1;
}
printf("Server listening on port %d...\n", PORT);
int expected_sequence_number = 0;
while (1) {
int n = recvfrom(serverSocket, buffer, sizeof(buffer), 0, (struct
sockaddr*)&clientAddr, &addr_size);
// Simulate packet loss
if (rand() % 100 < 30) {
printf("Packet loss, sequence number %d\n", 
expected_sequence_number);
continue;
}
int received_sequence_number;
sscanf(buffer, "%d", &received_sequence_number);
if (received_sequence_number == expected_sequence_number) {
printf("Received: %d\n", received_sequence_number);
// Send acknowledgment
char ack[16];
sprintf(ack, "ACK: %d", received_sequence_number);
sendto(serverSocket, ack, strlen(ack), 0, (struct
sockaddr*)&clientAddr, addr_size);
expected_sequence_number = (expected_sequence_number + 1) % 
(WINDOW_SIZE);
} else {
printf("Discarded: %d\n", received_sequence_number);
expected_sequence_number=0;
}
}
closesocket(serverSocket);
WSACleanup();
return 0;
}
