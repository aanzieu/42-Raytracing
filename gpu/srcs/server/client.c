/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/21 16:19:51 by aanzieu           #+#    #+#             */
/*   Updated: 2017/07/27 17:02:08 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cluster.h>
#include <gpu_rt.h>

static void			check_cmd_recv(char cmd, t_data *data, t_cluster *cluster)
{
	printf("data_used = %zu\n", data->used);
	printf("cmd = %c\n", cmd);
	if (cmd == 's')
	{
		printf("uptdate spehres\n");
		updated_objs(data, cmd, data->used / sizeof(t_sphere), cluster);
		printf("je sors de update spheres\n");
	}
	if (cmd == 'p')
		updated_objs(data, cmd, data->used / sizeof(t_plane), cluster);
	// if (cmd == 'x')
	// 	updated_objs(data, cmd, data->used / sizeof(t_cone), cluster);
	// if (cmd == 'y')
	// 	updated_objs(data, cmd, data->used / sizeof(t_cylinder), cluster);
	if (cmd == 'l')
	{
		printf("uptdate lights\n");
		updated_objs(data, cmd, data->used / sizeof(t_light), cluster);
		printf("je sors de light \n");
		
	}	
	printf("Sors de Check_cmd_recv\n");
}

void				process_send(char cmd, t_data *data,
		t_cluster *cluster, int sockfd)
{
	size_t	main_size;

	main_size = sizeof(int) * (WIN_WIDTH *
			(cluster->world->offsets.y_max - cluster->world->offsets.y_min));
	if (cmd == 'c')
		ft_memcpy(&cluster->world->camera, data->data, sizeof(t_camera));
	if (cmd == 'z')
		ft_memcpy(&cluster->world->ambient, data->data, sizeof(t_ambient));
	if (cmd == 'k')
		ft_memcpy(&cluster->world->keys, data->data, sizeof(t_keys));
	check_cmd_recv(cmd, data, cluster);
	if (cmd == 'r')
	{
		printf("avant RT\n");
		rt_cluster(cluster->world);
		printf("sors de RT_cluster\n");
		data->used = 0;
		data_recv(data, main_size);
		data->used = main_size;
		ft_memcpy(data->data, cluster->world->a_h, data->used);
		send(sockfd, data->data, data->used, 0);
		// clear_world(cluster->world);

	}
	if (cmd == 'w')
		ft_memcpy(&cluster->world->offsets, data->data, data->used);
	send(sockfd, &cmd, 1, 0);
}
