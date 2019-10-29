/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawwalls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 20:14:26 by dtoy              #+#    #+#             */
/*   Updated: 2019/10/29 12:43:46 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int			renew2(t_doom *doom, int *rensects)
{
	int		x;
	int		y;

	x = 0;
	while (x < doom->num.sectors)
	{
		doom->lookwall[x] = -1;
		doom->item[x].sector = 0;
		rensects[x] = 0;
		x++;
	}
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			doom->visible[y][x] = 0;
			x++;
		}
		y++;
	}
	return (0);
}

int			renew(t_item *head, t_doom *doom, int *rensects)
{
	int		x;
	int		i;

	x = 0;
	while (x < WIDTH)
	{
		doom->ybot[x] = HEIGHT - 1;
		doom->ytop[x] = 0;
		x++;
	}
	i = 0;
	while (i < doom->num.pics)
	{
		doom->pic_interaction[i] = 0;
		i++;
	}
	renew2(doom, rensects);
	head->sx = 0;
	head->ex = WIDTH - 1;
	head->sector = doom->player.sector;
	return (0);
}

int			assign_value(t_item *item, t_item now, int *rensects)
{
	item[now.sector].sx = now.sx;
	item[now.sector].ex = now.ex;
	item[now.sector].sector = rensects[now.sector];
	return (0);
}

int			draw_walls(t_doom *doom)
{
	int			rensects[doom->num.sectors];
	t_sectors	*s;

	doom->head = doom->queue;
	doom->tail = doom->queue;
	renew(doom->head, doom, rensects);
	if (++doom->head == doom->queue + 32)
		doom->head = doom->queue;
	while (doom->head != doom->tail)
	{
		doom->now = *doom->tail;
		if (++doom->tail == doom->queue + 32)
			doom->tail = doom->queue;
		if (rensects[doom->now.sector] & 0x21)
			continue ;
		++rensects[doom->now.sector];
		assign_value(doom->item, doom->now, rensects);
		s = &doom->sectors[doom->now.sector];
		//printf("doom->now.sector - %d\n", doom->now.sector);
		calc_sector(doom, s, &doom->cood, doom->player);
		++rensects[doom->now.sector];
	}
	return (0);
}
