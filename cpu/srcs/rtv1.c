/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 13:30:18 by aanzieu           #+#    #+#             */
/*   Updated: 2017/06/15 13:38:07 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rtv1.h"
/*
static int		view_loop(t_env *e)
{
	if(one_keypressed(&e->keys))
		check_pressed_keys(&e->keys, e->scene, e);
	mlx_del(e);
	return (0);
}
*/
int				expose_hook(t_env *e)
{
	mlx_clear_window(e->mlx, e->win);
	launch_rtv1(e);
//	bayer_color(e);
//	black_white(e);
//	negative_color(e);
	mlx_put_image_to_window(e->mlx, e->win, e->image->img, 0, 0);
	return (0);
}

static	void	init_viewplane(t_env *e)
{
	if ((e->mlx = mlx_init()) == NULL)
		ft_putendl_fd("Error : Can't init MLX", 1);
	if ((e->win = mlx_new_window(e->mlx, WW, WH, e->scene->name)) == NULL)
		ft_putendl_fd("Error : Can't init Window", 1);
	if ((e->image = new_image(e)) == NULL)
		ft_putendl_fd("Error : Impossible to Malloc Image", 1);
	ft_bzero(&e->keys, sizeof(*(&e->keys)));
	e->mouse_event = 1;
}

static void		first_read(char *argv, int ret, int fd)
{
	char	*line;
	char	*tmp;

	if ((fd = open(argv, O_RDONLY)) < 0)
		ft_putendl_fd("Error : can't open file", 1);
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		tmp = ft_strtrim(line);
		while (tmp)
		{
			if (ft_strnequ(tmp, "<?xml", ft_strlen("<?xml")))
			{
				free(line);
				free(tmp);
				close(fd);
				return ;
			}
			else
				ft_putendl_fd("Not an XML File, choose another one, thx", 1);
		}
	}
	if (ret == -1)
		ft_putendl_fd("Error : Not a Correct File", 1);
}

int				main(int argc, char **argv)
{
	t_env *e;

	if (argc == 2)
	{
		if (!(e = (t_env*)ft_memalloc(sizeof(t_env))))
			ft_putendl_fd("Error Malloc Struct Environement", 1);
		first_read(argv[1], 0, 0);
		parse_rtv1(e, argv[1]);
		init_viewplane(e);
		mlx_expose_hook(e->win, expose_hook, e);
		mlx_hook(e->win, 2, 2, key_hook, e);
		mlx_hook(e->win, 4, (1L << 2), mousepress, e);
		mlx_hook(e->win, 5, (1L << 3), mouserelease, e);
		mlx_hook(e->win, 6, (1L << 6), motionnotify_env, e);//&e->scene->camera);
//		mlx_loop_hook(e->mlx, view_loop, e);
		mlx_loop(e->mlx);
	}
	else
		ft_putendl_fd("Usage : ./rtv1 [files.xml]", 1);
	return (0);
}
