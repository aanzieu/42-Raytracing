#define NK_INCLUDE_MEDIA
#define NK_INCLUDE_FONT_BAKING
#include "../../../includes/rt.h"
#include "../header/nuklear.h"
#include "../header/gui.h"

void	mobius_informations(t_world *world, struct nk_context *ctx, struct media *media)
{
    int	i = 0;
    t_intersection o;
    static const double s = 1.0/255.0;
    static struct	nk_color color ;

    while (i < world->mobius_len)
	{
		if (world->id_save == world->mobius[i].id)
		{
      o.id_save = world->id_save;
			if (ui_widget_value_infos(ctx, media, &world->mobius[i].pos.x, "pos  : X"))
				world->redraw = 1;
			else if (ui_widget_value_infos(ctx, media, &world->mobius[i].pos.y, "pos  : Y"))
				world->redraw = 1;
			else if (ui_widget_value_infos(ctx, media, &world->mobius[i].pos.z, "pos  : Z"))
        world->redraw = 1;
			else if (ui_widget_value_infos(ctx, media, &world->mobius[i].radius, "radius :"))
        world->redraw = 1;
      else if (ui_widget_value_infos(ctx, media, &world->mobius[i].reflection_coef, "reflection_coef :"))
        world->redraw = 1;
      else if (ui_widget_value_infos(ctx, media, &world->mobius[i].refraction_coef, "refraction_coef :"))
        world->redraw = 1;
      else if (ui_widget_value_infos(ctx, media, &world->mobius[i].transparence_coef, "transparence_coef :"))
        world->redraw = 1;
      ui_header(ctx, media, "---- Colors ----");
      nk_layout_row_dynamic(ctx, 125, 1);
      if (nk_color_pick(ctx, &color, NK_RGB))
      {
          world->mobius[i].color.r = (double)color.r * s;
          world->mobius[i].color.g = (double)color.g * s;
          world->mobius[i].color.b = (double)color.b * s;
          world->redraw = 1;
      }
			refresh_mobius(world, i);
      ui_widget_centered(ctx, media, 30);
      if (nk_button_label(ctx, "Delete object"))
      {
        remove_mobius(&world->mobius_tmp, &o);
        load_mobius(&world->mobius, world->mobius_tmp, &world->mobius_len);
        world->redraw = 1;
      }
			break;
		}
		i++;
    }
}

void	disk_informations(t_world *world, struct nk_context *ctx, struct media *media)
{
    int	i = 0;
    t_intersection o;
    static const double s = 1.0/255.0;
    static struct	nk_color color ;

    while (i < world->disks_len)
	{
		if (world->id_save == world->disks[i].id)
		{
      o.id_save = world->id_save;
			if (ui_widget_value_infos(ctx, media, &world->disks[i].pos.x, "pos  : X"))
				world->redraw = 1;
			else if (ui_widget_value_infos(ctx, media, &world->disks[i].pos.y, "pos  : Y"))
				world->redraw = 1;
			else if (ui_widget_value_infos(ctx, media, &world->disks[i].pos.z, "pos  : Z"))
        world->redraw = 1;
      else if (ui_widget_value_infos(ctx, media, &world->disks[i].up.x, "norm : X"))
				world->redraw = 1;
			else if (ui_widget_value_infos(ctx, media, &world->disks[i].up.y, "norm : Y"))
				world->redraw = 1;
			else if (ui_widget_value_infos(ctx, media, &world->disks[i].up.z, "norm : Z"))
				world->redraw = 1;
			else if (ui_widget_value_infos(ctx, media, &world->disks[i].radius, "radius :"))
				world->redraw = 1;
      else if (ui_widget_value_infos(ctx, media, &world->disks[i].reflection_coef, "reflection_coef :"))
        world->redraw = 1;
      else if (ui_widget_value_infos(ctx, media, &world->disks[i].refraction_coef, "refraction_coef :"))
        world->redraw = 1;
      else if (ui_widget_value_infos(ctx, media, &world->disks[i].transparence_coef, "transparence_coef :"))
        world->redraw = 1;
      ui_header(ctx, media, "---- Colors ----");
      nk_layout_row_dynamic(ctx, 125, 1);
      if (nk_color_pick(ctx, &color, NK_RGB))
      {
          world->disks[i].color.r = (double)color.r * s;
          world->disks[i].color.g = (double)color.g * s;
          world->disks[i].color.b = (double)color.b * s;
          world->redraw = 1;
      }
			refresh_disk(world, i);
      ui_widget_centered(ctx, media, 30);
      if (nk_button_label(ctx, "Delete object"))
      {
        remove_disk(&world->disks_tmp, &o);
        load_disks(&world->disks, world->disks_tmp, &world->disks_len);
        world->redraw = 1;
      }
			break;
		}
		i++;
    }
}

void	cube_informations(t_world *world, struct nk_context *ctx, struct media *media)
{
    int	i = 0;
    t_intersection o;
    static const double s = 1.0/255.0;
    static struct	nk_color color ;

    while (i < world->cubes_len)
	{
		if (world->id_save == world->cubes[i].id)
		{
      o.id_save = world->id_save;
			if (ui_widget_value_infos(ctx, media, &world->cubes[i].min.x, "min  : X"))
				world->redraw = 1;
			else if (ui_widget_value_infos(ctx, media, &world->cubes[i].min.y, "min  : Y"))
				world->redraw = 1;
			else if (ui_widget_value_infos(ctx, media, &world->cubes[i].min.z, "min  : Z"))
        world->redraw = 1;
			else if (ui_widget_value_infos(ctx, media, &world->cubes[i].max.x, "max  : X"))
				world->redraw = 1;
			else if (ui_widget_value_infos(ctx, media, &world->cubes[i].max.y, "max  : Y"))
				world->redraw = 1;
			else if (ui_widget_value_infos(ctx, media, &world->cubes[i].max.z, "max  : Z"))
        world->redraw = 1;
      else if (ui_widget_value_infos(ctx, media, &world->cubes[i].reflection_coef, "reflection_coef :"))
        world->redraw = 1;
      else if (ui_widget_value_infos(ctx, media, &world->cubes[i].refraction_coef, "refraction_coef :"))
        world->redraw = 1;
      else if (ui_widget_value_infos(ctx, media, &world->cubes[i].transparence_coef, "transparence_coef :"))
        world->redraw = 1;
      ui_header(ctx, media, "---- Colors ----");
      nk_layout_row_dynamic(ctx, 125, 1);
      if (nk_color_pick(ctx, &color, NK_RGB))
      {
          world->cubes[i].color.r = (double)color.r * s;
          world->cubes[i].color.g = (double)color.g * s;
          world->cubes[i].color.b = (double)color.b * s;
          world->redraw = 1;
      }
			refresh_cube(world, i);
      ui_widget_centered(ctx, media, 30);
      if (nk_button_label(ctx, "Delete object"))
      {
        remove_cube(&world->cubes_tmp, &o);
        load_cubes(&world->cubes, world->cubes_tmp, &world->cubes_len);
        world->redraw = 1;
      }
			break;
		}
		i++;
    }
}

void	triangle_informations(t_world *world, struct nk_context *ctx, struct media *media)
{
    int	i = 0;
    t_intersection o;
    static const double s = 1.0/255.0;
    static struct	nk_color color ;

    while (i < world->triangles_len)
	{
		if (world->id_save == world->triangles[i].id)
		{
      o.id_save = world->id_save;
			if (ui_widget_value_infos(ctx, media, &world->triangles[i].pos.x, "pos  : X"))
				world->redraw = 1;
			else if (ui_widget_value_infos(ctx, media, &world->triangles[i].pos.y, "pos  : Y"))
				world->redraw = 1;
			else if (ui_widget_value_infos(ctx, media, &world->triangles[i].pos.z, "pos  : Z"))
        world->redraw = 1;
      else if (ui_widget_value_infos(ctx, media, &world->triangles[i].v1.x, "side 1 : X"))
				world->redraw = 1;
			else if (ui_widget_value_infos(ctx, media, &world->triangles[i].v1.y, "side 1 : Y"))
				world->redraw = 1;
			else if (ui_widget_value_infos(ctx, media, &world->triangles[i].v1.z, "side 1 : Z"))
				world->redraw = 1;
      else if (ui_widget_value_infos(ctx, media, &world->triangles[i].v2.x, "side 2 : X"))
				world->redraw = 1;
			else if (ui_widget_value_infos(ctx, media, &world->triangles[i].v2.y, "side 2 : Y"))
				world->redraw = 1;
			else if (ui_widget_value_infos(ctx, media, &world->triangles[i].v2.z, "side 2 : Z"))
				world->redraw = 1;
      else if (ui_widget_value_infos(ctx, media, &world->triangles[i].up.x, "norm : X"))
				world->redraw = 1;
			else if (ui_widget_value_infos(ctx, media, &world->triangles[i].up.y, "norm : Y"))
				world->redraw = 1;
			else if (ui_widget_value_infos(ctx, media, &world->triangles[i].up.z, "norm : Z"))
				world->redraw = 1;
      else if (ui_widget_value_infos(ctx, media, &world->triangles[i].reflection_coef, "reflection_coef :"))
        world->redraw = 1;
      else if (ui_widget_value_infos(ctx, media, &world->triangles[i].refraction_coef, "refraction_coef :"))
        world->redraw = 1;
      else if (ui_widget_value_infos(ctx, media, &world->triangles[i].transparence_coef, "transparence_coef :"))
        world->redraw = 1;
      ui_header(ctx, media, "---- Colors ----");
      nk_layout_row_dynamic(ctx, 125, 1);
      if (nk_color_pick(ctx, &color, NK_RGB))
      {
          world->triangles[i].color.r = (double)color.r * s;
          world->triangles[i].color.g = (double)color.g * s;
          world->triangles[i].color.b = (double)color.b * s;
          world->redraw = 1;
      }
			refresh_triangle(world, i);
      ui_widget_centered(ctx, media, 30);
      if (nk_button_label(ctx, "Delete object"))
      {
        remove_triangle(&world->triangles_tmp, &o);
        load_triangles(&world->triangles, world->triangles_tmp, &world->triangles_len);
        world->redraw = 1;
      }
			break;
		}
		i++;
    }
}

void	paraboloid_informations(t_world *world, struct nk_context *ctx, struct media *media)
{
    int	i = 0;
    t_intersection o;
    static const double s = 1.0/255.0;
    static struct	nk_color color ;

    while (i < world->paraboloids_len)
	{
    o.id_save = world->id_save;
		if (world->id_save == world->paraboloids[i].id)
		{
			if (ui_widget_value_infos(ctx, media, &world->paraboloids[i].top.x, "pos  : X"))
				world->redraw = 1;
			else if (ui_widget_value_infos(ctx, media, &world->paraboloids[i].top.y, "pos  : Y"))
				world->redraw = 1;
			else if (ui_widget_value_infos(ctx, media, &world->paraboloids[i].top.z, "pos  : Z"))
        world->redraw = 1;
			else if (ui_widget_value_infos(ctx, media, &world->paraboloids[i].normal.x, "normal  : X"))
				world->redraw = 1;
			else if (ui_widget_value_infos(ctx, media, &world->paraboloids[i].normal.y, "normal  : Y"))
				world->redraw = 1;
			else if (ui_widget_value_infos(ctx, media, &world->paraboloids[i].normal.z, "normal  : Z"))
        world->redraw = 1;
			else if (ui_widget_value_infos(ctx, media, &world->paraboloids[i].distance, "distance :"))
        world->redraw = 1;
			else if (ui_widget_value_infos(ctx, media, &world->paraboloids[i].maxm, "maxm :"))
        world->redraw = 1;
      else if (ui_widget_value_infos(ctx, media, &world->paraboloids[i].reflection_coef, "reflection_coef :"))
        world->redraw = 1;
      else if (ui_widget_value_infos(ctx, media, &world->paraboloids[i].refraction_coef, "refraction_coef :"))
        world->redraw = 1;
      else if (ui_widget_value_infos(ctx, media, &world->paraboloids[i].transparence_coef, "transparence_coef :"))
        world->redraw = 1;
      ui_header(ctx, media, "---- Colors ----");
      nk_layout_row_dynamic(ctx, 125, 1);
      if (nk_color_pick(ctx, &color, NK_RGB))
      {
          world->cubes[i].color.r = (double)color.r * s;
          world->cubes[i].color.g = (double)color.g * s;
          world->cubes[i].color.b = (double)color.b * s;
          world->redraw = 1;
      }
			refresh_paraboloid(world, i);
      ui_widget_centered(ctx, media, 30);
      if (nk_button_label(ctx, "Delete object"))
      {
        remove_hyperboloid(&world->hyperboloids_tmp, &o);
        load_hyperboloids(&world->hyperboloids, world->hyperboloids_tmp, &world->hyperboloids_len);
        world->redraw = 1;
      }
			break;
		}
		i++;
    }
}
