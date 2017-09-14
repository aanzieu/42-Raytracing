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
	if (cmd == 'x')
		updated_objs(data, cmd, data->used / sizeof(t_cone), cluster);
	if (cmd == 'y')
		updated_objs(data, cmd, data->used / sizeof(t_cylinder), cluster);
	if (cmd == 'l')
		updated_objs(data, cmd, data->used / sizeof(t_light), cluster);
	if (cmd == 'd')
		updated_objs(data, cmd, data->used / sizeof(t_disk), cluster);
	if (cmd == 'h')
		updated_objs(data, cmd, data->used / sizeof(t_hyperboloid), cluster);
	if (cmd == 'b')
		updated_objs(data, cmd, data->used / sizeof(t_paraboloid), cluster);
	if (cmd == 'o')
		updated_objs(data, cmd, data->used / sizeof(t_torus), cluster);
	if (cmd == 'm')
		updated_objs(data, cmd, data->used / sizeof(t_mobius), cluster);
	if (cmd == 't')
		updated_objs(data, cmd, data->used / sizeof(t_triangle), cluster);
	if (cmd == 'u')
		updated_objs(data, cmd, data->used / sizeof(t_cube), cluster);
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
