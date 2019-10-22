/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawweapon.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 18:08:49 by glormell          #+#    #+#             */
/*   Updated: 2019/10/22 19:58:17 by dtoy             ###   ########.fr       */
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

void	weapon_anim_next(t_player *player, t_weapon *weapon, int state, t_fps fps)
{
	int index;
	static float t = 0;

	t += fps.time_frame;
	if (t >= weapon->delay)
	{
		weapon->anim_frame++;
		if (weapon->anim_frame >= weapon->anim_count[state] ||
			weapon->images[state][weapon->anim_frame] == -1)
		{
			if (weapon->states_frame == 2)
				player->reload = 0;
			if (weapon->type != 3)
				weapon->states_frame = 0;
			weapon->anim_frame = 0;
		}
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
	static float time2 = 0;
	int		tmp = 0;
	int		y;
	int		x;
	t_xy	scale;
	t_xy	t;
	t_img	img;
	
	//printf("ind - %d\n", weapon->images[weapon->states_frame][weapon->anim_frame]);
	if (weapon->type == 0 && weapon->states_frame == 0)
		return ;

	if (doom->push || doom->shakey != 0 || doom->shakex != 0)
	{
		time += doom->fps.time_frame;
		if (time >= 0.015f && weapon->type != 0)
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
	if (weapon->type == 0 || weapon->states_frame == 1)
	{
		doom->shakey = 0;
		doom->shakex = 0;
	}
	if (doom->player.reload == 1 && weapon->type != 0 && weapon->type != 2)
		weapon->states_frame = 2;
	if (doom->lkey && weapon->type == 3)
	{
		weapon->states_frame = 1;
		doom->shakex = 0;
		if (weapon->anim_frame % 3 == 0)
			doom->shakey = 15;
		else
			doom->shakey = 0;
	}
	if (!doom->lkey && weapon->type == 3)
	{
		weapon->states_frame = 0;
		weapon->anim_frame = 0;
	}
	if (weapon->states_frame != 0)
		weapon_anim_next(&doom->player, weapon, weapon->states_frame, doom->fps);
	if (weapon->type == 0)
		tmp = WIDTH / 4;
	else
		tmp = 0;
	//printf("reload - %d, state - %d\n", doom->player.reload, weapon->states_frame);
	img = weapon_get_image(doom, weapon);
	x = WIDTH / 4;// - doom->shakex;
	scale.x = (float)img.w / (WIDTH - WIDTH / 4);
	scale.y = (float)img.h / (HEIGHT);
	while (x < WIDTH)// - doom->shakex)
	{
		t.y = 0;
		t.x = (x - WIDTH) * scale.x;// + doom->shakex) * scale.x;
		y = 0 + doom->shakey;// + 25 + doom->player.yaw * 5;//2 * HEIGHT / 4 + doom->shakey;
		while (y < HEIGHT)
		{
			if (img.data[(int)t.y * img.w + (int)t.x])
				doom->sdl->pix[y * WIDTH + x] =
					img.data[(int)t.y * img.w + (int)t.x];
			t.y += scale.y;
			y++;
		}
		x++;
	}
}
