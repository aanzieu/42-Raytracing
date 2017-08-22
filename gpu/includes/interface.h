/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/21 19:04:06 by PZC               #+#    #+#             */
/*   Updated: 2017/08/22 16:14:16 by xpouzenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERFACE_H
# define INTERFACE_H

# include "rt.h"

void				init_interface(t_world *world);
SDL_Rect			interface_set_position(int x, int y);
void 				create_loader(t_world *world);

#endif
