/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 13:44:32 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/15 13:44:49 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

int		sqr(int x)
{
	return (x * x);
}

/*
**	Возвращает расстояние между двумя точками
*/

float	distance(t_v2 p1, t_v2 p2)
{
	t_v2	tmp;
	float	distance;

	tmp.x = p2.x - p1.x;
	tmp.y = p2.y - p1.y;
	distance = sqrt((tmp.x * tmp.x) + (tmp.y * tmp.y));
	return (distance);
}

/*
**	l1, l2 - точки отрезка, к которому ищем расстояние
**	p - точка, от которой ищем расстояние
**	hit - проекция точки на отрезок
**	Возвращает расстояние между отрезком и точкой
*/

float	line_distance(t_v2 l1, t_v2 l2, t_v2 p, t_v2 *hit)
{
	float	dist;
	float	t;
	t_v2	proj;

	dist = (sqr(l1.x - l2.x) + sqr(l1.y - l2.y));
	if (dist == 0)
	{
		*hit = l1;
		return (distance(l1, p));
	}
	t = ((p.x - l1.x) * (l2.x - l1.x) + (p.y - l1.y) * (l2.y - l1.y)) / dist;
	t = clamp(t, 0, 1);
	proj.x = l1.x + t * (l2.x - l1.x);
	proj.y = l1.y + t * (l2.y - l1.y);
	if (hit != NULL)
		*hit = proj;
	dist = distance(p, proj);
	return (dist);
}
