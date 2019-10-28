/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawceilandfloor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 20:20:00 by dtoy              #+#    #+#             */
/*   Updated: 2019/10/27 20:46:45 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int			render_ceil_floor(t_doom *doom, t_sectors *s, t_cood *cood, t_player player)
{
	float 	mapx;
	float	mapz;
	int 	txtx;
	int 	txtz;
	int		pel;
	static int	prev_light;
	static int	prev_color;
	float	hei;
	t_img	set;

	hei = cood->y < cood->cy.a ? cood->yceil : cood->yfloor;
	if (s->sky == 1 && hei == cood->yceil)
	{
		doom->visible[cood->y][cood->x] = 1;
		return (0);
	}
	to_map_coordinates(hei, cood->x, cood->y, &mapx, &mapz, player);
    txtx = (mapx * 8);
	txtz = (mapz * 8);
	set = cood->y < cood->cy.a - 1 ? doom->img[doom->ceils[s->txtc].image] : doom->img[doom->floors[s->txtf].image];
	pel = set.data[(txtz % set.h) * set.w + (txtx % set.w)];
	if (pel != prev_color)
	{
		prev_light = rgb_multiply(pel, s->light);
		prev_color = pel;
	}
	doom->sdl->pix[cood->y * WIDTH + cood->x] = pel;
	if (!set.data[(txtz % set.h) * set.w + (txtx % set.w)])
	{
		doom->visible[cood->y][cood->x] = 1;
		return (0);
	}
	return (1);
}

int			draw_ceil_floor(t_doom *doom, t_sectors *s, t_cood *cood, t_player player)
{
	int		y;

	y = doom->ytop[cood->x];
	while (y <= doom->ybot[cood->x])
	{
		if (y >= cood->cy.a - 1 && y <= cood->cy.b - 1)
		{
			y = cood->cy.b - 1;
			y++;
			continue ;
		}
		cood->y = y;
		if (!(render_ceil_floor(doom, s, cood, player)))
		{
			y++;
			continue ;
		}
		y++;
	}
	return (0);
}
