#include "doom.h"

//math functions
t_xy	rot_to_v2(float rot)
{
	t_xy	v2;

	v2.x = cos(rot);
	v2.y = sin(rot);
	return (v2);
}

float	v2_to_rot(t_xy v2)
{
	return(atan2(v2.y, v2.x));
}

t_xy	v2_add(t_xy v1, t_xy v2)
{
	t_xy tmp;

	tmp.x = v1.x + v2.x;
	tmp.y = v1.y + v2.y;
	return (tmp);
}

t_xy	v2_addf(t_xy v2, float f)
{
	t_xy tmp;

	tmp.x = v2.x + f;
	tmp.y = v2.y + f;
	return (tmp);
}

t_xy	v2_subtract(t_xy v1, t_xy v2)
{
	t_xy tmp;

	tmp.x = v1.x - v2.x;
	tmp.y = v1.y - v2.y;
	return (tmp);
}

t_xy	v2_multf(t_xy v2, float f)
{
	t_xy tmp;

	tmp.x = v2.x * f;
	tmp.y = v2.y * f;
	return (tmp);
}

float	distance(t_xy p1, t_xy p2)
{
	t_xy	tmp;
	float	distance;

	tmp.x = p2.x - p1.x;
	tmp.y = p2.y - p1.y;
	distance = sqrt((tmp.x * tmp.x) + (tmp.y * tmp.y));
	return (distance);
}

float	rad_to_deg(float rad)
{
	return (rad * (180 / M_PI));
}
//Math functions

int		rotate_enemy(t_doom *doom, t_enemy *enemy)
{
	float player_deg;
	float enemy_deg;
	float angle;

	player_deg = doom->player.angle;
	if (player_deg < 0)
		player_deg = -player_deg;
	while (player_deg > 6)
		player_deg -= 6;
	player_deg = rad_to_deg(player_deg);
	enemy_deg = enemy->rot;
	if (enemy_deg < 0)
		enemy_deg = -enemy_deg;
	enemy_deg = rad_to_deg(enemy_deg);
	angle = enemy_deg - player_deg + 22.5f;
	if (angle < 0)
		angle += 360;
	printf("pl %f, en %f, angle %f\n", player_deg, enemy_deg, angle);
	printf("state %d\n", (int)(angle / 45));
	return ((int)(angle / 45));
}

int		detect_player(t_doom *doom, t_enemy *enemy)
{
	t_xy player_pos;

	return (0);
	player_pos = (t_xy){0, 0};
	if (distance(player_pos, enemy->obj->p) > enemy->view_distance)
		return (0);
	//if player is within enemy's range and is seen		return 1
	//otherwise											return 0
	return (1);
}

int		can_move(t_doom *doom, t_xy new_pos)
{
	//if new_pos is not in the wall		return 1
	//otherwise							return 0
	return (1);
}

void	enemy_on_attack(t_doom *doom, t_enemy *enemy)
{
	enemy->attack_cd = enemy->attack_speed;
	//launch projectile towards enemy rotation
}

void	enemy_on_hit(t_doom *doom, t_enemy *enemy)
{
	enemy->health -= 1;
	//change texture to enemy_hit, spawn particles, etc
	if (enemy->health <= 0)
		enemy->txt_index = 1; //change to enemy_dead texture
}

void	enemy_on_framestart(t_doom *doom, t_enemy *enemy)
{
	t_xy	move_pos;

	if (enemy->health <= 0)
		return ;
	if (enemy->state == 0)
	{
		move_pos = v2_add(enemy->obj->p, v2_multf(v2_multf(enemy->dir, enemy->move_speed), doom->time_frame));
		if (can_move(doom, move_pos))
		{
			//enemy->obj->p = move_pos;
		}
		else
		{
			//change dir, idk
			enemy->dir.x *= -1;
			enemy->dir.y *= -1;
		}
		if (detect_player(doom, enemy))
			enemy->state = 1;
		enemy->obj->state_change(enemy->obj, rotate_enemy(doom, enemy));
	}
	else if (enemy->state == 1)
	{
		//rotate towards player
		enemy->obj->state_change(enemy->obj, 0);
		if (enemy->attack_cd > 0)
			enemy->attack_cd -= doom->time_frame;
		else
			enemy->on_attack(doom, enemy);
	}
	enemy->rot = v2_to_rot(enemy->dir);
}

t_enemy	*create_enemy(t_doom *doom, t_obj *obj)
{
	t_enemy *enemy;

	enemy = (t_enemy*)malloc(sizeof(t_enemy));
	enemy->obj = obj;
	enemy->obj->p = (t_xy){0, 0};
	//dir is normalized vector and shouldn't be 0
	enemy->dir = (t_xy){1, 1};
	enemy->state = 0;
	enemy->health = 3;
	enemy->txt_index = 0;
	enemy->attack_speed = 3.0f;
	enemy->attack_damage = 5;
	enemy->move_speed = 2;
	enemy->on_framestart = enemy_on_framestart;
	enemy->on_attack = enemy_on_attack;
	enemy->on_hit = enemy_on_hit;
	return (enemy);
}

void	enemies_update(t_doom *doom)
{
	doom->enemy->on_framestart(doom, doom->enemy);
	//foreach enemy in enemies_array
	//	enemy.on_framestart();
}