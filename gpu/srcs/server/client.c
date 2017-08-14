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
	if (cmd == 's')
		updated_objs(data, cmd, data->used / sizeof(t_sphere), cluster);
	if (cmd == 'p')
		updated_objs(data, cmd, data->used / sizeof(t_plane), cluster);
	if (cmd == 'n')
		updated_objs(data, cmd, data->used / sizeof(t_cone), cluster);
	if (cmd == 'l')
		updated_objs(data, cmd, data->used / sizeof(t_light), cluster);
}

void				process_send(char cmd, t_data *data,
		t_cluster *cluster, int sockfd)
{
	size_t	main_size;

	main_size = sizeof(int) * (WIN_WIDTH *
			(cluster->world->offsets.y_max - cluster->world->offsets.y_min));
	if (cmd == 'c')
		ft_memcpy(&cluster->world->camera, data->data, sizeof(t_camera));
	check_cmd_recv(cmd, data, cluster);
	if (cmd == 'r')
	{
		rt_cluster(cluster->world);
		data->used = 0;
		data_recv(data, main_size);
		data->used = main_size;
		ft_memcpy(data->data, cluster->world->a_h, data->used);
		send(sockfd, data->data, data->used, 0);
	}
	if (cmd == 'w')
		ft_memcpy(&cluster->world->offsets, data->data, data->used);
	send(sockfd, &cmd, 1, 0);
}
