#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>


int main(int argc, char **argv){

	struct hostent *server;
	struct sockaddr_in serveraddr;
	int sock = socket(AF_INET, SOCK_STREAM, 0), n;
	char buffer[4096], msg[40] = {"GET /index.html HTTP/1.0\r\n\r\n"};

	if (sock < 0){
		printf("Error opening socket!\n");
	}

	server = gethostbyname("99.21.48.48");
	if (server == NULL){
		printf("Error, no such name\n");
	}

	bzero((char*)&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	bcopy((char*)server->h_addr, (char*)&serveraddr.sin_addr.s_addr, server->h_length);

	serveraddr.sin_port = htons(80);

	if (connect(sock, (struct sockaddr*)&serveraddr, sizeof(serveraddr)) < 0){
		printf("Error connecting!\n");
	}

	
	n = write(sock, msg, 28);


	bzero(buffer, 40);
	n = read(sock, buffer, 4095);
	if (n < 0){
		printf("Error reading!\n");
	}

	printf("N = %d, Data =\n", n);
	printf("%s\n", buffer);

	bzero(buffer, 40);
	n = read(sock, buffer, 39);
	if (n < 0){
		printf("Error reading!\n");
	}

	printf("%s\n", buffer);

	close(sock);
	

	return 0;
}
