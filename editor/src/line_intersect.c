#include "doom.h"

int	line_on_segment(t_v2 p, t_v2 q, t_v2 r)
{
	if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
		q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))
		return (1);
	return (0);
}

/*
** Возвращаемые значения:
**	0 - колинеарны
**	1 - по часовой
**	2 - против часовой
*/

int line_orientation(t_v2 p, t_v2 q, t_v2 r)
{
	int val;

	val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
	if (val == 0)
		return (0);
	return (val > 0 ? 1 : 2);
}

/*
**	Возвращает 1 если отрезки p1q1 и p2q2 пересекаются
*/

int	lines_intersect(t_v2 p1, t_v2 q1, t_v2 p2, t_v2 q2)
{
	int o1;
	int o2;
	int o3;
	int o4;

	o1 = line_orientation(p1, q1, p2);
	o2 = line_orientation(p1, q1, q2);
	o3 = line_orientation(p2, q2, p1);
	o4 = line_orientation(p2, q2, q1);
	if (o1 != o2 && o3 != o4)
		return (1);
	if (o1 == 0 && line_on_segment(p1, p2, q1))
		return (1);
	if (o2 == 0 && line_on_segment(p1, q2, q1))
		return (1);
	if (o3 == 0 && line_on_segment(p2, p1, q2))
		return (1);
	if (o4 == 0 && line_on_segment(p2, q1, q2))
		return (1);
	return (0);
}

/*
**	Возвращает 1 если точка p принадлежит какой-либо из вершин
*/

int	point_belongs_to_vertex(t_doom *doom, t_v2 p)
{
	int			i;
	t_vertex	v;

	i = 0;
	while (i < doom->verts->count - 1)
	{
		v = doom->verts->list[i];
		if (p.x == v.pos.x && p.y == v.pos.y)
			return (1);
		i++;
	}
	return (0);
}

/*
**	Возвращает 1 если линия p1p2 пересекается с какой-либо из стен
*/

int	lines_intersect_loop(t_doom *doom, t_v2 p1, t_v2 p2)
{
	t_v2	p3;
	t_v2	p4;
	int		i;

	i = 0;
	while (i < doom->walls->count)
	{
		p3 = doom->verts->list[doom->walls->wall[i].vert_one].pos;
		p4 = doom->verts->list[doom->walls->wall[i].vert_two].pos;
		if (!(p1.x == p3.x && p1.y == p3.y && p2.x == p4.x && p2.y == p4.y) &&
			!point_belongs_to_vertex(doom, p1) &&
			!point_belongs_to_vertex(doom, p2) &&
			lines_intersect(p1, p2, p3, p4))
			return (1);
		i++;
	}
	return (0);
}