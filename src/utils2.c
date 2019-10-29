/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 00:51:11 by dtoy              #+#    #+#             */
/*   Updated: 2019/10/29 01:59:48 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		sqr(int x)
{
	return (x * x);
}

/*
**	l1, l2 - точки отрезка, к которому ищем расстояние
**	p - точка, от которой ищем расстояние
**	hit - проекция точки на отрезок
**	Возвращает расстояние между отрезком и точкой
*/

float	line_distance(t_xy l1, t_xy l2, t_xy p)
{
	float	dist;
	float	t;
	t_xy	proj;

	dist = (sqr(l1.x - l2.x) + sqr(l1.y - l2.y));
	if (dist == 0)
		return (distance(l1, p));
	t = ((p.x - l1.x) * (l2.x - l1.x) +
	(p.y - l1.y) * (l2.y - l1.y)) / dist;
	t = CLAMP(t, 0, 1);
	proj.x = l1.x + t * (l2.x - l1.x);
	proj.y = l1.y + t * (l2.y - l1.y);
	dist = distance(p, proj);
	if (distance(l1, p) < dist)
		dist = distance(l1, p);
	else if (distance(l2, p) < dist)
		dist = distance(l2, p);
	return (dist);
}

int		overlap(float a0, float a1, float b0, float b1)
{
	return ((MIN(a0, a1) <= MAX(b0, b1) && MIN(b0, b1) <= MAX(a0, a1)));
}
