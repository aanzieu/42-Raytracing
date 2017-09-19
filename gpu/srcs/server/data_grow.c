/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_grow.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 13:32:06 by aanzieu           #+#    #+#             */
/*   Updated: 2017/09/19 13:35:58 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cluster.h"

int					data_grow(t_data *data, size_t size)
{
	void	*new;
	size_t	new_total;

	new_total = data->total * size * 1.618;
	new = ft_memalloc(new_total);
	ft_memcpy(new, data->data, data->used);
	free(data->data);
	data->data = new;
	data->total = new_total;
	return (1);
}

int					data_recv(t_data *data, size_t size)
{
	if (!size)
		return (0);
	if (!data->total)
	{
		data->data = ft_memalloc(size);
		data->total = size;
		data->used = 0;
	}
	if (data->total >= data->used + size)
		return (1);
	if (data->total == 1)
		data->total++;
	return (data_grow(data, size));
}
