/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   master_dup_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 14:00:43 by aanzieu           #+#    #+#             */
/*   Updated: 2017/09/19 14:05:48 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/cluster.h>

static void			*dup_data_obj4(t_cluster *cluster, char cmd, void *ret)
{
	size_t	size;

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
	if (cmd == 'y')
	{
		size = sizeof(t_cylinder) * cluster->world->cylinders_len;
		if ((ret = ft_memalloc(size)) != NULL)
			ret = ft_memcpy(ret, cluster->world->cylinders, size);
	}
	return (ret);
}

static void			*dup_data_obj3(t_cluster *cluster, char cmd, void *ret)
{
	size_t	size;

	if (cmd == 't')
	{
		size = sizeof(t_triangle) * cluster->world->triangles_len;
		if ((ret = ft_memalloc(size)) != NULL)
			ret = ft_memcpy(ret, cluster->world->triangles, size);
	}
	if (cmd == 'u')
	{
		size = sizeof(t_cube) * cluster->world->cubes_len;
		if ((ret = ft_memalloc(size)) != NULL)
			ret = ft_memcpy(ret, cluster->world->cubes, size);
	}
	if (cmd == 'e')
	{
		size = sizeof(t_h_cube) * cluster->world->h_cubes_len;
		if ((ret = ft_memalloc(size)) != NULL)
			ret = ft_memcpy(ret, cluster->world->h_cubes, size);
	}
	return (dup_data_obj4(cluster, cmd, ret));
}

static void			*dup_data_obj2(t_cluster *cluster, char cmd, void *ret)
{
	size_t	size;

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
	return (dup_data_obj3(cluster, cmd, ret));
}

void				*dup_data_obj(t_cluster *cluster, char cmd, void *ret)
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
	return (dup_data_obj2(cluster, cmd, ret));
}
