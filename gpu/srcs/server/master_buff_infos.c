/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   master_buff_infos.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/27 15:04:43 by aanzieu           #+#    #+#             */
/*   Updated: 2017/07/27 16:52:15 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/cluster.h>

static void			*dup_data_obj(t_cluster *cluster, char cmd, void *ret)
{
	size_t	size;

	if (cmd == 's')
	{
		size = sizeof(t_sphere) * cluster->world->spheres_len;
		if ((ret = ft_memalloc(size)) != NULL)
			ret = ft_memcpy(ret, cluster->world->spheres, size);
	}
	if (cmd == 'p')
	{
		size = sizeof(t_plane) * cluster->world->planes_len;
		if ((ret = ft_memalloc(size)) != NULL)
			ret = ft_memcpy(ret, cluster->world->planes, size);
	}
	if (cmd == 'x')
	{
		size = sizeof(t_cone) * cluster->world->cones_len;
		if ((ret = ft_memalloc(size)) != NULL)
			ret = ft_memcpy(ret, cluster->world->cones, size);
	}
	if (cmd == 'y')
	{
		size = sizeof(t_cylinder) * cluster->world->cylinders_len;
		if ((ret = ft_memalloc(size)) != NULL)
			ret = ft_memcpy(ret, cluster->world->cylinders, size);
	}
	if (cmd == 'd')
	{
		size = sizeof(t_disk) * cluster->world->disks_len;
		if ((ret = ft_memalloc(size)) != NULL)
			ret = ft_memcpy(ret, cluster->world->disks, size);
	}
	if (cmd == 'h')
	{
		size = sizeof(t_hyperboloid) * cluster->world->hyperboloids_len;
		if ((ret = ft_memalloc(size)) != NULL)
			ret = ft_memcpy(ret, cluster->world->hyperboloids, size);
	}
	if (cmd == 'b')
	{
		size = sizeof(t_paraboloid) * cluster->world->paraboloids_len;
		if ((ret = ft_memalloc(size)) != NULL)
			ret = ft_memcpy(ret, cluster->world->paraboloids, size);
	}
	if (cmd == 'o')
	{
		size = sizeof(t_torus) * cluster->world->torus_len;
		if ((ret = ft_memalloc(size)) != NULL)
			ret = ft_memcpy(ret, cluster->world->torus, size);
	}
	if (cmd == 'm')
	{
		size = sizeof(t_mobius) * cluster->world->mobius_len;
		if ((ret = ft_memalloc(size)) != NULL)
			ret = ft_memcpy(ret, cluster->world->mobius, size);
	}
	if (cmd == 't')
	{
		size = sizeof(t_triangle) * cluster->world->triangles_len;
		if ((ret = ft_memalloc(size)) != NULL)
			ret = ft_memcpy(ret, cluster->world->triangles, size);
	}
	if (cmd == 'u')
	{
		size = sizeof(t_cylinder) * cluster->world->cubes_len;
		if ((ret = ft_memalloc(size)) != NULL)
			ret = ft_memcpy(ret, cluster->world->cubes, size);
	}
	if (cmd == 'e')
	{
		size = sizeof(t_cylinder) * cluster->world->h_cubes_len;
		if ((ret = ft_memalloc(size)) != NULL)
			ret = ft_memcpy(ret, cluster->world->h_cubes, size);
	}
	return (ret);
}

static void			*dup_data(t_cluster *cluster, char cmd, void *ret)
{
	size_t	size;

	if (cmd == 'c')
	{
		size = sizeof(t_camera);
		if ((ret = ft_memalloc(size)) != NULL)
			ret = ft_memcpy(ret, &cluster->world->camera, sizeof(t_camera));
	}
	if (cmd == 'z')
	{
		size = sizeof(t_ambient);
		if ((ret = ft_memalloc(size)) != NULL)
			ret = ft_memcpy(ret, &cluster->world->ambient, sizeof(t_ambient));
	}
	if (cmd == 'k')
	{
		size = sizeof(t_keys);
		if ((ret = ft_memalloc(size)) != NULL)
			ret = ft_memcpy(ret, &cluster->world->keys, sizeof(t_keys));
	}
	if (cmd == 'l')
	{
		size = sizeof(t_light) * cluster->world->lights_len;
		if ((ret = ft_memalloc(size)) != NULL)
			ret = ft_memcpy(ret, cluster->world->lights, size);
	}
	return (ret);
}

int			send_buffer_obj_next(t_cluster *cluster,
		t_client *clients, void *buffer)
{
	if ((clients->status & SEND_CONES) == 0)
	{
		if (!(buffer = dup_data_obj(cluster, 'x', NULL)))
			return (0);
		send_informations(clients, 'x', buffer,
				cluster->world->cones_len * sizeof(t_cone));
		free(buffer);
	}
	if ((clients->status & SEND_CYLINDERS) == 0)
	{
		if (!(buffer = dup_data_obj(cluster, 'y', NULL)))
			return (0);
		send_informations(clients, 'y', buffer,
				cluster->world->cylinders_len * sizeof(t_cylinder));
		free(buffer);
	}
	if ((clients->status & SEND_HYPERBOLOID) == 0)
	{
		if (!(buffer = dup_data_obj(cluster, 'h', NULL)))
			return (0);
		send_informations(clients, 'h', buffer,
				cluster->world->hyperboloids_len * sizeof(t_hyperboloid));
		free(buffer);
	}
	if ((clients->status & SEND_PARABOLOID) == 0)
	{
		if (!(buffer = dup_data_obj(cluster, 'b', NULL)))
			return (0);
		send_informations(clients, 'b', buffer,
				cluster->world->paraboloids_len * sizeof(t_paraboloid));
		free(buffer);
	}
	if ((clients->status & SEND_DISK) == 0)
	{
		if (!(buffer = dup_data_obj(cluster, 'd', NULL)))
			return (0);
		send_informations(clients, 'd', buffer,
				cluster->world->disks_len * sizeof(t_disk));
		free(buffer);
	}
	if ((clients->status & SEND_TORUS) == 0)
	{
		if (!(buffer = dup_data_obj(cluster, 'o', NULL)))
			return (0);
		send_informations(clients, 'o', buffer,
				cluster->world->torus_len * sizeof(t_torus));
		free(buffer);
	}
	if ((clients->status & SEND_MOEBIUS) == 0)
	{
		if (!(buffer = dup_data_obj(cluster, 'm', NULL)))
			return (0);
		send_informations(clients, 'm', buffer,
				cluster->world->mobius_len * sizeof(t_mobius));
		free(buffer);
	}
	if ((clients->status & SEND_TRIANGLE) == 0)
	{
		if (!(buffer = dup_data_obj(cluster, 't', NULL)))
			return (0);
		send_informations(clients, 't', buffer,
				cluster->world->triangles_len * sizeof(t_triangle));
		free(buffer);
	}
	if ((clients->status & SEND_CUBE) == 0)
	{
	if (!(buffer = dup_data_obj(cluster, 'u', NULL)))
			return (0);
		send_informations(clients, 'u', buffer,
				cluster->world->cubes_len * sizeof(t_cube));
		free(buffer);
	}
	if ((clients->status & SEND_H_CUBE) == 0)
	{
	if (!(buffer = dup_data_obj(cluster, 'b', NULL)))
			return (0);
		send_informations(clients, 'b', buffer,
				cluster->world->h_cubes_len * sizeof(t_h_cube));
		free(buffer);
	}
	return (1);
}

static int			send_buffer_obj(t_cluster *cluster,
		t_client *clients, void *buffer)
{
	if ((clients->status & SEND_PLANS) == 0)
	{
		if (!(buffer = dup_data_obj(cluster, 'p', NULL)))
			return (0);
		send_informations(clients, 'p', buffer,
				cluster->world->planes_len * sizeof(t_plane));
		free(buffer);
	}
	if ((clients->status & SEND_SPHERES) == 0)
	{
		if (!(buffer = dup_data_obj(cluster, 's', NULL)))
			return (0);
		send_informations(clients, 's', buffer,
				cluster->world->spheres_len * sizeof(t_sphere));
		free(buffer);
	}
	return (send_buffer_obj_next(cluster, clients, buffer));
}


int					send_buffer_clients(t_cluster *cluster, t_client *clients)
{
	void	*buffer;

	buffer = NULL;
	if ((clients->status & SEND_CAMERA) == 0)
	{
		if (!(buffer = dup_data(cluster, 'c', NULL)))
			return (0);
		send_informations(clients, 'c', buffer, sizeof(t_camera));
		free(buffer);
	}
	if ((clients->status & SEND_AMBIANT) == 0)
	{
		if (!(buffer = dup_data(cluster, 'z', NULL)))
			return (0);
		send_informations(clients, 'z', buffer, sizeof(t_ambient));
		free(buffer);
	}
	if ((clients->status & SEND_KEYS) == 0)
	{
		if (!(buffer = dup_data(cluster, 'k', NULL)))
			return (0);
		send_informations(clients, 'k', buffer, sizeof(t_keys));
		free(buffer);
	}
	if ((clients->status & SEND_LIGHTS) == 0)
	{
		if (!(buffer = dup_data(cluster, 'l', NULL)))
			return (0);
		send_informations(clients, 'l',
				buffer, cluster->world->lights_len * sizeof(t_light));
		free(buffer);
	}
	return (send_buffer_obj(cluster, clients, buffer));
}
