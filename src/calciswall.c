/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calciswall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 19:23:01 by dtoy              #+#    #+#             */
/*   Updated: 2019/10/29 17:31:50 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	px_p1x(t_xy *p, t_xy *p1, t_xy d, t_player *player)
{
	p->x = player->where.x;
	p->y = player->where.y;
	p1->x = player->where.x + d.x;
	p1->y = player->where.y + d.y;
}

int		calc_newsector(t_xy d, t_doom *doom, t_player *player)
{
	int			n;
	t_xy		p;
	t_xy		p1;
	t_sectors	*sect;
	t_xy		*v;

	px_p1x(&p, &p1, d, player);
	sect = &doom->sectors[player->sector];
	v = sect->vert;
	n = -1;
	while (++n < sect->npoints)
	{
		if (sect->neighbors[n] >= 0 &&
		IntersectBox(p.x, p.y, p1.x, p1.y, v[n].x,
						v[n].y, v[n + 1].x, v[n + 1].y) &&
		PointSide(p1.x, p1.y, v[n].x, v[n].y, v[n + 1].x, v[n + 1].y) < 0)
		{
			player->sector = sect->neighbors[n];
			if (player->where.z != doom->sectors[player->sector].floor)
				doom->player.fall = 1;
			break ;
		}
	}
	player_move(doom, d);
	return (0);
}

int		glide_on_wall(t_xy *d, t_doom *doom, t_sectors *sect, int n)
{
	float		hole_low;
	float		hole_high;
	float		tmp;
	t_xy		a;

	tmp = doom->player.sit ? DUCKHEIGHT : EYEHEIGHT;
	doom->player.velocity.x = 0;
	doom->player.velocity.y = 0;
	hole_low = sect->neighbors[n] < 0 ? 9e9 :
	MAX(sect->floor, doom->sectors[sect->neighbors[n]].floor);
	hole_high = sect->neighbors[n] < 0 ? -9e9 :
	MIN(sect->ceil, doom->sectors[sect->neighbors[n]].ceil);
	if (hole_high < doom->player.where.z + HEADMARGIN
	|| hole_low > doom->player.where.z - tmp + KNEEHEIGHT)
	{
		d->x = d->x - doom->player.where.x;
		d->y = d->y - doom->player.where.y;
		a.x = sect->vert[n + 1].x - sect->vert[n].x;
		a.y = sect->vert[n + 1].y - sect->vert[n].y;
		d->x = a.x * (d->x * a.x + a.y * d->y) / (pow(a.x, 2) + pow(a.y, 2));
		d->y = a.y * (d->x * a.x + a.y * d->y) / (pow(a.x, 2) + pow(a.y, 2));
		return (1);
	}
	return (0);
}

int		is_wall(t_doom *doom, t_sectors *sect, t_xy *d, int n)
{
	t_xy		p;
	t_xy		p1;
	t_xy		*v;

	v = sect->vert;
	p.x = doom->player.where.x;
	p.y = doom->player.where.y;
	p1.x = doom->player.where.x + d->x;
	p1.y = doom->player.where.y + d->y;
	if ((IntersectBox(p.x, p.y, p1.x, p1.y,
	v[n].x, v[n].y, v[n + 1].x, v[n + 1].y) &&
	PointSide(p1.x, p1.y, v[n].x, v[n].y, v[n + 1].x, v[n + 1].y) < 0))
		if (glide_on_wall(d, doom, sect, n))
			return (1);
	return (0);
}

int		calc_is_wall(t_doom *doom, t_player *player)
{
	t_sectors	*sect;
	t_xy		d;
	int			n;

	d.x = player->velocity.x;
	d.y = player->velocity.y;
	sect = &doom->sectors[player->sector];
	n = 0;
	while (n < sect->npoints)
	{
		if ((is_wall(doom, sect, &d, n)))
			break ;
		n++;
	}
	calc_newsector(d, doom, player);
	return (0);
}
