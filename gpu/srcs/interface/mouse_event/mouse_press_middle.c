#define NK_INCLUDE_MEDIA
#define NK_INCLUDE_FONT_BAKING
#include "../../../includes/rt.h"
#include "../../cuda/cudaheader/gpu_rt.h"
#include "../header/nuklear.h"
#include "../header/gui.h"
#include "float.h"

int     remove_object_3(t_world *world, t_intersection *i)
{
  if (i->type == 'h')
  {
  	remove_hyperboloid(&world->hyperboloids_tmp, i);
  	load_hyperboloids(&world->hyperboloids, world->hyperboloids_tmp,
      &world->hyperboloids_len);
  }
  else if (i->type == 'a')
  {
  	remove_paraboloid(&world->paraboloids_tmp, i);
  	load_paraboloids(&world->paraboloids, world->paraboloids_tmp,
      &world->paraboloids_len);
  }
  else
    return (0);
  return (1);
}

int			remove_object_2(t_world *world, t_intersection *i)
{
  if (i->type == 'o')
  {
  	remove_torus(&world->torus_tmp, i);
  	load_torus(&world->torus, world->torus_tmp, &world->torus_len);
  }
  else if (i->type == 'm')
  {
  	remove_mobius(&world->mobius_tmp, i);
  	load_mobius(&world->mobius, world->mobius_tmp, &world->mobius_len);
  }
  else if (i->type == 'd')
  {
  	remove_disk(&world->disks_tmp, i);
  	load_disks(&world->disks, world->disks_tmp, &world->disks_len);
  }
  else if (i->type == 'b')
  {
  	remove_cube(&world->cubes_tmp, i);
  	load_cubes(&world->cubes, world->cubes_tmp, &world->cubes_len);
  }
  else
    return (remove_object_3(world, i));
  return (1);
}

int			remove_object(t_world *world, t_intersection *i)
{
    if (i->type != '0')
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
    		load_cylinders(&world->cylinders, world->cylinders_tmp,
          &world->cylinders_len);
      }
      else if (i->type == 'p')
      {
      	remove_plane(&world->planes_tmp, i);
      	load_planes(&world->planes, world->planes_tmp, &world->planes_len);
      }
      else if (remove_object_2(world, i) == 1)
        return (1);
    }
	return (0);
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
	return (0);
}
