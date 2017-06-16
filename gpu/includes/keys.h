/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 10:50:12 by svilau            #+#    #+#             */
/*   Updated: 2017/06/16 12:59:26 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYS_H
# define KEYS_H

void				key_release_handler1(t_world *world, SDL_Event event);

void				key_release_handler2(t_world *world, SDL_Event event);

void				key_press_handler1(t_world *world, SDL_Event event);

void				key_press_handler2(t_world *world, SDL_Event event);

void				key_press_handler3(t_world *world, SDL_Event event);

void				key_press_handler4(t_world *world, SDL_Event event);

#endif
