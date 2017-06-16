/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 10:50:12 by svilau            #+#    #+#             */
/*   Updated: 2017/06/16 12:54:07 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_H
# define DISPLAY_H
# include <SDL2/SDL.h>

# define BLACK 0
# define WHITE 16777215
# define RED 16737380
# define BLUE 49151
# define GREEN 8190976
# define ORANGE 16753920
# define DARK_PINK 16711935
# define SKY_BLUE 8900331
# define LIGHT_BROWN 12624511

void	pixel_to_image(SDL_Surface *surface, int x, int y, Uint32 color);

#endif
