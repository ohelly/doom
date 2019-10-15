/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadweapons.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glormell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 19:48:09 by glormell          #+#    #+#             */
/*   Updated: 2019/10/15 18:24:01 by glormell         ###   ########.fr       */
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
	return (doom->images[
			weapon->images[weapon->states_frame][weapon->anim_frame]]);
}

int		loadweapon(t_weapon *weapon, t_data *weapon_daata, char *str)
{
	static int	n = 0;
	float		tmp;
	int			id;
	int			i;
	int			j;

	str = todigit(str, &tmp);
	id = (int)tmp;
	str = todigit(str, &weapon[n].p.y);
	str = todigit(str, &weapon[n].p.x);
	str = todigit(str, &tmp);
	weapon[n].sector = (int)tmp;
	weapon[n].type = weapon_data[id].type;
	weapon[n].images = weapon_data[id].images;
	weapon[n].anim_count = weapon_data[id].anim_count;
	weapon[n].states_count = weapon_data[id].states_count;
	n++;
	return (0);
}
