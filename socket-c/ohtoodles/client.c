#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#define BUFFERSIZE  1024

int main(int argc, char** argv){
	if(argc < 3){
		printf("Usage: %s <ip> <port>\n", argv[0]);
		exit(1);
	}

	int sockfd, retcode;
	struct sockaddr_in addr;
	socklen_t addrL = sizeof(struct sockaddr_in);
	char msg[BUFFERSIZE];
	char buffer[BUFFERSIZE];

	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
		perror("socket");
		exit(2);
	}

	addr.sin_family = AF_INET;
	addr.sin_port = htons(atoi(argv[2]));
	inet_pton(AF_INET, argv[1], &addr.sin_addr);

	if(connect(sockfd, (struct sockaddr*)&addr, addrL) == -1){
		perror("connect");
		exit(3);
	}

	strncpy(msg, "ohtoodles", BUFFERSIZE);
	write(sockfd, msg, strlen(msg));

	if((retcode = read(sockfd, buffer, BUFFERSIZE)) == -1){
		perror("read");
		exit(4);
	}

	printf("%s", buffer);

	fgets(msg, BUFFERSIZE, stdin);
	write(sockfd, msg, strlen(msg));

	if((retcode = read(sockfd, buffer, BUFFERSIZE)) == -1){
		perror("read");
		exit(4);
	}

	printf("%s", buffer);
	
	close(sockfd);
}