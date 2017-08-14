/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_cylinders.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 18:07:37 by aanzieu           #+#    #+#             */
/*   Updated: 2017/06/16 18:11:50 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

static unsigned int		count_cylinders(t_cylinder *cylinders)
{
	t_cylinder		*p;
	unsigned int	size;

	size = 0;
	p = cylinders;
	while (p)
	{
		size++;
		p = p->next;
	}
	return (size);
}

void					load_cylinders(t_cylinder **cylinders,
								t_cylinder *cylinders_tmp, int *cylinders_len)
{
	unsigned int	i;
	t_cylinder		*tmp;

	i = 0;
	*cylinders_len = count_cylinders(cylinders_tmp);
	*cylinders = (t_cylinder*)malloc(sizeof(t_cylinder) * *cylinders_len);
	tmp = cylinders_tmp;
	while (tmp)
	{
		(*cylinders)[i] = *tmp;
		tmp = tmp->next;
		i++;
	}
}
