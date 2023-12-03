#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>


typedef struct packet{
    char data[1024];
}Packet;

typedef struct frame{
    int frame_kind; //ACK:0, SEQ:1 FIN:2
    int sq_no;
    int ack;
    Packet packet;
}Frame;

int main(){

	int sockfd,newsockfd;
	struct sockaddr_in serverAddr;
	char buffer[1024];

	int frame_id=0;
	Frame frame_recv;
	Frame frame_send;	

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(9000);
	serverAddr.sin_addr.s_addr = INADDR_ANY;

	bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	listen(sockfd,5);
	
	newsockfd = accept(sockfd, NULL, NULL);

	while(1){
		int f_recv_size = recv(newsockfd, &frame_recv, sizeof(Frame), 0);
		if (f_recv_size > 0 && frame_recv.frame_kind == 1 && frame_recv.sq_no == frame_id){
			printf("[+]Frame Received: %s\n", frame_recv.packet.data);
			
			frame_send.sq_no = 0;
			frame_send.frame_kind = 0;
			frame_send.ack = frame_recv.sq_no + 1;
			send(newsockfd, &frame_send, sizeof(frame_send), 0);
			printf("[+]Ack Send\n");
		}else{
			printf("[+]Frame Not Received\n");
		}
		frame_id++;	
	}
	close(newsockfd);
	close(sockfd);
	return 0;
}
