#define NK_INCLUDE_MEDIA
#define NK_INCLUDE_FONT_BAKING
#include "../../../includes/rt.h"
#include "../header/nuklear.h"
#include "../header/gui.h"

void	refresh_sphere(t_world *world, int i)
{
	t_sphere	*tmp;
	
	tmp = world->spheres_tmp;
	while(tmp)
	{
		if(tmp->id == world->id_save){
			tmp->pos = world->spheres[i].pos;
			tmp->radius = world->spheres[i].radius;
			tmp->color = world->spheres[i].color;
			tmp->chess = world->spheres[i].chess;
			tmp->rgba = world->spheres[i].rgba;
			tmp->reflection_coef = world->spheres[i].reflection_coef;
			tmp->refraction_coef = world->spheres[i].refraction_coef;
			break;
			}
		tmp = tmp->next;
	}
}

void	refresh_cone(t_world *world, int i)
{
	t_cone	*tmp;
	
	tmp = world->cones_tmp;
	while(tmp)
	{
		if(tmp->id == world->id_save){
            tmp->pos = world->cones[i].pos;
            tmp->up= world->cones[i].up;
			tmp->half_angle = world->cones[i].half_angle;
			tmp->color = world->cones[i].color;
			tmp->chess = world->cones[i].chess;
			// tmp->rgba = world->cones[i].rgba;
			tmp->reflection_coef = world->cones[i].reflection_coef;
			tmp->refraction_coef = world->cones[i].refraction_coef;
			break;
			}
		tmp = tmp->next;
	}
}

void	refresh_cylinder(t_world *world, int i)
{
	t_cylinder	*tmp;
	
	tmp = world->cylinders_tmp;
	while(tmp)
	{
		if(tmp->id == world->id_save){
            tmp->pos = world->cylinders[i].pos;
            tmp->up= world->cylinders[i].up;
			tmp->radius = world->cylinders[i].radius;
			tmp->color = world->cylinders[i].color;
			tmp->chess = world->cylinders[i].chess;
			// tmp->rgba = world->cones[i].rgba;
			tmp->reflection_coef = world->cylinders[i].reflection_coef;
			tmp->refraction_coef = world->cylinders[i].refraction_coef;
			break;
			}
		tmp = tmp->next;
	}
}

void	refresh_plane(t_world *world, int i)
{
	t_plane	*tmp;
	
	tmp = world->planes_tmp;
	while(tmp)
	{
		if(tmp->id == world->id_save){
            tmp->pos = world->planes[i].pos;
            tmp->up= world->planes[i].up;
			tmp->color = world->planes[i].color;
			tmp->chess = world->planes[i].chess;
			// tmp->rgba = world->cones[i].rgba;
			tmp->reflection_coef = world->planes[i].reflection_coef;
			tmp->refraction_coef = world->planes[i].refraction_coef;
			break;
			}
		tmp = tmp->next;
	}
}