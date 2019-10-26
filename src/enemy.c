/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 17:31:17 by njacobso          #+#    #+#             */
/*   Updated: 2019/10/26 11:03:38 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
**	N NE E SE S SW W WN
*/

int		rotate_enemy(t_doom *doom, t_enemy *enemy)
{
	float	player_deg;
	float	enemy_deg;
	float	angle;
	int		state;

	player_deg = v2_to_rot(v2_subtract((t_xy){doom->player.where.x,
					doom->player.where.y}, enemy->obj->p));
	player_deg = rad_to_deg(player_deg);
	enemy_deg = enemy->rot;
	enemy_deg = rad_to_deg(enemy_deg);
	angle = enemy_deg - player_deg + 22.5f;
	if (angle < 0)
		angle += 360;
	state = (int)(angle / 45);
	return (state);
}

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

void	enemy_on_attack(t_doom *doom, t_enemy *enemy)
{
	enemy->attack_cd = enemy->attack_speed;
	player_take_damage(doom, enemy->attack_damage);
	play_sound(doom, SOUND_E_ATTACK);
}

void	enemy_on_hit(t_doom *doom, t_enemy *enemy)
{
	if (enemy->health <= 0)
		return ;
	obj_state_change(enemy->obj, ENEMY_STATE_HIT);
	enemy->health -= doom->weapon[doom->player.weapon].damage /
		sqrt(pow(enemy->obj->p.x - doom->player.where.x, 2) + pow(enemy->obj->p.y - doom->player.where.y, 2));
	if (enemy->health <= 0)
	{
		obj_state_change(enemy->obj, ENEMY_STATE_DEAD);
		play_sound(doom, SOUND_DEATH);
	}
}

float	random_range(float min, float max)
{
	return (min + (max - min) * ((double)rand() / RAND_MAX * 2.0 - 1.0));
}

void	enemy_on_framestart(t_doom *doom, t_enemy *enemy)
{
	t_xy	move_pos;
	t_xy	new_dir;

	if (enemy->health <= 0 || enemy->obj->enabled == 0)
		return ;
	if (enemy->state == 0)
	{
		move_pos = v2_add(enemy->obj->p, v2_multf(enemy->dir, (enemy->move_speed * doom->fps.time_frame)));
		if (can_move(doom, enemy, move_pos))
		{
			enemy->obj->p = move_pos;
		}
		else
		{
			new_dir = v2_normalize((t_xy){random_range(-1, 1), random_range(-1, 1)});
			enemy->dir = new_dir;
		}
		if (detect_player(doom, enemy))
			enemy->state = 1;
		if (enemy->obj->states_frame != ENEMY_STATE_HIT || doom->a == 1)
			obj_state_change(enemy->obj, rotate_enemy(doom, enemy));
	}
	else if (enemy->state == 1)
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
	enemy->rot = v2_to_rot(enemy->dir);
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

void	enemy_obj_on_hit(t_doom *doom, t_obj *obj)
{
	t_enemy *enemy;

	printf("Enemy obj on hit\n");
	enemy = get_enemy_by_obj_id(doom, obj->n);
	enemy->on_hit(doom, enemy);
}

t_enemy	*create_enemy_default(t_doom *doom, t_obj *obj)
{
	t_enemy	*enemy;
	t_xy	new_dir;

	enemy = (t_enemy*)malloc(sizeof(t_enemy));
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
	doom->enemies[doom->num.enemies] = *enemy;
	doom->num.enemies++;
	return (enemy);
}

void	enemies_update(t_doom *doom)
{
	int		i;
	t_enemy *enemy;

	i = 0;
	while (i < doom->num.enemies)
	{
		enemy = &doom->enemies[i];
		if (enemy->obj->enabled && enemy->health > 0)
			enemy->on_framestart(doom, enemy);
		i++;
	}
}
