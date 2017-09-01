#define NK_INCLUDE_MEDIA
#define NK_INCLUDE_FONT_BAKING
#include "../../../includes/rt.h"
#include "../../cuda/cudaheader/gpu_rt.h"
#include "../header/nuklear.h"
#include "../header/gui.h"
#include "float.h"

int			remove_object_next(t_world *world, t_intersection *i)
{
    (void)i;
    (void)world;
    if(i->type != '0')
    {
        if (i->type == 'p')
	    {
	    	remove_plane(&world->planes_tmp, i);
	    	load_planes(&world->planes, world->planes_tmp, &world->planes_len);		
        }
        return(1);
    }
    return(0);
}

int			remove_object(t_world *world, t_intersection *i)
{
    if(i->type != '0')
    {
	    if (i->type == 's')
	    {
	    	remove_sphere(&world->spheres_tmp, i);
	    	load_spheres(&world->spheres, world->spheres_tmp, &world->spheres_len);		
        }
        else if (i->type == 'x')
	    {
	    	remove_cone(&world->cones_tmp, i);
	    	load_cones(&world->cones, world->cones_tmp, &world->cones_len);		
        }
        else if (i->type == 'c')
	    {
		    remove_cylinder(&world->cylinders_tmp, i);
    		load_cylinders(&world->cylinders, world->cylinders_tmp, &world->cylinders_len);		
        }
        return(remove_object_next(world, i));
    }    
	return(0);
}

int		mousepress_middle(struct nk_context *ctx, t_world *world, struct nk_vec2 pos)
{
	t_ray      		ray;
	t_intersection	intersection;
	t_vec2d			padding;

	intersection.t = DBL_MAX;
	intersection.type = '0';
	intersection.id = -1;
	if(ctx->input.mouse.buttons[NK_BUTTON_MIDDLE].down)
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
			if(remove_object(world, &intersection) == 1)
				world->redraw = 1;
		}
	}
	return(0);
}