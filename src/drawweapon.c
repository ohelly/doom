/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawweapon.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 18:08:49 by glormell          #+#    #+#             */
/*   Updated: 2019/10/15 19:36:03 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	weapon_state_change(t_weapon *weapon, int state)
{
	if (state >= weapon->states_count ||
		state < 0 || state == weapon->states_frame)
		return ;
	weapon->states_frame = state;
	weapon->anim_frame = 0;
}

void	weapon_anim_next(t_weapon *weapon, int state)
{
	int index;

	weapon->anim_frame++;
	if (weapon->anim_frame >= weapon->anim_count[state] ||
		weapon->images[state][weapon->anim_frame] == -1)
		weapon->anim_frame = 0;
}

t_img	weapon_get_image(t_doom *doom, t_weapon *weapon)
{
	return (doom->img[weapon->images[weapon->states_frame][weapon->anim_frame]]);
}

void		drawweapon(t_doom *doom, t_weapon *weapon)
{
	int		y;
	int		x;
	t_xy	scale;
	t_xy	t;
	t_img	img;

	if (doom->lkey)
		weapon_anim_next(weapon, 0);
	img = weapon_get_image(doom, weapon);
	x = -1;
	while (++x < WIDTH / 3)
	{
		scale.x = (float)img.w / (WIDTH / 3);
		scale.y = (float)img.h / (HEIGHT / 3);
		t.y = 0;
		t.x = x * scale.x;
		y = -1;
		while (++y < HEIGHT / 3)
		{
			if (img.data[(int)t.y * img.w + (int)t.x])
				doom->sdl->pix[y * WIDTH + x] =
					img.data[(int)t.y * img.w + (int)t.x];
			t.y += scale.y;
		}
	}
}
