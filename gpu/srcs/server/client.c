#define _XOPEN_SOURCE 700

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <arpa/inet.h>
#include <netdb.h> /* getprotobyname */
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include "../includes/rt.h"
#include "../includes/display.h"

void    send_buffer(t_world *world, int port)
{
   char buffer[BUFSIZ];
   char protoname[] = "tcp";
   struct protoent *protoent;
   int enable = 1; 
   int size = 0;
   int color = 0;
   int ret = 0;
   int server_sockfd, client_sockfd;
   socklen_t client_len;
   ssize_t nbytes_read;
   struct sockaddr_in client_address, server_address;
   unsigned short server_port = port;
    
   protoent = getprotobyname(protoname);
   if (protoent == NULL) {
       perror("getprotobyname");
       exit(EXIT_FAILURE);
   }

   server_sockfd = socket(
       AF_INET,
       SOCK_STREAM,
       protoent->p_proto
       /* 0 */
   );
   if (server_sockfd == -1) {
       perror("socket");
       exit(EXIT_FAILURE);
   }

   if (setsockopt(server_sockfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable)) < 0) {
       perror("setsockopt(SO_REUSEADDR) failed");
       exit(EXIT_FAILURE);
   }

   server_address.sin_family = AF_INET;
   server_address.sin_addr.s_addr = htonl(INADDR_ANY);
   server_address.sin_port = htons(server_port);
   if (bind(
           server_sockfd,
           (struct sockaddr*)&server_address,
           sizeof(server_address)
       ) == -1
   ) {
       perror("bind");
       exit(EXIT_FAILURE);
   }

   if (listen(server_sockfd, 5) == -1) {
       perror("listen");
       exit(EXIT_FAILURE);
   }
fprintf(stderr, "listening on port %d\n", server_port);
(void)world;
	while (1)
	{
		client_len = sizeof(client_address);
		client_sockfd = accept(server_sockfd, (struct sockaddr*)&client_address, &client_len);
	    if ((nbytes_read = read(client_sockfd, buffer, BUFSIZ)) > 0)
		{
			printf("received: %zd\n", nbytes_read);
    	    if (write(STDOUT_FILENO, buffer, nbytes_read) == -1){
    			perror("write");
      			exit(EXIT_FAILURE);
   			}
	        if (write(client_sockfd, buffer, nbytes_read) == -1){
    			perror("write");
      			exit(EXIT_FAILURE);
   			}
	        size = 0;
			ret = 0;
			color = 0;
    		while (size < (WIN_HEIGHT * WIN_WIDTH))
        	{
        		color = world->a_h[size];
				// if (size % 2 == 0)
					// color = RED;
				// else
				// if (size < 500)
					// color = RED;
				// else
				//  color = BLACK;
        	    ret = send(client_sockfd, &color, sizeof(color), 0);
				if (ret < 0){
    				perror("send");
      				exit(EXIT_FAILURE);
   				}
				// if (ret > 0)
        	    	size++;
        	}
			// break;
    	}
		close(client_sockfd);
   	}
}