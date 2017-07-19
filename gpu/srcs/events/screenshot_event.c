/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot_event.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 18:50:50 by xpouzenc          #+#    #+#             */
/*   Updated: 2017/07/19 16:58:41 by xpouzenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "parse.h"

static void	write_file_name(t_world *w, size_t nb)
{
	char	*path;
	char	*num;
	char	*ext;
	int		ret;

	num = ft_itoa(nb);
	path = ft_strjoin("screenshots/image", num);
	ft_strdel(&num);
	ext = ft_strjoin(path, ".bmp");
	ft_strdel(&path);
	if ((ret = SDL_SaveBMP(w->window.screen, ext)) == -1)
		show_error("saving png file error");
	ft_strdel(&ext);
}

void		savebmp(t_world *world)
{
	DIR				*rep;
	size_t			nb;
	struct dirent	*f;

	nb = 0;
	rep = NULL;
	f = NULL;
	if ((rep = opendir("screenshots")) == NULL)
		system("mkdir ./screenshots");
	if ((rep = opendir("screenshots")) == NULL)
		show_error("open screenshots directory error");
	while ((f = readdir(rep)) != NULL)
	{
		if (ft_strncmp(f->d_name, ".", ft_strlen(".")))
			nb++;
	}
	if (closedir(rep) == -1)
		show_error("close screenshots directory error");
	write_file_name(world, nb);
}
