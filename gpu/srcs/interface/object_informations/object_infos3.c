#define NK_INCLUDE_MEDIA
#define NK_INCLUDE_FONT_BAKING
#include "../../../includes/rt.h"
#include "../header/nuklear.h"
#include "../header/gui.h"

void	hyperboloid_informations(t_world *world, struct nk_context *ctx, struct media *media)
{
    int	i = 0;
    t_intersection o;
    static const double s = 1.0/255.0;
    static struct	nk_color color ;

    while (i < world->hyperboloids_len)
	{
		if (world->id_save == world->hyperboloids[i].id)
		{
      nk_layout_row_begin(ctx, NK_STATIC, 60, 2);
        {
          nk_layout_row_push(ctx, 60);
          nk_image(ctx, media->hyperboloid);
          nk_layout_row_push(ctx, 150);
          nk_text(ctx, "HYPERBOLOID", ft_strlen("HYPERBOLOID"), NK_TEXT_LEFT);
        }
        nk_layout_row_end(ctx);

      o.id_save = world->id_save;
			if (ui_widget_value_infos(ctx, media, &world->hyperboloids[i].top.x, "pos  : X"))
				world->redraw = 1;
			else if (ui_widget_value_infos(ctx, media, &world->hyperboloids[i].top.y, "pos  : Y"))
				world->redraw = 1;
			else if (ui_widget_value_infos(ctx, media, &world->hyperboloids[i].top.z, "pos  : Z"))
        world->redraw = 1;
			else if (ui_widget_value_infos(ctx, media, &world->hyperboloids[i].normal.x, "normal  : X"))
				world->redraw = 1;
			else if (ui_widget_value_infos(ctx, media, &world->hyperboloids[i].normal.y, "normal  : Y"))
				world->redraw = 1;
			else if (ui_widget_value_infos(ctx, media, &world->hyperboloids[i].normal.z, "normal  : Z"))
        world->redraw = 1;
			else if (ui_widget_value_infos(ctx, media, &world->hyperboloids[i].radius, "radius :"))
        world->redraw = 1;
			else if (ui_widget_value_infos(ctx, media, &world->hyperboloids[i].maxm, "maxm :"))
        world->redraw = 1;
      else if (ui_widget_value_infos(ctx, media, &world->hyperboloids[i].reflection_coef, "reflection_coef :"))
        world->redraw = 1;
      else if (ui_widget_value_infos(ctx, media, &world->hyperboloids[i].refraction_coef, "refraction_coef :"))
        world->redraw = 1;
      else if (ui_widget_value_infos(ctx, media, &world->hyperboloids[i].transparence_coef, "transparence_coef :"))
        world->redraw = 1;
      ui_header(ctx, media, "---- Colors ----");
      nk_layout_row_dynamic(ctx, 125, 1);
      get_color_for_gui(&color, world->hyperboloids[i].color, s);
      if (nk_color_pick(ctx, &color, NK_RGB))
      {
          world->hyperboloids[i].color.r = (double)color.r * s;
          world->hyperboloids[i].color.g = (double)color.g * s;
          world->hyperboloids[i].color.b = (double)color.b * s;
          world->redraw = 1;
      }
			refresh_hyperboloid(world, i);
      ui_widget_centered(ctx, media, 10);
      ui_widget_centered(ctx, media, 30);
      if (nk_button_image_label(ctx, media->del, "Delete object", NK_TEXT_CENTERED))
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
