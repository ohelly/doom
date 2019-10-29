/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_event_framestart.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 19:42:30 by glormell          #+#    #+#             */
/*   Updated: 2019/10/29 01:33:02 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	enemy_on_framestart_state0(t_doom *doom, t_enemy *enemy)
{
	t_xy	move_pos;
	t_xy	new_dir;

	move_pos = v2_add(enemy->obj->p,
			v2_multf(enemy->dir, (enemy->move_speed * doom->fps.time_frame)));
	if (can_move(doom, enemy, move_pos))
		enemy->obj->p = move_pos;
	else
	{
		new_dir = v2_normalize((t_xy){random_range(-1, 1),
				random_range(-1, 1)});
		enemy->dir = new_dir;
	}
	if (detect_player(doom, enemy))
		enemy->state = 1;
	if (enemy->obj->states_frame != ENEMY_STATE_HIT || doom->a == 1)
		obj_state_change(enemy->obj, rotate_enemy(doom, enemy));
}

void	enemy_on_framestart_state1(t_doom *doom, t_enemy *enemy)
{
	if (detect_player(doom, enemy) != 1)
		enemy->state = 0;
	if (enemy->attack_cd > 0)
	{
		enemy->attack_cd -= doom->fps.time_frame;
		if (doom->a == 1 && enemy->obj->anim_frame == 0)
			obj_state_change(enemy->obj, ENEMY_STATE_IDLE);
	}
	else
	{
		enemy->on_attack(doom, enemy);
		obj_state_change(enemy->obj, ENEMY_STATE_ATTACK);
	}
}

void	enemy_on_framestart(t_doom *doom, t_enemy *enemy)
{
	if (enemy->health <= 0 || enemy->obj->enabled == 0)
		return ;
	if (enemy->state == 0)
		enemy_on_framestart_state0(doom, enemy);
	else if (enemy->state == 1)
		enemy_on_framestart_state1(doom, enemy);
	enemy->rot = v2_to_rot(enemy->dir);
}
