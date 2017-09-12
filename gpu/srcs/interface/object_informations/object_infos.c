#define NK_INCLUDE_MEDIA
#define NK_INCLUDE_FONT_BAKING
#include "../../../includes/rt.h"
#include "../header/nuklear.h"
#include "../header/gui.h"

void	sphere_informations(t_world *world, struct nk_context *ctx, struct media *media)
{
    int	i = 0;
    t_intersection o;
    static const double s = 1.0/255.0;
    static struct	nk_color color ;

	while (i < world->spheres_len)
	{
		if (world->id_save == world->spheres[i].id)
		{
      nk_layout_row_begin(ctx, NK_STATIC, 60, 2);
      {
        nk_layout_row_push(ctx, 60);
        nk_image(ctx, media->sphere);
        nk_layout_row_push(ctx, 150);
        nk_text(ctx, "SPHERE", ft_strlen("SPHERE"), NK_TEXT_LEFT);
      }
      nk_layout_row_end(ctx);

      o.id_save = world->id_save;
			if (ui_widget_value_infos(ctx, media, &world->spheres[i].pos.x, "pos : X"))
				world->redraw = 1;
			else if (ui_widget_value_infos(ctx, media, &world->spheres[i].pos.y, "pos : Y"))
				world->redraw = 1;
			else if (ui_widget_value_infos(ctx, media, &world->spheres[i].pos.z, "pos : Z"))
				world->redraw = 1;
			else if (ui_widget_value_infos(ctx, media, &world->spheres[i].radius, "radius"))
        world->redraw = 1;
      else if (ui_widget_value_infos(ctx, media, &world->spheres[i].reflection_coef, "reflection_coef :"))
        world->redraw = 1;
      else if (ui_widget_value_infos(ctx, media, &world->spheres[i].refraction_coef, "refraction_coef :"))
        world->redraw = 1;
      else if (ui_widget_value_infos(ctx, media, &world->spheres[i].transparence_coef, "transparence_coef :"))
        world->redraw = 1;
      ui_header(ctx, media, "---- Colors ----");
      nk_layout_row_dynamic(ctx, 125, 1);

      get_color_for_gui(&color, world->spheres[i].color, s);
      if (nk_color_pick(ctx, &color, NK_RGB))
      {
          world->spheres[i].color.r = (double)color.r * s;
          world->spheres[i].color.g = (double)color.g * s;
          world->spheres[i].color.b = (double)color.b * s;
          world->redraw = 1;
      }
			refresh_sphere(world, i);
      ui_widget_centered(ctx, media, 10);
      ui_widget_centered(ctx, media, 30);
			if (nk_button_image_label(ctx, media->del, "Delete object", NK_TEXT_CENTERED))
			{
				remove_sphere(&world->spheres_tmp, &o);
				load_spheres(&world->spheres, world->spheres_tmp, &world->spheres_len);
				world->redraw = 1;
			}
			break;
		}
		i++;
	}
}

void	cone_informations(t_world *world, struct nk_context *ctx, struct media *media)
{
    int	i = 0;
    t_intersection o;
    static const double s = 1.0/255.0;
    static struct	nk_color color ;

    while (i < world->cones_len)
	{
		if (world->id_save == world->cones[i].id)
		{
      nk_layout_row_begin(ctx, NK_STATIC, 60, 2);
      {
        nk_layout_row_push(ctx, 60);
        nk_image(ctx, media->cone);
        nk_layout_row_push(ctx, 150);
        nk_text(ctx, "CONE", ft_strlen("CONE"), NK_TEXT_LEFT);
      }
      nk_layout_row_end(ctx);

      o.id_save = world->id_save;
			if (ui_widget_value_infos(ctx, media, &world->cones[i].pos.x, "pos  : X"))
				world->redraw = 1;
			else if (ui_widget_value_infos(ctx, media, &world->cones[i].pos.y, "pos  : Y"))
				world->redraw = 1;
			else if (ui_widget_value_infos(ctx, media, &world->cones[i].pos.z, "pos  : Z"))
        world->redraw = 1;
      else if (ui_widget_value_infos(ctx, media, &world->cones[i].up.x, "norm : X"))
				world->redraw = 1;
			else if (ui_widget_value_infos(ctx, media, &world->cones[i].up.y, "norm : Y"))
				world->redraw = 1;
			else if (ui_widget_value_infos(ctx, media, &world->cones[i].up.z, "norm : Z"))
				world->redraw = 1;
			else if (ui_widget_value_infos(ctx, media, &world->cones[i].height, "height :"))
				world->redraw = 1;
			else if (ui_widget_value_infos(ctx, media, &world->cones[i].half_angle, "radius"))
        world->redraw = 1;
      else if (ui_widget_value_infos(ctx, media, &world->cones[i].reflection_coef, "reflection_coef :"))
        world->redraw = 1;
      else if (ui_widget_value_infos(ctx, media, &world->cones[i].refraction_coef, "refraction_coef :"))
        world->redraw = 1;
      else if (ui_widget_value_infos(ctx, media, &world->cones[i].transparence_coef, "transparence_coef :"))
        world->redraw = 1;
      ui_header(ctx, media, "---- Colors ----");
      nk_layout_row_dynamic(ctx, 125, 1);
      get_color_for_gui(&color, world->cones[i].color, s);
      if (nk_color_pick(ctx, &color, NK_RGB))
      {
          world->cones[i].color.r = (double)color.r * s;
          world->cones[i].color.g = (double)color.g * s;
          world->cones[i].color.b = (double)color.b * s;
          world->redraw = 1;
      }
			refresh_cone(world, i);
      ui_widget_centered(ctx, media, 10);
      ui_widget_centered(ctx, media, 30);
      if (nk_button_image_label(ctx, media->del, "Delete object", NK_TEXT_CENTERED))
      {
        remove_cone(&world->cones_tmp, &o);
        load_cones(&world->cones, world->cones_tmp, &world->cones_len);
        world->redraw = 1;
      }
			break;
		}
		i++;
    }
}

void	cylinder_informations(t_world *world, struct nk_context *ctx, struct media *media)
{
    int	i = 0;
    t_intersection o;
    static const double s = 1.0/255.0;
    static struct	nk_color color ;

    while (i < world->cylinders_len)
	{
		if (world->id_save == world->cylinders[i].id)
		{
      nk_layout_row_begin(ctx, NK_STATIC, 60, 2);
      {
        nk_layout_row_push(ctx, 60);
        nk_image(ctx, media->cylinder);
        nk_layout_row_push(ctx, 150);
        nk_text(ctx, "CYLINDER", ft_strlen("CYLINDER"), NK_TEXT_LEFT);
      }
      nk_layout_row_end(ctx);

      o.id_save = world->id_save;
			if (ui_widget_value_infos(ctx, media, &world->cylinders[i].pos.x, "pos  : X"))
				world->redraw = 1;
			else if (ui_widget_value_infos(ctx, media, &world->cylinders[i].pos.y, "pos  : Y"))
				world->redraw = 1;
			else if (ui_widget_value_infos(ctx, media, &world->cylinders[i].pos.z, "pos  : Z"))
        world->redraw = 1;
      else if (ui_widget_value_infos(ctx, media, &world->cylinders[i].up.x, "norm : X"))
				world->redraw = 1;
			else if (ui_widget_value_infos(ctx, media, &world->cylinders[i].up.y, "norm : Y"))
				world->redraw = 1;
			else if (ui_widget_value_infos(ctx, media, &world->cylinders[i].up.z, "norm : Z"))
				world->redraw = 1;
			else if (ui_widget_value_infos(ctx, media, &world->cylinders[i].height, "height :"))
        world->redraw = 1;
			else if (ui_widget_value_infos(ctx, media, &world->cylinders[i].radius, "radius :"))
        world->redraw = 1;
      else if (ui_widget_value_infos(ctx, media, &world->cylinders[i].reflection_coef, "reflection_coef :"))
        world->redraw = 1;
      else if (ui_widget_value_infos(ctx, media, &world->cylinders[i].refraction_coef, "refraction_coef :"))
        world->redraw = 1;
      else if (ui_widget_value_infos(ctx, media, &world->cylinders[i].transparence_coef, "transparence_coef :"))
        world->redraw = 1;
      ui_header(ctx, media, "---- Colors ----");
      nk_layout_row_dynamic(ctx, 125, 1);
      get_color_for_gui(&color, world->cylinders[i].color, s);
      if (nk_color_pick(ctx, &color, NK_RGB))
      {
          world->cylinders[i].color.r = (double)color.r * s;
          world->cylinders[i].color.g = (double)color.g * s;
          world->cylinders[i].color.b = (double)color.b * s;
          world->redraw = 1;
      }
			refresh_cylinder(world, i);
      ui_widget_centered(ctx, media, 10);
      ui_widget_centered(ctx, media, 30);
      if (nk_button_image_label(ctx, media->del, "Delete object", NK_TEXT_CENTERED))
      {
        remove_cylinder(&world->cylinders_tmp, &o);
        load_cylinders(&world->cylinders, world->cylinders_tmp, &world->cylinders_len);
        world->redraw = 1;
      }

			break;
		}
		i++;
    }
}

void	plane_informations(t_world *world, struct nk_context *ctx, struct media *media)
{
    int	i = 0;
    t_intersection o;
    static const double s = 1.0/255.0;
    static struct	nk_color color ;

    while (i < world->planes_len)
	{
		if (world->id_save == world->planes[i].id)
		{
      nk_layout_row_begin(ctx, NK_STATIC, 60, 2);
      {
        nk_layout_row_push(ctx, 60);
        nk_image(ctx, media->plane);
        nk_layout_row_push(ctx, 150);
        nk_text(ctx, "PLANE", ft_strlen("PLANE"), NK_TEXT_LEFT);
      }
      nk_layout_row_end(ctx);

      o.id_save = world->id_save;
			if (ui_widget_value_infos(ctx, media, &world->planes[i].pos.x, "pos  : X"))
				world->redraw = 1;
			else if (ui_widget_value_infos(ctx, media, &world->planes[i].pos.y, "pos  : Y"))
				world->redraw = 1;
			else if (ui_widget_value_infos(ctx, media, &world->planes[i].pos.z, "pos  : Z"))
        world->redraw = 1;
      else if (ui_widget_value_infos(ctx, media, &world->planes[i].up.x, "norm : X"))
				world->redraw = 1;
			else if (ui_widget_value_infos(ctx, media, &world->planes[i].up.y, "norm : Y"))
				world->redraw = 1;
			else if (ui_widget_value_infos(ctx, media, &world->planes[i].up.z, "norm : Z"))
				world->redraw = 1;
      else if (ui_widget_value_infos(ctx, media, &world->planes[i].reflection_coef, "reflection_coef :"))
        world->redraw = 1;
      else if (ui_widget_value_infos(ctx, media, &world->planes[i].refraction_coef, "refraction_coef :"))
        world->redraw = 1;
      else if (ui_widget_value_infos(ctx, media, &world->planes[i].transparence_coef, "transparence_coef :"))
        world->redraw = 1;
      ui_header(ctx, media, "---- Colors ----");
      nk_layout_row_dynamic(ctx, 125, 1);
      get_color_for_gui(&color, world->planes[i].color, s);
      if (nk_color_pick(ctx, &color, NK_RGB))
      {
          world->planes[i].color.r = (double)color.r * s;
          world->planes[i].color.g = (double)color.g * s;
          world->planes[i].color.b = (double)color.b * s;
          world->redraw = 1;
      }
			refresh_plane(world, i);
      ui_widget_centered(ctx, media, 10);
      ui_widget_centered(ctx, media, 30);
      if (nk_button_image_label(ctx, media->del, "Delete object", NK_TEXT_CENTERED))
      {
        remove_plane(&world->planes_tmp, &o);
        load_planes(&world->planes, world->planes_tmp, &world->planes_len);
        world->redraw = 1;
      }

			break;
		}
		i++;
    }
}

void	torus_informations(t_world *world, struct nk_context *ctx, struct media *media)
{
    int	i = 0;
    t_intersection o;
    static const double s = 1.0/255.0;
    static struct	nk_color color ;

    while (i < world->torus_len)
	{
		if (world->id_save == world->torus[i].id)
		{
      nk_layout_row_begin(ctx, NK_STATIC, 60, 2);
      {
        nk_layout_row_push(ctx, 60);
        nk_image(ctx, media->torus);
        nk_layout_row_push(ctx, 150);
        nk_text(ctx, "TORUS", ft_strlen("TORUS"), NK_TEXT_LEFT);
      }
      nk_layout_row_end(ctx);

      o.id_save = world->id_save;
			if (ui_widget_value_infos(ctx, media, &world->torus[i].pos.x, "pos  : X"))
				world->redraw = 1;
			else if (ui_widget_value_infos(ctx, media, &world->torus[i].pos.y, "pos  : Y"))
				world->redraw = 1;
			else if (ui_widget_value_infos(ctx, media, &world->torus[i].pos.z, "pos  : Z"))
        world->redraw = 1;
			else if (ui_widget_value_infos(ctx, media, &world->torus[i].radius_small, "outter radius :"))
        world->redraw = 1;
			else if (ui_widget_value_infos(ctx, media, &world->torus[i].radius_big, "inner radius :"))
        world->redraw = 1;
      else if (ui_widget_value_infos(ctx, media, &world->torus[i].reflection_coef, "reflection_coef :"))
        world->redraw = 1;
      else if (ui_widget_value_infos(ctx, media, &world->torus[i].refraction_coef, "refraction_coef :"))
        world->redraw = 1;
      else if (ui_widget_value_infos(ctx, media, &world->torus[i].transparence_coef, "transparence_coef :"))
        world->redraw = 1;
      ui_header(ctx, media, "---- Colors ----");
      nk_layout_row_dynamic(ctx, 125, 1);
      get_color_for_gui(&color, world->torus[i].color, s);
      if (nk_color_pick(ctx, &color, NK_RGB))
      {
          world->torus[i].color.r = (double)color.r * s;
          world->torus[i].color.g = (double)color.g * s;
          world->torus[i].color.b = (double)color.b * s;
          world->redraw = 1;
      }
      refresh_torus(world, i);
      ui_widget_centered(ctx, media, 10);
      ui_widget_centered(ctx, media, 30);
      if (nk_button_image_label(ctx, media->del, "Delete object", NK_TEXT_CENTERED))
      {
        remove_torus(&world->torus_tmp, &o);
        load_torus(&world->torus, world->torus_tmp, &world->torus_len);
        world->redraw = 1;
      }
			break;
		}
		i++;
    }
}
