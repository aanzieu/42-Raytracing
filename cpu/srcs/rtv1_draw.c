/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 15:09:26 by aanzieu           #+#    #+#             */
/*   Updated: 2017/06/15 13:37:57 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rtv1.h"
/*
static void			draw_p_with_thread(t_thread_cpy *e, int x, int y,
		unsigned int color)
{
	void		*mlx;
	size_t		pixel;

	mlx = e->mlx;
	if (y <= WH && y >= 0 && x >= 0 && x <= WW)
	{
		pixel = ((WW * y) + x) * (e->bpp);
		color = mlx_get_color_value(mlx, color);
		if (e->endian == 0)
		{
			(e->img_s + pixel)[2] = color >> 16;
			(e->img_s + pixel)[1] = (color & 0x00FF00) >> 8;
			(e->img_s + pixel)[0] = color & 0x0000FF;
		}
		else
		{
			(e->img_s + pixel)[0] = color >> 16;
			(e->img_s + pixel)[1] = (color & 0x00FF00) >> 8;
			(e->img_s + pixel)[2] = color & 0x0000FF;
		}
	}
}
*/

void	draw_p(t_thread_cpy *e, int x, int y, int color)
{
	if (x < 0 || x >= WW || y < 0 || y >= WH)
		return ;
	((unsigned int*)e->img_s)[y * WW + x] = color;
}


void			fast_mode(t_thread_cpy *cpy, unsigned int x, unsigned int y)
{
	if (x % FAST_RENDER_PRECISION || y % FAST_RENDER_PRECISION)
		return ;
	cam_position(&cpy->scene->camera, x, y);
	cpy->r = get_raytracing(&cpy->scene->camera);
	cpy->color = get_color_object(cpy->r, cpy->scene);
	cpy->co = get_special_color(get_color(cpy->color), 0, 0);
	draw_p(cpy, x, y, cpy->co);
//	draw_p_with_thread(cpy, x, y, cpy->c[y * WW + x]);
}

void	fast_mode_color(t_thread_cpy *cpy, int x, int y, int color)
{
	int			i;
	int			j;

	(void)color;
	cam_position(&cpy->scene->camera, x, y);
	cpy->r = get_raytracing(&cpy->scene->camera);
	cpy->color = get_color_object(cpy->r, cpy->scene);
//	cpy->co = get_color(cpy->color);
	cpy->co = get_special_color(get_color(cpy->color), 0, 0);
	j = 0;
	while(j < FAST_RENDER_PRECISION)
	{
		i = 0;
		while(i < FAST_RENDER_PRECISION)
		{
			draw_p(cpy, x + i, y + j, cpy->co);
			i++;
		}
		j++;
	}
}

static	void		*perform_rtv1(void *arg)
{
	t_thread_input	*thread;
	t_thread_cpy	*cpy;
	int			x;
	int			y;

	thread = (t_thread_input *)arg;
	if (!(cpy = (t_thread_cpy*)ft_memalloc(sizeof(t_thread_cpy))))
		ft_putendl_fd("Error : Can't init thread\n", 1);
	thread_copy(thread->e, cpy);
	y = (thread->th * (WH / NB_TH));
	while (y < (thread->th + 1) * ((WH / NB_TH)))
	{
		x = 0;
		while (x < WW)
		{
			if ((!(x % FAST_RENDER_PRECISION) || (!(y % FAST_RENDER_PRECISION))) && thread->e->mouse_event)
			{
				fast_mode_color(cpy, x, y, cpy->co);
				x += FAST_RENDER_PRECISION;
			}
			else
			{
				cam_position(&cpy->scene->camera, x, y);
				cpy->r = get_raytracing(&cpy->scene->camera);
				cpy->color = get_color_object(cpy->r, cpy->scene);
				cpy->co = get_special_color(get_color(cpy->color), 0, 0);
				draw_p(cpy, x, y, cpy->co);
				x++;
			}
		}
		if(thread->e->mouse_event)
			y +=FAST_RENDER_PRECISION;
		else
			y++;
	}
	thread_free_lists(cpy);
	free(cpy);
	pthread_exit(0);
}

int					launch_rtv1(t_env *e)
{
	t_thread_input		tab[NB_TH];
	int					i;

	i = -1;
	while (++i < NB_TH)
	{
		tab[i].th = i;
		tab[i].e = e;
		if (pthread_create(&e->thread[i], NULL, &perform_rtv1, &tab[i]))
			ft_putendl_fd("Error : Can't init launch_rtv1\n", 1);
	}
	i = -1;
	while (++i < NB_TH)
		pthread_join(e->thread[i], NULL);
	return (0);
}

/*
** Test pour l'antialising non fonctionnel
** static int	ft_raytrace(t_thread_cpy *cpy, double x, double y)
** {
** double p;
** p = 0.0;
** while (y < cpy->y + 1 && (x = cpy->x) > -1)
** {
** while (x < cpy->x + 1 && (p += 1) > 0)
** {
** cam_position(&cpy->scene->camera, x, y);
** cpy->r = get_raytracing(&cpy->scene->camera);
** py->color = get_color_object(cpy->r, cpy->scene);
** cpy->c = get_color(cpy->color);
** x = x + (1.0);
** }
** y = y + (1.0);
** }
** return (0);
** }
*/
