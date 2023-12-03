#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <arpa/inet.h>


// Function to perform byte destuffing
void destuff(char *destuffed, char *stuffed, int length) {
    int i, j = 0;
    for (i = 0; i < length; i++) {
        if (stuffed[i] == 0x7D) {
            i++;
            destuffed[j++] = stuffed[i] ^ 0x20; // XOR with 0x20 to get original byte
        } else {
            destuffed[j++] = stuffed[i];
        }
    }
    destuffed[j] = '\0';
}

int main() {
    int server_socket,client_socket;
    char stuffed_message[1024];
    char destuffed_message[1024];

    // Create socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Server configuration, binding, and listening code goes here...
    // You can reuse the server setup from the previous example.

    // Accept incoming connection (assuming client has connected)

    // Read the stuffed message from the client
    read(client_socket, stuffed_message, sizeof(stuffed_message));

    // Perform byte destuffing
    destuff(destuffed_message, stuffed_message, strlen(stuffed_message));

    // Print the received and destuffed message
    printf("Received and Destuffed Message: %s\n", destuffed_message);

    // Close the server socket
    close(server_socket);

    return 0;
}

