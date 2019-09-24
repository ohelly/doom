#include "doom.h"

/*
**	Возвращает 1 если отрезки p1q1 и p2q2 пересекаются
*/

int	lines_intersect(t_v2 p0, t_v2 p1, t_v2 p2, t_v2 p3)
{
	t_v2	s1;
	t_v2	s2;
	t_v2	hit;
	float	s;
	float	t;
	float	div;

	s1.x = p1.x - p0.x;
	s1.y = p1.y - p0.y;
	s2.x = p3.x - p2.x;
	s2.y = p3.y - p2.y;
	div = -s2.x * s1.y + s1.x * s2.y;
	if (div == 0)
		return (0);
	s = (-s1.y * (p0.x - p2.x) + s1.x * (p0.y - p2.y)) / div;
	t = ( s2.x * (p0.y - p2.y) - s2.y * (p0.x - p2.x)) / div;
	if (s > 0 && s < 1 && t > 0 && t < 1)
	{
		hit.x = p0.x + (t * s1.x);
		hit.y = p0.y + (t * s1.y);
		if ((v2_compare(hit, p0) || v2_compare(hit, p1)) && (v2_compare(hit, p2) || v2_compare(hit, p3)))
			return (0);
		return (1);
	}
	return (0);
}

/*
**	Возвращает 1 если отрезок p1p2 пересекается с какой-либо из стен
*/

int	lines_intersect_loop(t_doom *doom, t_v2 p1, t_v2 p2)
{
	t_v2	p3;
	t_v2	p4;
	int		i;

	i = 0;
	while (i < doom->walls->count - 1)
	{
		p3 = doom->verts->list[doom->walls->wall[i].vert_one].pos;
		p4 = doom->verts->list[doom->walls->wall[i].vert_two].pos;
		if (lines_intersect(p1, p2, p3, p4))
		{
			printf("Line intersects with another wall.\n");
			return (1);
		}
		i++;
	}
	return (0);
}