/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcsector.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 20:15:57 by dtoy              #+#    #+#             */
/*   Updated: 2019/10/29 11:15:20 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		find_t_points(t_xy *v, t_player player, t_cood *cood)
{
	cood->v1.x = v[cood->n].x - player.where.x;
	cood->v1.y = v[cood->n].y - player.where.y;
	cood->v2.x = v[cood->n + 1].x - player.where.x;
	cood->v2.y = v[cood->n + 1].y - player.where.y;
	cood->t1.x = cood->v1.x * player.psin - cood->v1.y * player.pcos;
	cood->t1.z = cood->v1.x * player.pcos + cood->v1.y * player.psin;
	cood->t2.x = cood->v2.x * player.psin - cood->v2.y * player.pcos;
	cood->t2.z = cood->v2.x * player.pcos + cood->v2.y * player.psin;
}

int			calc_points(t_doom *doom, t_sectors *s,
t_cood *cood, t_player player)
{
	find_t_points(s->vert, player, cood);
	if (cood->t1.z <= 0 && cood->t2.z <= 0)
		return (0);
	cood->u0 = 0;
	cood->u1 = 128;//; / ((s->ceil - s->floor) / 142) * 3;
	if (cood->t1.z <= 0 || cood->t2.z <= 0)
		intersect(&cood->t1, &cood->t2, cood);
	if (!(find_scales(cood)))
		return (0);
	calc_pics(doom, doom->pics);
	find_yceil_yfloor(doom, s, cood, player);
	render_walls(doom, s, cood, player);
	return (1);
}

int			calc_sector(t_doom *doom, t_sectors *s,
t_cood *cood, t_player player)
{
	int		n;

	n = 0;
	while (n < s->npoints)
	{
		printf("n - %d\n", n);
		cood->n = n;
		if (!(calc_points(doom, s, cood, player)))
		{
			n++;
			continue ;
		}
		n++;
		doom->item[doom->now.sector].ytop = doom->ytop;
		doom->item[doom->now.sector].ybot = doom->ybot;
		if (cood->neighbor >= 0 && cood->endx >= cood->beginx
		&& (doom->head + 32 + 1 - doom->tail) % 32)
		{
			doom->head->sector = cood->neighbor;
			doom->head->sx = cood->beginx;
			doom->head->ex = cood->endx;
			if (++doom->head == doom->queue + 32)
				doom->head = doom->queue;
		}
	}
	return (0);
}
