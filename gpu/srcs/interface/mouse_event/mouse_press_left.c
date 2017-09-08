/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/24 21:17:41 by aanzieu           #+#    #+#             */
/*   Updated: 2017/08/24 21:29:08 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define NK_INCLUDE_MEDIA
#define NK_INCLUDE_FONT_BAKING
#include "../../../includes/rt.h"
#include "../../cuda/cudaheader/gpu_rt.h"
#include "../header/nuklear.h"
#include "../header/gui.h"
#include "float.h"

int	find_object(t_world *world, t_intersection *inter, t_vec2d *pos,struct nk_context *ctx)
{
	int	i = 0;
	t_sphere *tmp = world->spheres_tmp;

	(void)ctx;
	float	vitesse;
	t_ray ray1;
	t_ray ray2;

	//Fonctionne MAL a revoir
	t_vec3d coeff1;
	t_vec3d coeff2;
	get_up_left(world);
	get_ray_direction(*(world), &ray1, world->xy.x, world->xy.y);
	get_ray_direction(*(world), &ray2, pos->x, pos->y);
	if(inter->type == 's')
	{
		while(i < world->spheres_len)
		{
			// printf("test\n");
			if(world->id_save == world->spheres[i].id)
			{
				vitesse = vector_length(vector_substract(world->spheres[i].pos, ray1.origin)) * 0.01;
				coeff1 = vector_substract(world->spheres[i].pos, ray1.dir);
				coeff2 = vector_substract(world->spheres[i].pos, ray2.dir);
				world->spheres[i].pos.x += (coeff1.x - coeff2.x);// * vitesse;
				while(tmp)
				{
					if(tmp->id == world->id_save){
						tmp->pos.x += (coeff1.x - coeff2.x);
						break;
					}
					tmp = tmp->next;
				}
				return(1);
			}
			i++;
		}
	}
	world->xy.x = pos->x;
	world->xy.y = pos->y;
	return(0);
	
}

int	move_object(t_world *world, struct nk_context *ctx, t_vec2d *pos, t_intersection *i)
{
	int	find = 1;
	
	if(ctx->input.keyboard.keys[NK_KEY_X].down != 0)
	{
		if((find = find_object(world, i, pos, ctx)) == 1)
			return(1);
	}
	return(0);
		
}


int		mousepress_left(struct nk_context *ctx, t_world *world, struct nk_vec2 pos)
{
	t_ray      		ray;
	t_intersection	intersection;
	t_vec2d			padding;

	intersection.t = DBL_MAX;
	intersection.type = '0';
	intersection.id = -1;
	if(ctx->input.mouse.buttons[NK_BUTTON_LEFT].down)
	{
		padding.x = ctx->input.mouse.pos.x - pos.x;;
		padding.y = ctx->input.mouse.pos.y - pos.y - 40;
		if(padding.x < 0 || padding.y < 0 || padding.x > WIN_WIDTH || padding.y > WIN_HEIGHT)
			return (0);	
		get_up_left(world);
		get_ray_direction(*(world), &ray, padding.x, padding.y);
		get_closest_intersection(*(world), ray, &intersection);
		if(intersection.t != INFINITY)
		{	
			world->id_save = intersection.id_save;
			world->ob_save = intersection.type;			
			world->keys.select = 1;
			if(move_object(world, ctx, &padding, &intersection))
				printf("%d id \n", world->id_save);
			printf("%d id world \n", world->id_save);
			printf("%d id inter \n", intersection.id_save);
			world->redraw = 1;
				
		}
	}
	return(0);
}