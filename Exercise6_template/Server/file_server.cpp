/* A simple server in the internet domain using TCP
The port number is passed as an argument 
Based on example: https://www.linuxhowtos.org/C_C++/socket.htm 

Modified: Michael Alrøe
Extended to support file server!
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include "iknlib.h"

#define BUFSIZE_TX 1000

void error(const char *msg)
{
	perror(msg);
	exit(1);
}

/**
 * @brief Sends a file to a client socket
 * @param clientSocket Socket stream to client
 * @param fileName Name of file to be sent to client
 * @param fileSize Size of file
 */
void sendFile(int clientSocket, const char* fileName, long fileSize)
{
	printf("Sending: %s, size: %li\n", fileName, fileSize);
    
	
	
}


int main(int argc, char *argv[])
{
	printf("Starting server...\n");

	int sockfd, newsockfd, portno;
	
	size_t numBytes;
	FILE * fp;

	socklen_t clilen;
	char transferBuffer[BUFSIZE_TX];
	char fileName[256];
	struct sockaddr_in serv_addr, cli_addr;
	int n;
	
	if (argc < 2) 
		error("ERROR usage: port");


	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) 
		error("ERROR opening socket");

	printf("Binding...\n");
	bzero((char *) &serv_addr, sizeof(serv_addr));
	portno = atoi(argv[1]);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);
	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
		error("ERROR on binding");

	printf("Listen...\n");
	listen(sockfd,5);

	clilen = sizeof(cli_addr);

	printf("Accept...\n");
	newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

	if (newsockfd < 0) error("ERROR on accept");
	else printf("Accepted\n");

	bzero(transferBuffer,sizeof(transferBuffer));
	n = read(newsockfd,transferBuffer,sizeof(transferBuffer));

	if (n < 0) error("ERROR reading from socket");
	printf("Filename: %s\n",(char*)transferBuffer);
	return 0; 
}