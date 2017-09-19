/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot_event.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: PZC <PZC@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 18:50:50 by xpouzenc          #+#    #+#             */
/*   Updated: 2017/09/19 13:04:26 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>
#include <display.h>
#include "parse.h"

static void		update_surface(int *a_h, SDL_Surface *img)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < WIN_HEIGHT)
	{
		j = 0;
		while (j < WIN_WIDTH)
		{
			pixel_to_image(img, j, i, a_h[i * WIN_WIDTH + j]);
			j++;
		}
		i++;
	}
}

static void		write_file_name(t_world *w, int nb)
{
	char			*path;
	char			*num;
	char			*ext;
	SDL_Surface		*img;
	int				ret;

	num = NULL;
	if (nb != -1)
	{
		num = ft_itoa(nb + 1);
		path = ft_strjoin("screenshots/image", num);
		ft_strdel(&num);
	}
	else
		path = ft_strdup("screenshots/image");
	ext = ft_strjoin(path, ".bmp");
	ft_printf("insave\n");
	ft_strdel(&path);
	img = SDL_CreateRGBSurface(0, WIN_WIDTH, WIN_HEIGHT, 32, 0, 0, 0, 0);
	update_surface(w->a_h, img);
	if ((ret = SDL_SaveBMP(img, ext)) != 0)
		show_error("saving png file error");
	ft_putstr("Snapshot ! -> ");
	ft_putendl(ext);
	ft_strdel(&ext);
}

/*
** Save a bitmap format image using SDL_SaveBMP
** We check if the "screenshots" dir exist and how many files are in it
** to determinate the id of the new image
*/

void			savebmp(t_world *world)
{
	DIR				*rep;
	int				nb;
	struct dirent	*f;

	nb = -1;
	rep = NULL;
	f = NULL;
	if ((rep = opendir("screenshots")) == NULL)
		system("mkdir screenshots");
	if ((rep = opendir("screenshots")) == NULL)
		show_error("open screenshots directory error");
	while ((f = readdir(rep)) != NULL)
	{
		if (ft_strncmp(f->d_name, "image", ft_strlen("image")) == 0)
		{
			if (ft_atoi(f->d_name + 5) > nb)
				nb = ft_atoi(f->d_name + 5);
		}
	}
	if (closedir(rep) == -1)
		show_error("close screenshots directory error");
	write_file_name(world, nb);
}
