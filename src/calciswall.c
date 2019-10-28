/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calciswall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 19:23:01 by dtoy              #+#    #+#             */
/*   Updated: 2019/10/28 19:28:23 by glormell         ###   ########.fr       */
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
	t_xy		delta;

	px_p1x(&p, &p1, d, player);
	sect = &doom->sectors[player->sector];
	n = 0;
	while (n < sect->npoints)
	{
		if (sect->neighbors[n] >= 0 &&
		intersect_box(p, p1, sect->vert[n], sect->vert[n + 1]) &&
		point_side(p1, sect->vert[n], sect->vert[n + 1]) < 0)
		{
			player->sector = sect->neighbors[n];
			if (player->where.z != doom->sectors[player->sector].floor)
				doom->player.fall = 1;
			break ;
		}
		n++;
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

	tmp = doom->player.sit ? DuckHeight : EyeHeight;
	doom->player.velocity.x = 0;
	doom->player.velocity.y = 0;
	hole_low = sect->neighbors[n] < 0 ? 9e9 :
	max(sect->floor, doom->sectors[sect->neighbors[n]].floor);
	hole_high = sect->neighbors[n] < 0 ? -9e9 :
	min(sect->ceil, doom->sectors[sect->neighbors[n]].ceil);
	if (hole_high < doom->player.where.z + HeadMargin
	|| hole_low > doom->player.where.z - tmp + KneeHeight)
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
	if ((intersect_box(p, p1, v[n], v[n + 1]) &&
	point_side(p1, v[n], v[n + 1]) < 0))
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
