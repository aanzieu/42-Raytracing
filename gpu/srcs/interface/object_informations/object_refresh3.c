#define NK_INCLUDE_MEDIA
#define NK_INCLUDE_FONT_BAKING
#include "../../../includes/rt.h"
#include "../header/nuklear.h"
#include "../header/gui.h"

void	refresh_triangle(t_world *world, int i)
{
	t_triangle	*tmp;

	tmp = world->triangles_tmp;
	while (tmp)
	{
		if (tmp->id == world->id_save){
      tmp->pos = world->triangles[i].pos;
      tmp->up = world->triangles[i].up;
     	tmp->v1 = world->triangles[i].v1;
     	tmp->v2 = world->triangles[i].v2;
			tmp->color = world->triangles[i].color;
			tmp->chess = world->triangles[i].chess;
			// tmp->rgba = world->cones[i].rgba;
			tmp->reflection_coef = world->triangles[i].reflection_coef;
			tmp->refraction_coef = world->triangles[i].refraction_coef;
			tmp->transparence_coef = world->triangles[i].transparence_coef;
			break ;
			}
		tmp = tmp->next;
	}
}
