/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 19:49:01 by dtoy              #+#    #+#             */
/*   Updated: 2019/10/28 19:49:07 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_xyz	find_wall_intersection(t_xy t, t_xy w1, t_xy w2, t_xyz p)
{
	t_xyz	i;
	t_xy	s1;
	t_xy	s2;
	float	s;
	float	f;

	s1.x = w2.x - w1.x;
	s1.y = w2.y - w1.y;
	s2.x = t.x - p.x;
	s2.y = t.y - p.y;
	s = (-s1.y * (w1.x - p.x) + s1.x *
	(w1.y - p.y)) / (-s2.x * s1.y + s1.x * s2.y);
	f = (s2.x * (w1.y - p.y) - s2.y *
	(w1.x - p.x)) / (-s2.x * s1.y + s1.x * s2.y);
	if (s >= 0 && s <= 1 && f >= 0 && f <= 1)
	{
		i.x = w1.x + (f * s1.x);
		i.y = w1.y + (f * s1.y);
		return (i);
	}
	i.x = -1;
	i.y = -1;
	return (i);
}

t_xy	find_t(t_player player, t_xyz p)
{
	t_xy	t;

	t.x = p.x + 10000 * player.pcos;
	t.y = p.y + 10000 * player.psin;
	return (t);
}

int		shoot_wall(t_doom *doom, t_player player, t_sectors *sect, t_pics *pic)
{
	int			sector;
	t_sectors	*s;
	t_xyz		p;
	t_xyz		i;

	if (doom->num_shots == SHOTS_NUM)
		doom->num_shots = 0;
	sector = player.sector;
	p = player.where;
	s = &sect[sector];
	if (doom->lookwall[sector] == -1)
		return (0);
	i = find_wall_intersection(find_t(player, p),
	s->vert[doom->lookwall[sector]], s->vert[doom->lookwall[sector] + 1], p);
	if (!i.x && !i.y)
		return (0);
	doom->shot_pics.p = i;
	doom->shot_pics.p.z = player.where.z + tanf(atanf(-player.yaw)) *
	(sqrtf(powf(i.x - doom->player.where.x, 2) +
	powf(i.y - doom->player.where.y, 2)));
	doom->shot_pics.wall = doom->lookwall[sector];
	doom->shot_pics.sector = sector;
	if (s->neighbors[doom->lookwall[sector]] < 0)
	{
		if (doom->shot_pics.p.z > s->ceil ||
		doom->shot_pics.p.z < s->floor)
			return (0);
		findpicpoints(doom, &doom->shot_pics,
		(float)(doom->img[doom->shot_pics.images[0][0]].w) / 270.f);
	}
	else
		return (0);
	pic[doom->num.pics + doom->num_shots] = doom->shot_pics;
	doom->num_shots++;
	return (0);
}
