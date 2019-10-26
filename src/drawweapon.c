/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawweapon.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 18:08:49 by glormell          #+#    #+#             */
/*   Updated: 2019/10/26 03:40:24 by dtoy             ###   ########.fr       */
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
			if (weapon->type != WEAPON_RIPPER)
				weapon_state_change(weapon, 0);
			weapon->anim_frame = 0;
		}
		t = 0;
	}
}

t_img	weapon_get_image(t_doom *doom, t_weapon *weapon)
{
	return (doom->img[weapon->images[weapon->states_frame][weapon->anim_frame]]);
}

int			weapon_foot(t_doom *doom, t_weapon *weapon)
{
	if (weapon->type == WEAPON_FOOT && weapon->states_frame == 0)
		return (0);
	if (weapon->type == WEAPON_FOOT || weapon->states_frame == 1)
	{
		doom->shakey = 0;
		doom->shakex = 0;
	}
	return (1);
}

int			shake_timer(t_doom *doom, t_fps fps)
{
	static float time = 0;

	if (doom->push || doom->shakey || doom->shakex)
	{
		time += fps.time_frame;
		if (time >= 0.015f)
		{
			if (doom->shakey == 0)
				doom->shaketmp = 1;
			if (doom->shakey == 20)
				doom->shaketmp = -1;
			doom->shakey += doom->shaketmp;
			time = 0;
		}
	}
	return (0);
}

int			ripper_animation(t_doom *doom, t_weapon *weapon)
{
	if (doom->lkey && weapon->type == WEAPON_RIPPER && weapon->ammo)
	{
		weapon->states_frame = 1;
		if (weapon->anim_frame % 3 == 0)
			doom->shakey = 15;
		else
			doom->shakey = 0;
	}
	if (doom->lkey && weapon->type == WEAPON_RIPPER && !weapon->ammo)
		weapon_state_change(weapon, 0);
	if (!doom->lkey && weapon->type == WEAPON_RIPPER)
		weapon_state_change(weapon, 0);
	return (0);
}

void		render_weapon2(t_doom *doom, t_xy scale, t_img img, int *pix)
{
	int		y;
	int		x;
	t_xy	t;

	x = WIDTH / 4;
	while (x < WIDTH)
	{
		t.y = 1;
		t.x = (x - WIDTH) * scale.x;
		y = 0 + doom->shakey;
		while (y < HEIGHT)
		{
			if (img.data[(int)t.y * img.w + (int)t.x])
				pix[y * WIDTH + x] =
					img.data[(int)t.y * img.w + (int)t.x];
			t.y += scale.y;
			y++;
		}
		x++;
	}
}

int			render_weapon(t_doom *doom, t_weapon *weapon)
{
	t_xy	scale;
	t_img	img;

	img = weapon_get_image(doom, weapon);
	scale.x = (float)img.w / (WIDTH - WIDTH / 4);
	scale.y = (float)img.h / (HEIGHT);
	render_weapon2(doom, scale, img, doom->sdl->pix);
	return (0);
}

void		drawweapon(t_doom *doom, t_weapon *weapon)
{
	if (!(weapon_foot(doom, weapon)))
		return ;
	shake_timer(doom, doom->fps);
	if (doom->player.reload == 1 && weapon->type == WEAPON_PISTOL)
		weapon->states_frame = 2;
	ripper_animation(doom, weapon);
	if (weapon->states_frame != 0)
		weapon_anim_next(&doom->player, weapon, weapon->states_frame, doom->fps);
	render_weapon(doom, weapon);
	if (weapon->type == WEAPON_RIPPER && doom->lkey && weapon->anim_frame % 3 == 0 && weapon->ammo)
	{
		shoot(doom, weapon);
		weapon->ammo--;
		if (!weapon->ammo)
			weapon_state_change(weapon, 0);
	}
}
