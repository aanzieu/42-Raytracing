/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 19:25:50 by aanzieu           #+#    #+#             */
/*   Updated: 2017/04/28 12:53:17 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		find_bckslach(char *str, int i)
{
	if (!(*str))
		return (-1);
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

static int		one_line(char **str, char **line, int size)
{
	char	*tmp;

	if (!(*line = ft_strsub(*str, 0, size)))
		return (-1);
	tmp = *str;
	if (!(*str = ft_strdup(ft_strchr(tmp, '\n') + 1)))
		return (-1);
	free(tmp);
	tmp = NULL;
	return (1);
}

static t_gnl	*find_list(t_gnl *list, t_gnl *new, int fd)
{
	t_gnl	*tmp;

	if (!list)
	{
		if (!(list = (t_gnl*)malloc(sizeof(t_gnl))))
			return (NULL);
		list->fd = fd;
		list->str = ft_strdup("");
		list->next = NULL;
		list->prw = list;
	}
	list = list->prw;
	tmp = list;
	while (list->fd != fd && list->next)
		list = list->next;
	if (fd == list->fd)
		return (list);
	if (!(new = malloc(sizeof(t_gnl))))
		return (NULL);
	new->fd = fd;
	new->str = ft_strdup("");
	new->next = NULL;
	new->prw = tmp;
	list->next = new;
	return (new);
}

static int		read_line(int fd, char **str, char **line, int size)
{
	int		ret;
	char	*tmp;
	char	buf[BUFF_SIZE + 1];

	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		if (ret == -1)
			return (-1);
		buf[ret] = '\0';
		tmp = *str;
		*str = ft_strjoin(tmp, buf);
		free(tmp);
		tmp = NULL;
		if ((size = find_bckslach(*str, 0)) > -1)
			return (one_line(str, line, size));
	}
	return (-42);
}

int				get_next_line(const int fd, char **line)
{
	static t_gnl	*list = NULL;
	t_gnl			*new;
	char			*tmp;
	int				end;
	int				ret;

	end = 0;
	new = NULL;
	if (fd < 0 || !line || BUFF_SIZE < 1 || fd == 1)
		return (-1);
	list = find_list(list, new, fd);
	if ((end = find_bckslach(list->str, 0)) > -1)
		return (one_line(&list->str, line, end));
	if ((ret = read_line(fd, &list->str, line, end)) != -42)
		return (ret);
	ret = (list->str[0] != '\0') ? 1 : 0;
	ft_swap_str(&list->str, &tmp);
	end = find_bckslach(tmp, 0) == -1 ? ft_strlen(tmp) : find_bckslach(tmp, 0);
	*line = ft_strsub(tmp, 0, end);
	list->str = ft_strsub(tmp, end + 1, ft_strlen(tmp));
	free(tmp);
	return (ret);
}
