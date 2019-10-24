/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawhud.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 17:27:54 by glormell          #+#    #+#             */
/*   Updated: 2019/10/24 18:45:24 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void		drawhudel(t_hudel e, int *pix)
{
	int			i;
	int			j;
	int			n;
	int			m;

	i = -1;
	while (++i < e.h)
	{
		j = -2;
		while (++j < e.w)
		{
			n = (e.y + i) * WIDTH + e.x + j;
			m = i * e.s->pitch + j * e.s->format->BytesPerPixel;
			if (e.p[m] != 0 && j >= 0)
				pix[n] = e.c;
			else if ((j < 0 && e.p[m + 1] != 0) || (j >= 0 && (e.p[m + 1] != 0
					|| e.p[m - 1] != 0) && j + 1 < e.w && j - 1 >= 0) ||
					((e.p[m + e.w] != 0 || e.p[m - e.w] != 0) &&
					(i + 1 < e.h && i - 1 >= 0)))
				pix[n] = e.b;
		}
	}
}

void			drawhud(t_doom *doom)
{
	//doom->hud->ammo.t = ft_itoa(doom->weapon[doom->player.weapon].ammo);
	//printf("ammo - %s\n", doom->hud->ammo.t);
	
	//doom->hud->health.t = ft_itoa(doom->player.hp);
	load_hud(doom);
	drawhudel(doom->hud->health, doom->sdl->pix);
	drawhudel(doom->hud->ammo, doom->sdl->pix);
}
