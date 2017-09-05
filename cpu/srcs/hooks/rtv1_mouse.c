/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_mouse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 13:37:01 by aanzieu           #+#    #+#             */
/*   Updated: 2017/06/14 18:56:46 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rtv1.h"

void			remove_object(t_scene *scene, t_object *i)
{
	if (i->type == SPHERE)
		remove_sphere(&scene->s, i->sphere);
	else if (i->type == CONE)
		remove_cone(&scene->co, i->cone);
	else if (i->type == CYLINDRE)
		remove_cyl(&scene->cy, i->cy);
	else if (i->type == PLAN)
		remove_plan(&scene->p, i->plan);
}

int				mousepress(int button, int x, int y, t_env *e)
{
	t_ray		ray;
	t_object	*obj;

	cam_position(&e->scene->camera, x, y);
	ray = get_raytracing(&e->scene->camera);
	obj = find_intersection(ray, e->scene);
//	if (e->block_events)
//		return (0);
//	if (button == 1)
//		e->mouse.pressed_mouse = 1;
	if (obj->tclose != INFINITY)
	{
		if (button == 2)
			remove_object(e->scene, obj);
	}
	if (button == 5)
		point_vector_scal(&e->scene->camera.pos, &e->scene->camera.axe_z, 1);
	else if (button == 4)
		point_vector_scal(&e->scene->camera.pos, &e->scene->camera.axe_z, -1);
	free(obj);
	if (y < 0)
		return (0);
	e->mouse.id |= 1 << button;
	mlx_del(e);
	return (0);
}

int				mouserelease(int button, int x, int y, t_env *e)
{
	(void)x;
	(void)y;
	e->mouse.id &= ~(1 << button);
//	if (button == 1 || button == 0)
//	{
//		e->selected_object = NULL;
//		e->mouse.pressed_mouse = 0;
//	}
	return (0);
}

int				motionnotify_env(int x, int y, t_env *e)
{
	double w;
	double h;
//
	e->mouse.lastx = e->mouse.x;
	e->mouse.lasty = e->mouse.y;
	e->mouse.x = x;
	e->mouse.y = y;
	if (e->mouse.id & (1 << 1))
	{
		w = ((e->mouse.x - e->mouse.lastx));// - WW / 2);// % 36;// / 8);
		h = ((e->mouse.y - e->mouse.lasty));// - WW / 2);// % 36;// / 8);
		if (w < 0.0)
			vector_rot_y(&e->scene->camera.axe_z, &e->scene->camera.axe_x, deg_to_radian(-10));
		if(w > 0.0)
			vector_rot_y(&e->scene->camera.axe_z, &e->scene->camera.axe_x, deg_to_radian(10));
		if (h < 0.0)
			vector_rot_x(&e->scene->camera.axe_y, &e->scene->camera.axe_z, deg_to_radian(-10));
		if (h > 0.0)
			vector_rot_x(&e->scene->camera.axe_y, &e->scene->camera.axe_z, deg_to_radian(10));
//		e->scene->camera.look_at.x = w ;
//		e->scene->camera.look_at.y = h ;
//		cam_axes(&e->scene->camera);
//		printf("x position :%lf | y position :%lf\n", w, h);
	}
	if (e->mouse.id)
		mlx_del(e);
	return (0);
}
