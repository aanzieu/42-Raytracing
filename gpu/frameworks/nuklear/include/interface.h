/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 16:05:35 by xpouzenc          #+#    #+#             */
/*   Updated: 2017/09/26 16:14:28 by xpouzenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERFACE_H
# define INTERFACE_H

# include "../../../includes/rt.h"

# define STB_IMAGE_IMPLEMENTATION
# include "stb_image.h"

# define NK_IMPLEMENTATION
# include "nuklear.h"

# define MIN(a,b) ((a) < (b) ? (a) : (b))
# define LEN(a) (sizeof(a)/sizeof(a)[0])

void	gui_calls(struct file_browser *browser, struct nk_context *ctx,\
		struct media *media, t_world *world);

#endif
