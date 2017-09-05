/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_equation_resolve.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 16:32:15 by aanzieu           #+#    #+#             */
/*   Updated: 2017/06/13 16:42:07 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmath.h"

double		positive_solution(t_solve solve)
{
	if (solve.none == -1)
		return (INFINITY);
	return (solve.s1 > 0 ? solve.s2 : solve.s1);
}

t_solve		equation_second_degres(t_eq e)
{
	t_solve	rslt;

	e.delta = ((e.b * e.b) - (4 * e.a * e.c));
	if (e.delta < 0)
		rslt.none = -1;
	if (e.delta >= 0)
	{
		rslt.s1 = (-e.b + (sqrt(e.delta))) / (2 * e.a);
		rslt.s2 = (-e.b - (sqrt(e.delta))) / (2 * e.a);
		rslt.none = 1;
	}
	return (rslt);
}

t_solve		second_degres(double a, double b, double c)
{
	double	delta;
	t_solve	rslt;

	delta = ((b * b) - (4 * a * c));
	if (delta < 0)
		rslt.none = -1;
	if (delta >= 0)
	{
		rslt.s1 = (-b + (sqrt(delta))) / (2 * a);
		rslt.s2 = (-b - (sqrt(delta))) / (2 * a);
		rslt.none = 1;
	}
	return (rslt);
}
