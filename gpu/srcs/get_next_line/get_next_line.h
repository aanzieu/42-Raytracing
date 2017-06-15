/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilau <svilau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/15 09:41:54 by svilau            #+#    #+#             */
/*   Updated: 2016/06/21 13:36:22 by svilau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include "../../libft/libft.h"

# define BUFF_SIZE 1234

typedef struct		s_gnl
{
    char			*str;
    int				fd;
    struct s_gnl	*next;
    struct s_gnl	*prw;
}					t_gnl;

int					get_next_line(const int fd, char **line);

#endif
