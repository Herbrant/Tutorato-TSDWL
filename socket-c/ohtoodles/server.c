#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#define BUFFERSIZE 1024
#define PORT 3000
#define LOCALHOST "127.0.0.1"
#define MAXQ 80

char* build_msg(char** tools){
	char* msg = malloc(sizeof(char) * BUFFERSIZE);
	strncpy(msg, "", BUFFERSIZE);

	for(int i = 0; i < 4; i++)
		sprintf(msg, "%s %d. %s\n", msg, i+1, tools[i]);
	
	return msg;
}


int main(void){
	int sockfd, s1, retcode;
	struct sockaddr_in localAddr, farAddr;
	socklen_t localAddrL, farAddrL;
	localAddrL = farAddrL = sizeof(struct sockaddr_in);
	char buffer[BUFFERSIZE], *msg;
	char* tools[4] = {"scopa", "secchiello", "aquilone", "?"};

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
		perror("socket");
		exit(1);
	}

	localAddr.sin_family = AF_INET;
	localAddr.sin_port = htons(PORT);
	inet_pton(AF_INET, LOCALHOST, &(localAddr.sin_addr));

	//Binding
	if(bind(sockfd, (struct sockaddr*) &(localAddr), localAddrL) == -1){
		perror("binding");
		exit(2);
	}

	//Listen
	listen(sockfd, MAXQ);

	while((s1 = accept(sockfd, (struct sockaddr*) &farAddr, &farAddrL)) != -1){
		printf("Client %s:%d\n", inet_ntoa(farAddr.sin_addr), ntohs(farAddr.sin_port));

		if((retcode = read(s1, buffer, BUFFERSIZE)) > 0){
			buffer[retcode] = '\0';

			printf("Client asks: %s\n", buffer);
			
			if(strcmp(buffer, "ohtoodles") == 0){
				msg = build_msg(tools);
				write(s1, msg, strlen(msg));
				free(msg);

				if((retcode = read(s1, buffer, BUFFERSIZE)) > 0){
					int value = atoi(buffer);

					if(value >= 1 && value <= 4){
						tools[value - 1] = "-";
						msg = build_msg(tools);
						write(s1, msg, strlen(msg));
						free(msg);
					}
				}
			}
			else{
				msg = "Scusami non ho capito, chiudo la connessione!";
				write(s1, msg, strlen(msg));
			}
		}

		close(s1);
	}

	close(sockfd);
}