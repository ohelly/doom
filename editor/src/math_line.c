#include "doom.h"

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

	dist = distance(l1, l2);
	if (dist == 0)
	{
		*hit = l1;
		return (distance(l1, p));
	}
	t = dot(v2_sub(p, l2), v2_sub(l1, l2)) / dist;
	t = clamp(t, 0, 1);
	proj = v2_mult(v2_addf(l1, t), v2_sub(l2, l1));
	if (hit != NULL)
		*hit = proj;
	return (distance(p, proj));
}