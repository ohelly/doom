/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_intersect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 17:50:33 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/13 19:03:22 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

/*
**	Возвращает 1 если отрезки p1q1 и p2q2 пересекаются
*/

int		lines_intersect(t_v2 p0, t_v2 p1, t_v2 p2, t_v2 p3)
{
	t_intersect	str;

	str.s1.x = p1.x - p0.x;
	str.s1.y = p1.y - p0.y;
	str.s2.x = p3.x - p2.x;
	str.s2.y = p3.y - p2.y;
	str.div = -str.s2.x * str.s1.y + str.s1.x * str.s2.y;
	if (str.div == 0)
		return (0);
	str.s = (-str.s1.y * (p0.x - p2.x) + str.s1.x * (p0.y - p2.y)) / str.div;
	str.t = (str.s2.x * (p0.y - p2.y) - str.s2.y * (p0.x - p2.x)) / str.div;
	if (str.s > 0 && str.s < 1 && str.t > 0 && str.t < 1)
	{
		str.hit.x = p0.x + (str.t * str.s1.x);
		str.hit.y = p0.y + (str.t * str.s1.y);
		if ((v2_compare(str.hit, p0) || v2_compare(str.hit, p1)) &&
		(v2_compare(str.hit, p2) || v2_compare(str.hit, p3)))
			return (0);
		return (1);
	}
	return (0);
}

/*
**	Возвращает 1 если отрезок p1p2 пересекается с какой-либо из стен
*/

int		lines_intersect_loop(t_doom *doom, t_v2 p1, t_v2 p2)
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
			doom->hud->msg = "Line intersects with another wall";
			return (1);
		}
		i++;
	}
	return (0);
}
