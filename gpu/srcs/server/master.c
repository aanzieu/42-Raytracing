/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   master.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/29 15:32:15 by aanzieu           #+#    #+#             */
/*   Updated: 2017/06/29 18:09:41 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _XOPEN_SOURCE 700

#include <assert.h>
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
/*
typedef struct s_stockage
{
	    int        test;
		int			tab[2];
}            t_stockage;
*/
void		test_pixel_put(int *a_h)
{
	int 			i;
	int 			j;
	i = 0;
//	(void)a_h;
	while (i < WIN_HEIGHT)
	{
		j = 0;
		while (j < WIN_WIDTH)
		{
//			printf("JE rentre dans la fonciton\n");
			if(a_h[i * WIN_WIDTH + j] > 0)
				printf("%d\n", a_h[i * WIN_WIDTH + j]);
			j++;
		}
		i++;
	}
}

void *get_data_from_client_thread(void *arg)
{
	t_thread_input		*thread;
	thread = (t_thread_input*)arg;

	char buffer[BUFSIZ];
	char protoname[] = "tcp";
	struct protoent *protoent;
//	{"10.11.13.10","10.12.13.8", NULL} ;
	//	char *user_input = NULL;
	in_addr_t in_addr;
	int sockfd;
	ssize_t nbytes_read;// user_input_len;
	struct hostent *hostent;
	/* This is the struct used by INet addresses. */
	struct sockaddr_in sockaddr_in;
	
	
	unsigned short server_port = thread->port[thread->th];//12345;
	char *server_hostname = thread->str[thread->th];
	
	
	int size;
	size = thread->th * (WIN_HEIGHT * WIN_WIDTH) / 2;
	
	if(thread->th == 1)
	{
		server_port = 23456;
		server_hostname = "10.11.13.10";
	}
	if(thread->th == 0)
	{
		server_port = 12345;
		server_hostname = "10.11.12.18";
	}
//	while(*server_hostname) {
//	if (argc > 1) {
//		server_hostname = serveurid;
//		if (argc > 2) {
//			server_port = strtol(argv[2], NULL, 10);
//		}
//	}

	/* Get socket. */
	protoent = getprotobyname(protoname);
	if (protoent == NULL) {
		perror("getprotobyname");
		exit(EXIT_FAILURE);
	}
	thread->fd[thread->th] = socket(AF_INET, SOCK_STREAM, protoent->p_proto);
	sockfd = thread->fd[thread->th];
	if (sockfd == -1) {
		perror("socket");
		exit(EXIT_FAILURE);
	}

	/* Prepare sockaddr_in. */
	hostent = gethostbyname(server_hostname);//serverid]);
	if (hostent == NULL) {
		fprintf(stderr, "error: gethostbyname(\"%s\")\n", server_hostname);
		exit(EXIT_FAILURE);
	}
	in_addr = inet_addr(inet_ntoa(*(struct in_addr*)*(hostent->h_addr_list)));
	if (in_addr == (in_addr_t)-1) {
		fprintf(stderr, "error: inet_addr(\"%s\")\n", *(hostent->h_addr_list));
		exit(EXIT_FAILURE);
	}
	sockaddr_in.sin_addr.s_addr = in_addr;
	sockaddr_in.sin_family = AF_INET;
	sockaddr_in.sin_port = htons(server_port);
	static double i = 0.000;
	
//	int test = 0;
	/* Do the actual connection. */
	if (connect(sockfd, (struct sockaddr*)&sockaddr_in, sizeof(sockaddr_in)) == -1) {
		perror("connect");
		exit(EXIT_FAILURE);
	}
	while (1) {

		if (dprintf(sockfd, "%lf : Envoie demande connection\n", i) == -1) {
			perror("write");
			exit(EXIT_FAILURE);
		}
		i += 0.001;
//		(void)world;
		if ((nbytes_read = read(sockfd, buffer, BUFSIZ)) > 0)
		{
			while(size < (thread->th + 1) * (WIN_HEIGHT * WIN_WIDTH) / 2)//orld->size_main)
			{
				recv(sockfd, &thread->world->a_h[size], sizeof(thread->world->a_h), 0);
				size++;
//				recv(sockfd, world->a_h, sizeof(world->a_h) * 65536, 0);
	//			recv(sockfd, tab, sizeof(int), 0);
	//			write(STDOUT_FILENO, buffer, nbytes_read);
	//			printf("%d\n", world->a_h[0]);
//				printf("%d\n", tab[0]);
//				if (size == 0)
//					break;
		//		world->a_h[0] = RED;
//				return;
			}
		//	test_pixel_put(world->a_h);
		//	close(sockfd);
			//free(user_input);
		//	fflush(stdout);
		//	break;
		}
		break;
	//		if (buffer[nbytes_read - 1] == '\n') {
	//			fflush(stdout);
	//			break;
	//	}
	//	}
	}
//	serverid++;
//	}
	close(thread->fd[thread->th]);
	pthread_exit(0);//
//	exit(EXIT_SUCCESS);
}
