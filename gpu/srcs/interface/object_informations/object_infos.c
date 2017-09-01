#define NK_INCLUDE_MEDIA
#define NK_INCLUDE_FONT_BAKING
#include "../../../includes/rt.h"
#include "../header/nuklear.h"
#include "../header/gui.h"

void	sphere_informations(t_world *world, struct nk_context *ctx, struct media *media)
{
    int	i = 0;
    static const double s = 1.0/255.0;
    static struct	nk_color color ;
	
	while(i < world->spheres_len)
	{
		if(world->id_save == world->spheres[i].id)
		{
			if(ui_widget_value_infos(ctx, media, &world->spheres[i].pos.x, "pos : X"))
				world->redraw = 1;
			else if(ui_widget_value_infos(ctx, media, &world->spheres[i].pos.y, "pos : Y"))
				world->redraw = 1;	
			else if(ui_widget_value_infos(ctx, media, &world->spheres[i].pos.z, "pos : Z"))
				world->redraw = 1;		
			else if(ui_widget_value_infos(ctx, media, &world->spheres[i].radius, "radius"))
                world->redraw = 1;
                ui_header(ctx, media, "---- Colors ----");
            nk_layout_row_dynamic(ctx, 125, 1);
            if(nk_color_pick(ctx, &color, NK_RGB))
            {
                world->spheres[i].color.r = (double)color.r * s;
                world->spheres[i].color.g = (double)color.g * s;
                world->spheres[i].color.b = (double)color.b * s;
                world->redraw = 1;
            }
			refresh_sphere(world, i);			
			break;	
		}
		i++;
	}
}

void	cone_informations(t_world *world, struct nk_context *ctx, struct media *media)
{
    int	i = 0;
    static const double s = 1.0/255.0;
    static struct	nk_color color ;

    while(i < world->cones_len)
	{
		if(world->id_save == world->cones[i].id)
		{
			if(ui_widget_value_infos(ctx, media, &world->cones[i].pos.x, "pos  : X"))
				world->redraw = 1;
			else if(ui_widget_value_infos(ctx, media, &world->cones[i].pos.y, "pos  : Y"))
				world->redraw = 1;	
			else if(ui_widget_value_infos(ctx, media, &world->cones[i].pos.z, "pos  : Z"))
                world->redraw = 1;
            else if(ui_widget_value_infos(ctx, media, &world->cones[i].up.x, "norm : X"))
				world->redraw = 1;
			else if(ui_widget_value_infos(ctx, media, &world->cones[i].up.y, "norm : Y"))
				world->redraw = 1;	
			else if(ui_widget_value_infos(ctx, media, &world->cones[i].up.z, "norm : Z"))
				world->redraw = 1;		
			else if(ui_widget_value_infos(ctx, media, &world->cones[i].half_angle, "radius"))
                world->redraw = 1;
            ui_header(ctx, media, "---- Colors ----");
            nk_layout_row_dynamic(ctx, 125, 1);
            if(nk_color_pick(ctx, &color, NK_RGB))
            {
                world->cones[i].color.r = (double)color.r * s;
                world->cones[i].color.g = (double)color.g * s;
                world->cones[i].color.b = (double)color.b * s;
                world->redraw = 1;
            }
			refresh_cone(world, i);			
			break;	
		}
		i++;
    }
}

void	cylinder_informations(t_world *world, struct nk_context *ctx, struct media *media)
{
    int	i = 0;
    static const double s = 1.0/255.0;
    static struct	nk_color color ;

    while(i < world->cylinders_len)
	{
		if(world->id_save == world->cylinders[i].id)
		{
			if(ui_widget_value_infos(ctx, media, &world->cylinders[i].pos.x, "pos  : X"))
				world->redraw = 1;
			else if(ui_widget_value_infos(ctx, media, &world->cylinders[i].pos.y, "pos  : Y"))
				world->redraw = 1;	
			else if(ui_widget_value_infos(ctx, media, &world->cylinders[i].pos.z, "pos  : Z"))
                world->redraw = 1;
            else if(ui_widget_value_infos(ctx, media, &world->cylinders[i].up.x, "norm : X"))
				world->redraw = 1;
			else if(ui_widget_value_infos(ctx, media, &world->cylinders[i].up.y, "norm : Y"))
				world->redraw = 1;	
			else if(ui_widget_value_infos(ctx, media, &world->cylinders[i].up.z, "norm : Z"))
				world->redraw = 1;		
			else if(ui_widget_value_infos(ctx, media, &world->cylinders[i].radius, "radius"))
                world->redraw = 1;
            ui_header(ctx, media, "---- Colors ----");
            nk_layout_row_dynamic(ctx, 125, 1);
            if(nk_color_pick(ctx, &color, NK_RGB))
            {
                world->cylinders[i].color.r = (double)color.r * s;
                world->cylinders[i].color.g = (double)color.g * s;
                world->cylinders[i].color.b = (double)color.b * s;
                world->redraw = 1;
            }
			refresh_cylinder(world, i);			
			break;	
		}
		i++;
    }
}

void	plane_informations(t_world *world, struct nk_context *ctx, struct media *media)
{
    int	i = 0;
    static const double s = 1.0/255.0;
    static struct	nk_color color ;

    while(i < world->planes_len)
	{
		if(world->id_save == world->planes[i].id)
		{
			if(ui_widget_value_infos(ctx, media, &world->planes[i].pos.x, "pos  : X"))
				world->redraw = 1;
			else if(ui_widget_value_infos(ctx, media, &world->planes[i].pos.y, "pos  : Y"))
				world->redraw = 1;	
			else if(ui_widget_value_infos(ctx, media, &world->planes[i].pos.z, "pos  : Z"))
                world->redraw = 1;
            else if(ui_widget_value_infos(ctx, media, &world->planes[i].up.x, "norm : X"))
				world->redraw = 1;
			else if(ui_widget_value_infos(ctx, media, &world->planes[i].up.y, "norm : Y"))
				world->redraw = 1;	
			else if(ui_widget_value_infos(ctx, media, &world->planes[i].up.z, "norm : Z"))
				world->redraw = 1;		
            ui_header(ctx, media, "---- Colors ----");
            nk_layout_row_dynamic(ctx, 125, 1);
            if(nk_color_pick(ctx, &color, NK_RGB))
            {
                world->planes[i].color.r = (double)color.r * s;
                world->planes[i].color.g = (double)color.g * s;
                world->planes[i].color.b = (double)color.b * s;
                world->redraw = 1;
            }
			refresh_plane(world, i);			
			break;	
		}
		i++;
    }
}