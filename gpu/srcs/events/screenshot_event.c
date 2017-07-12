/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot_event.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: PZC <PZC@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/12 15:27:36 by PZC               #+#    #+#             */
/*   Updated: 2017/07/12 17:31:15 by PZC              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <dirent.h>

static void	write_file_name(t_world *w, size_t nb)
{
	char *path;

	path = ft_strjoin("screenshots/image", ft_itoa(nb));
	path = ft_strjoin(path, ".bmp");
	SDL_SaveBMP(w->window.screen, path);
	ft_strdel(&path);
}

void		savebmp(t_world *world)
{
    DIR* rep = NULL;
    size_t nb = 0;

    struct dirent *f = NULL; /* Déclaration d'un pointeur vers la structure dirent. */

    rep = opendir("screenshots");
    if (rep == NULL)
        exit(1);

    while ((f = readdir(rep)) != NULL)
	{
		if (ft_strncmp(f->d_name, ".", ft_strlen(".")))
		{
			nb++;
			printf("Le fichier lu s'appelle '%s'\n", f->d_name);
		}
	}
    printf("Il y a %s fichier(s)\n", ft_itoa(nb));

    if (closedir(rep) == -1)
        exit(-1);

    if (nb == 0)
		SDL_SaveBMP(world->window.screen, "screenshots/image.bmp");
	else
		write_file_name(world, nb);
}
