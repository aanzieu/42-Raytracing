/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/21 16:19:51 by aanzieu           #+#    #+#             */
/*   Updated: 2017/07/21 16:52:46 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/cluster.h>
#include <../includes/rt.h>
#include "../../gpu/srcs/cuda/cudaheader/gpu_rt.h"
#include <parse.h>
#include <display.h>
#include <unistd.h>


int	data_grow(t_data *data, size_t size)
{
	void	*new;
	size_t	new_total;

	new_total = data->total * 1.618 * size;
	new = ft_memalloc(new_total);
	ft_memcpy(new, data->data, data->used);
	free(data->data);
	data->data = new;
	data->total = new_total;
	return(1);
}

int	data_recv(t_data *data, size_t size)
{

	if(!size)
	{
		printf("size = 0");
		return(0);
	}
	if(!data->total)
	{
		data->data = ft_memalloc(size);
		data->total = size;
		data->used = 0;
	}
	if(data->total >= data->used + size)
		return(1);
	if(data->total == 1)
		data->total++;
	return(data_grow(data,size));
}
void	updated_camera(t_data *data, t_cluster *cluster)
{
	ft_memcpy(&cluster->world->camera, data->data, sizeof(t_camera));
	printf("camera position.z : %lf\n", cluster->world->camera.pos.z);
}

void	updated_objs(t_data *data, char cmd, short n, t_cluster *cluster)
{
	if(cmd == 's')
	{
		free(cluster->world->spheres);
		printf("data_len = %d\n", n);
		if (n == 0)
			return;
		cluster->world->spheres = (t_sphere*)malloc(sizeof(t_sphere) * n);
		ft_bzero(cluster->world->spheres, n);
		ft_memcpy(cluster->world->spheres, data->data, data->used);
		printf("client spheres radius %lf\n", cluster->world->spheres[0].radius);
	}
	if(cmd == 'l')
	{
		free(cluster->world->lights);
		printf("data_len = %d\n", n);
		if (n == 0)
			return;
		cluster->world->lights = (t_light*)malloc(sizeof(t_light) * n);
		ft_bzero(cluster->world->lights, n);
		ft_memcpy(cluster->world->lights, data->data, data->used);
		printf("client light pos.z %lf\n", cluster->world->lights[0].pos.z);
	}
}

void	process_send(char cmd, t_data *data, t_cluster *cluster, int sockfd)
{
	size_t	main_size;

	main_size = 4 * WIN_WIDTH * WIN_HEIGHT;// * sizeof(int);
	if(cmd == 'c')
		updated_camera(data, cluster);
	if(cmd == 's')
	{
		updated_objs(data, cmd, data->used / sizeof(t_sphere), cluster);
		cluster->world->spheres_len = data->used / sizeof(t_sphere);
		printf("nb de spheres %d\n", cluster->world->spheres_len);
	}
	if(cmd == 'l')
	{
		updated_objs(data, cmd, data->used / sizeof(t_light), cluster);
		cluster->world->lights_len = data->used / sizeof(t_light);
		printf("nb de light %d\n", cluster->world->lights_len);
	}
	if(cmd == 'r')
	{
		printf("je recois la commande %c\n", cmd);
		rt_cluster(cluster->world);
		data->used = 0;
		data_recv(data, main_size);
		printf("before cpy\n");
		printf("couleurs %d :\n", cluster->world->a_h[620]);
		ft_memcpy(data->data, cluster->world->a_h, main_size);
		printf("after cpy\n");

		send(sockfd, data->data, data->used, 0);
		printf("after send\n");
		printf("%zu\n", data->used);
	}
	if (cmd == 'w')
	{
		printf("%c\n", cmd);
		ft_memcpy(&cluster->offsets, data->data, data->used);
		printf("offsets.x %lf | offsets.y %lf\n", cluster->offsets.x, cluster->offsets.y);
	}
	send(sockfd, &cmd, 1, 0);
}




































// void    send_buffer(t_world *world, int port)
// {
//    char buffer[BUFSIZ];
//    char protoname[] = "tcp";
//    struct protoent *protoent;
//    int enable = 1; 
//    int size = 0;
//    int color = 0;
//    int ret = 0;
//    int server_sockfd, client_sockfd;
//    socklen_t client_len;
//    ssize_t nbytes_read;
//    struct sockaddr_in client_address, server_address;
//    unsigned short server_port = port;
    
//    protoent = getprotobyname(protoname);
//    if (protoent == NULL) {
//        perror("getprotobyname");
//        exit(EXIT_FAILURE);
//    }

//    server_sockfd = socket(
//        AF_INET,
//        SOCK_STREAM,
//        protoent->p_proto
//        /* 0 */
//    );
//    if (server_sockfd == -1) {
//        perror("socket");
//        exit(EXIT_FAILURE);
//    }

//    if (setsockopt(server_sockfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable)) < 0) {
//        perror("setsockopt(SO_REUSEADDR) failed");
//        exit(EXIT_FAILURE);
//    }

//    server_address.sin_family = AF_INET;
//    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
//    server_address.sin_port = htons(server_port);
//    if (bind(
//            server_sockfd,
//            (struct sockaddr*)&server_address,
//            sizeof(server_address)
//        ) == -1
//    ) {
//        perror("bind");
//        exit(EXIT_FAILURE);
//    }

//    if (listen(server_sockfd, 5) == -1) {
//        perror("listen");
//        exit(EXIT_FAILURE);
//    }
// fprintf(stderr, "listening on port %d\n", server_port);
// (void)world;
// 	while (1)
// 	{
// 		client_len = sizeof(client_address);
// 		client_sockfd = accept(server_sockfd, (struct sockaddr*)&client_address, &client_len);
// 	    if ((nbytes_read = read(client_sockfd, buffer, BUFSIZ)) > 0)
// 		{
// 			printf("received: %zd\n", nbytes_read);
//     	    if (write(STDOUT_FILENO, buffer, nbytes_read) == -1){
//     			perror("write");
//       			exit(EXIT_FAILURE);
//    			}
// 	        if (write(client_sockfd, buffer, nbytes_read) == -1){
//     			perror("write");
//       			exit(EXIT_FAILURE);
//    			}
// 	        size = 0;
// 			ret = 0;
// 			color = 0;
//     		while (size < (WIN_HEIGHT * WIN_WIDTH))
//         	{
//         		color = world->a_h[size];
// 				// if (size % 2 == 0)
// 					// color = RED;
// 				// else
// 				// if (size < 500)
// 					// color = RED;
// 				// else
// 				//  color = BLACK;
//         	    ret = send(client_sockfd, &color, sizeof(color), 0);
// 				if (ret < 0){
//     				perror("send");
//       				exit(EXIT_FAILURE);
//    				}
// 				// if (ret > 0)
//         	    	size++;
//         	}
// 			// break;
//     	}
// 		close(client_sockfd);
//    	}
// }
