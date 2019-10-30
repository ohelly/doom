/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawweapon.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 18:08:49 by glormell          #+#    #+#             */
/*   Updated: 2019/10/29 17:31:03 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int			wpn_foot(t_doom *doom, t_weapon *wpn)
{
	if (wpn->type == WEAPON_FOOT && wpn->states_frame == 0)
		return (0);
	if (wpn->type == WEAPON_FOOT || wpn->states_frame == 1)
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

int			ripper_animation(t_doom *doom, t_weapon *wpn)
{
	if (doom->lkey && wpn->type == WEAPON_RIPPER && wpn->ammo)
	{
		wpn->states_frame = 1;
		if (wpn->anim_frame % 3 == 0)
			doom->shakey = 15;
		else
			doom->shakey = 0;
	}
	if (doom->lkey && wpn->type == WEAPON_RIPPER && !wpn->ammo)
		wpn_state_change(wpn, 0);
	if (!doom->lkey && wpn->type == WEAPON_RIPPER)
		wpn_state_change(wpn, 0);
	return (0);
}

void		drawweapon(t_doom *doom, t_weapon *wpn)
{
	if (!(wpn_foot(doom, wpn)))
		return ;
	shake_timer(doom, doom->fps);
	ripper_animation(doom, wpn);
	if (doom->player.reload && wpn->type == WEAPON_PISTOL)
		wpn->states_frame = 2;
	if (wpn->states_frame != 0)
		wpn_anim_next(doom, &doom->player, wpn, doom->fps);
	render_weapon(doom, wpn);
	if (wpn->type == WEAPON_RIPPER && doom->lkey
	&& wpn->anim_frame % 4 == 0 && wpn->ammo)
	{
		shoot(doom);
		wpn->ammo--;
		if (!wpn->ammo)
			wpn_state_change(wpn, 0);
	}
}
