/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadweapondata.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 17:08:34 by dtoy              #+#    #+#             */
/*   Updated: 2019/10/27 17:27:13 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		count_params_weapon(char *map, t_weapon *wpn)
{
	float	tmp;
	int		n;
	int		a;

	map = todigit(map, &tmp);
	wpn->type = (int)tmp;
	map = todigit(map, &tmp);
	wpn->states_count = (int)tmp;
	wpn->images = (int**)ft_memalloc(sizeof(int*) * wpn->states_count);
	wpn->anim_count = (int*)ft_memalloc(sizeof(int) * wpn->states_count);
	n = 0;
	while (n < wpn->states_count)
	{
		map = todigit(map, &tmp);
		wpn->anim_count[n] = (int)tmp;
		wpn->images[n] = (int*)ft_memalloc(sizeof(int) * wpn->anim_count[n]);
		n++;
	}
	return (0);
}

void	load_weapon_params2(t_weapon *weapon, int type)
{
	if (type == WEAPON_FOOT)
	{
		weapon->ammo = 1;
		weapon->delay = 0.15f;
		weapon->damage = 40;
		weapon->scatterx = 5;
		weapon->scattery = 5;
	}
	if (type == WEAPON_PISTOL)
	{
		weapon->ammo = 70;
		weapon->delay = 0.07f;
		weapon->damage = 50;
		weapon->scatterx = 5;
		weapon->scattery = 5;
	}
}

void	load_weapon_params(t_weapon *weapon, int type)
{
	if (type == WEAPON_SHOTGUN)
	{
		weapon->ammo = 10;
		weapon->delay = 0.1f;
		weapon->damage = 80;
		weapon->scatterx = 30;
		weapon->scattery = 15;
	}
	if (type == WEAPON_RIPPER)
	{
		weapon->ammo = 60;
		weapon->delay = 0.01f;
		weapon->damage = 10;
		weapon->scatterx = 15;
		weapon->scattery = 10;
	}
}

int		load_weapon(char **map, t_weapon *weapon, t_img *img)
{
	int		n;
	int		a;
	int		i;
	int		t;

	i = 0;
	t = 1;
	n = 0;
	count_params_weapon(map[i], weapon);
	while (n < weapon->states_count)
	{
		a = 0;
		while (a < weapon->anim_count[n])
		{
			load_image(map[i + t], &weapon->images[n][a], img);
			t++;
			a++;
		}
		n++;
	}
	return (0);
}

int		load_weapon_data(char **map, t_doom *doom)
{
	int		i;
	int		t;
	int		count;
	float	tmp;

	map[0] = todigit(map[0], &tmp);
	count = (int)tmp;
	doom->num.weapons = count;
	doom->weapon = (t_weapon*)ft_memalloc(sizeof(t_weapon) * (count + 1));
	i = 1;
	while (*map[i] != '#')
	{
		load_weapon(&map[i], &doom->weapon[atoi(map[i])], doom->img);
		load_weapon_params(&doom->weapon[atoi(map[i])], atoi(map[i]));
		load_weapon_params2(&doom->weapon[atoi(map[i])], atoi(map[i]));
		while (*map[i] != '.')
		{
			if (*map[i] == '#')
				return (0);
			i++;
		}
		i++;
	}
	return (0);
}
