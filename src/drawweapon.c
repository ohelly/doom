/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawweapon.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 18:08:49 by glormell          #+#    #+#             */
/*   Updated: 2019/10/15 21:43:17 by dtoy             ###   ########.fr       */
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

void	weapon_anim_next(t_weapon *weapon, int state, t_fps fps)
{
	int index;
	static float t = 0;

	t += fps.time_frame;
	if (t >= weapon->delay)
	{
		weapon->anim_frame++;
		if (weapon->anim_frame >= weapon->anim_count[state] ||
			weapon->images[state][weapon->anim_frame] == -1)
			weapon->anim_frame = 0;
		t = 0;
	}
}

t_img	weapon_get_image(t_doom *doom, t_weapon *weapon)
{
	return (doom->img[weapon->images[weapon->states_frame][weapon->anim_frame]]);
}

void		drawweapon(t_doom *doom, t_weapon *weapon)
{
	static float time = 0;
	int		tmp = 0;
	int		y;
	int		x;
	t_xy	scale;
	t_xy	t;
	t_img	img;

	if (doom->push || doom->shakey != 0 || doom->shakex != 0)
	{
		time += doom->fps.time_frame;
		if (time >= 0.015f)
		{
			if (doom->shakey == 0)
				doom->shaketmp = 1;
			if (doom->shakey == 20)
				doom->shaketmp = -1;
			doom->shakey += doom->shaketmp;
			doom->shakex += doom->shaketmp;
			time = 0;
		}
	}
	if (doom->lkey || weapon->anim_frame != 0)
		weapon_anim_next(weapon, weapon->states_frame, doom->fps);
	img = weapon_get_image(doom, weapon);
	x = WIDTH / 3 - 1 - doom->shakex;
	while (++x < 2 * WIDTH / 3)
	{
		scale.x = (float)img.w / (WIDTH / 3);
		scale.y = (float)img.h / (HEIGHT / 3);
		t.y = 0;
		t.x = (x - WIDTH / 3 - doom->shakex) * scale.x;
		y = 2 * HEIGHT / 3 + 25 + doom->shakey + doom->player.yaw * 5;
		while (++y < HEIGHT)
		{
			if (img.data[(int)t.y * img.w + (int)t.x])
				doom->sdl->pix[y * WIDTH + x] =
					img.data[(int)t.y * img.w + (int)t.x];
			t.y += scale.y;
		}
	}
}
