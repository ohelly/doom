#include "doom.h"

int		rotate_enemy(t_doom *doom, t_enemy *enemy)
{
	float	player_deg;
	float	enemy_deg;
	float	angle;
	int		state;

	player_deg = v2_to_rot(v2_subtract((t_xy){doom->player.where.x, doom->player.where.y}, enemy->obj->p));
	player_deg = rad_to_deg(player_deg);
	enemy_deg = enemy->rot;
	enemy_deg = rad_to_deg(enemy_deg);
	angle = enemy_deg - player_deg + 22.5f;
	if (angle < 0)
		angle += 360;
	state = (int)(angle / 45);
	return (state);
}

//if player is within enemy's range and in same sector,	return 1
//otherwise												return 0
int		detect_player(t_doom *doom, t_enemy *enemy)
{
	t_xy player_pos;

	player_pos = (t_xy){doom->player.where.x, doom->player.where.y};
	if (enemy->obj->sector == doom->player.sector &&
		distance(player_pos, enemy->obj->p) <= enemy->view_distance)
		return (1);
	return (0);
}

//if new_pos is not in the wall		return 1
//otherwise							return 0
int		can_move(t_doom *doom, t_enemy *enemy, t_xy new_pos)
{
	t_sector	*s;
	t_xy		*v;
	int			n;

	s = &doom->sector[enemy->obj->sector];
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
	//launch projectile towards enemy rotation
}

void	enemy_on_hit(t_doom *doom, t_enemy *enemy)
{
	enemy->health -= 1;
	//change texture to enemy_hit, spawn particles, etc
	printf("Enemy took damage!\n");
	if (enemy->health <= 0)
		obj_state_change(enemy->obj, 8); //change to enemy_dead texture
}

float	ran(float min, float max)
{
	return (min + (max - min) * ((double)rand() / RAND_MAX * 2.0 - 1.0));
}

void	enemy_on_framestart(t_doom *doom, t_enemy *enemy)
{
	t_xy	move_pos;

	if (enemy->health <= 0 || enemy->obj->enabled == 0)
		return ;
	if (enemy->state == 0)
	{
		move_pos = v2_add(enemy->obj->p, v2_multf(enemy->dir, (enemy->move_speed * doom->time_frame)));
		if (can_move(doom, enemy, move_pos))
		{
			enemy->obj->p = move_pos;
		}
		else
		{
			t_xy new_dir = v2_normalize((t_xy){ran(-1, 1), ran(-1, 1)});
			enemy->dir.x = new_dir.x;
			enemy->dir.y = new_dir.y;
		}
		if (detect_player(doom, enemy))
			enemy->state = 1;
		obj_state_change(enemy->obj, rotate_enemy(doom, enemy));
	}
	else if (enemy->state == 1)
	{
		enemy->on_hit(doom, enemy);
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
	enemy->obj->enabled = 1;
	enemy->obj->col_size = 8.0f;
	enemy->obj->p = (t_xy){40, 10};
	//dir is normalized vector and shouldn't be 0
	enemy->dir = (t_xy){-1, 1};
	enemy->state = 0;
	enemy->health = 3;
	enemy->attack_speed = 3.0f;
	enemy->attack_damage = 5;
	enemy->move_speed = 8;
	enemy->view_distance = 3;
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