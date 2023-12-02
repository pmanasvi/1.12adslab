#include <stdio.h>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#define PORT 8080
#define SERVER_IP "127.0.0.1"
#define WINDOW_SIZE 4
#define TIMEOUT 3000 // Time in milliseconds
int main() {
WSADATA wsaData;
SOCKET clientSocket;
struct sockaddr_in serverAddr;
int addr_size = sizeof(serverAddr);
char buffer[1024];

if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
printf("WSAStartup failed.\n");
return 1;
}

clientSocket = socket(AF_INET, SOCK_DGRAM, 0);

if (clientSocket == INVALID_SOCKET) {
printf("Error in socket creation.\n");
return 1;
}

serverAddr.sin_family = AF_INET;
serverAddr.sin_port = htons(PORT);
serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);
int sequence_number = 0;

while (1) {
if (sequence_number < WINDOW_SIZE) {
sprintf(buffer, "%d", sequence_number);
sendto(clientSocket, buffer, strlen(buffer), 0, (struct
sockaddr*)&serverAddr, addr_size);
printf("Sent: %d\n", sequence_number);
// Set a timer for TIMEOUT milliseconds
struct timeval tv;
tv.tv_sec = TIMEOUT / 1000;
tv.tv_usec = (TIMEOUT % 1000) * 1000;
setsockopt(clientSocket, SOL_SOCKET, SO_RCVTIMEO, (const
char*)&tv, sizeof(tv));
// Receive acknowledgment
int n = recvfrom(clientSocket, buffer, sizeof(buffer), 0, (struct
sockaddr*)&serverAddr, &addr_size);
if (n < 0 && sequence_number!=0) {
// Timeout occurred, retransmit from 0
printf("Timeout, retransmitting from 0...\n");
sequence_number = 0; // Reset sequence number
} else {
printf("Received acknowledgment: %s\n", buffer);
sequence_number++;
}
}
Sleep(1000); // Simulate transmission delay
}
closesocket(clientSocket);
WSACleanup();
return 0;
}