#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>



#include <bits/stdc++.h>
#define SOCKET int
#define ISVALIDSOCKET(s) ((s) >= 0)
#define CLOSESOCKET(s) close(s)

using namespace std;



int main(int argc, char const *argv[])
{
	printf("************************************************\n");
	printf("******Configuring local address****************\n");
	struct addrinfo hints;
	/*   struct addrinfo {
    int ai_flags;
    int ai_family;
    int ai_socktype;
    int ai_protocol;
    size_t ai_addrlen;
    char * ai_canonname;
    struct sockaddr * ai_addr;
    struct addrinfo * ai_next
}; */

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	struct addrinfo * bind_address;
	getaddrinfo(0, "8080", &hints, &bind_address);

   printf("*****************Creating socket...***************\n");
   	SOCKET socket_listen;
   	socket_listen = socket(bind_address->ai_family, bind_address->ai_socktype,bind_address->ai_protocol);
   	if (socket_listen<0)
   	{
   		printf("error occured i creating sockets\n");
   		return 1;
   	}

      printf("***************Binding socket to local address...************\n");

   if (bind(socket_listen, bind_address->ai_addr,bind_address->ai_addrlen))
   {
   	printf("failded binding\n");
   	return 1;  

   	 }
   	 freeaddrinfo(bind_address);
  

   if (listen(socket_listen,5))
   {
   	printf("failded listen\n");
   	return 1;  

   	 }

     printf("************Waiting for connection... ***************\n");

  struct sockaddr_storage client_address;
  socklen_t client_len = sizeof(client_address);
  SOCKET socket_client = accept(socket_listen,(struct sockaddr*) &client_address, &client_len);
   if (!ISVALIDSOCKET(socket_client)) {
 fprintf(stderr, "accept() failed. (%d)\n", GETSOCKETERRNO());
 return 1;
 }

 printf("Reading request...\n");
 char request[1024];
 int bytes_received = recv(socket_client, request, 1024, 0);
 printf("Received %d bytes.\n", bytes_received);


 // will create a way to send info to client

	return 0;    
}
