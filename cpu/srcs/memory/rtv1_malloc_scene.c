/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_malloc_scene.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 13:43:39 by aanzieu           #+#    #+#             */
/*   Updated: 2017/06/13 18:11:42 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rtv1.h"

t_scene		*new_scene(void)
{
	t_scene	*s;

	s = (t_scene*)malloc(sizeof(t_scene));
	s->l = NULL;
	s->p = NULL;
	s->s = NULL;
	s->co = NULL;
	s->cy = NULL;
	s->para = NULL;
	s->elips = NULL;
	s->line = 1;
	return (s);
}

t_scene		*get_scene(t_list *curr)
{
	static t_scene	*s = NULL;
	static char		*name = NULL;
	int				i;

	i = 0;
	if (s == NULL)
		return (s = new_scene());
	name = ft_strdup((char*)curr->content);
	while (name[i])
	{
		if (name[++i] == '"')
		{
			s->name = ft_strsub(name, i, ft_strlen(name) - (i + 1));
			free(name);
			return (s);
		}
	}
	free(name);
	return (s);
}

t_scene		*ft_copy_scene(t_env *e)
{
	t_scene *cpy;

	cpy = new_scene();
	cpy->brillance = e->scene->brillance;
	cpy->light = e->scene->light;
	cpy->shadow = e->scene->shadow;
	cpy->l = copy_light(e->scene->l);
	cpy->s = copy_sphere(e->scene->s);
	cpy->cy = copy_cy(e->scene->cy);
	cpy->p = copy_plan(e->scene->p);
	cpy->co = copy_cone(e->scene->co);
	cpy->para = copy_para(e->scene->para);
	cpy->elips = copy_elips(e->scene->elips);
	cpy->camera.pos = e->scene->camera.pos;
	cpy->camera.look_at = e->scene->camera.look_at;
	cpy->camera.dir = e->scene->camera.dir;
	cpy->camera.axe_x = e->scene->camera.axe_x;
	cpy->camera.axe_y = e->scene->camera.axe_y;
	cpy->camera.axe_z = e->scene->camera.axe_z;
	cpy->camera.look_at_reset = e->scene->camera.look_at_reset;
	cpy->camera.posreset = e->scene->camera.posreset;
	cpy->camera.rotation = e->scene->camera.rotation;
	cpy->camera.x = e->scene->camera.x;
	cpy->camera.y = e->scene->camera.y;
	return (cpy);
}
