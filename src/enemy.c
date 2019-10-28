/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 17:31:17 by njacobso          #+#    #+#             */
/*   Updated: 2019/10/28 20:21:58 by glormell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
** if player is within enemy's range and in same sector,	return 1
** otherwise												return 0
*/

int		detect_player(t_doom *doom, t_enemy *enemy)
{
	t_xy player_pos;

	player_pos = (t_xy){doom->player.where.x, doom->player.where.y};
	if (enemy->obj->sector == doom->player.sector &&
		distance(player_pos, enemy->obj->p) <= enemy->view_distance)
		return (1);
	return (0);
}

/*
** if new_pos is not in the wall		return 1
** otherwise							return 0
*/

int		can_move(t_doom *doom, t_enemy *enemy, t_xy new_pos)
{
	t_sectors	*s;
	t_xy		*v;
	int			n;

	s = &doom->sectors[enemy->obj->sector];
	v = s->vert;
	n = 0;
	new_pos = v2_add(new_pos, v2_multf(enemy->dir, enemy->obj->col_size));
	while (n < s->npoints)
	{
		if (collision_box_dir(enemy->obj->p, new_pos, v[n], v[n + 1]))
			return (0);
		n++;
	}
	return (1);
}

float	random_range(float min, float max)
{
	return (min + (max - min) * ((double)rand() / RAND_MAX * 2.0 - 1.0));
}

t_enemy	*get_enemy_by_obj_id(t_doom *doom, int id)
{
	int		i;
	t_enemy	*enemy;

	i = 0;
	while (i < doom->num.enemies)
	{
		enemy = &doom->enemies[i];
		if (enemy->obj->n == id)
			return (enemy);
		i++;
	}
	return (NULL);
}

t_enemy	*create_enemy_default(t_doom *doom, t_obj *obj)
{
	t_enemy	*enemy;
	t_xy	new_dir;

	enemy = &doom->enemies[doom->num.enemies];
	enemy->obj = obj;
	enemy->obj->enabled = 1;
	new_dir = v2_normalize((t_xy){random_range(-1, 1), random_range(-1, 1)});
	enemy->dir = new_dir;
	enemy->state = 0;
	enemy->health = 10;
	enemy->attack_speed = 3.0f;
	enemy->attack_damage = (int)random_range(4, 7);
	enemy->move_speed = 8;
	enemy->view_distance = 25.0f;
	enemy->on_framestart = enemy_on_framestart;
	enemy->on_attack = enemy_on_attack;
	enemy->obj->on_hit = enemy_obj_on_hit;
	enemy->on_hit = enemy_on_hit;
	doom->num.enemies++;
	return (enemy);
}
