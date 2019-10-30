/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calciswall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 19:23:01 by dtoy              #+#    #+#             */
/*   Updated: 2019/10/30 20:08:08 by dtoy             ###   ########.fr       */
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
		if (sect->neighbors[n] >= 0 && collision_player_dir(doom, p1, n))
		{
			player->sector = sect->neighbors[n];
			if (player->sector == player->end)
				player_win(doom);
			if (player->where.z != doom->sectors[player->sector].floor)
				doom->player.fall = 1;
			break ;
		}
	}
	return (0);
}

int		calc_is_wall(t_doom *doom, t_player *player)
{
	t_sectors	*sect;
	t_xy		d;

	d.x = player->velocity.x;
	d.y = player->velocity.y;
	sect = &doom->sectors[player->sector];
	d = player_move(doom, d);
	d = (t_xy){CLAMP(d.x, -1.0f, 1.0f), CLAMP(d.y, -1.0f, 1.0f)};
	if (d.x == 0 && d.y == 0)
		return (0);
	calc_newsector(d, doom, player);
	doom->player.where.x = doom->player.where.x + d.x;
	doom->player.where.y = doom->player.where.y + d.y;
	doom->player.psin = sinf(doom->player.angle);
	doom->player.pcos = cosf(doom->player.angle);
	return (1);
}
