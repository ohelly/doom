typedef struct	s_v2
{
	float x;
	float y;
}				t_v2;

typedef struct	s_enemy
{
	t_v2	pos;
	//direction vector
	t_v2	dir;
	//rotation is stored in radians
	float	rot;
	//0 - wandering, 1 - attacking
	float	view_distance;
	float	move_speed;
	int		state;
	int		health;
	int		txt_index;
	float	attack_speed;
	float	attack_cd;
	int		attack_damage;
	void	(*on_attack)(t_enemy *enemy);
	void	(*on_hit)(t_enemy *enemy);
	void	(*on_framestart)(t_enemy *enemy);
}				t_enemy;

//math functions
t_v2	rot_to_v2(float rot)
{
	t_v2	v2;

	v2.x = cos(rot);
	v2.y = sin(rot);
	return (v2);
}

float	v2_to_rot(t_v2 v2)
{
	return(atan2(v2.y, v2.x));
}

t_v2	v2_add(t_v2 v1, t_v2 v2)
{
	t_v2 tmp;

	tmp.x = v1.x + v2.x;
	tmp.y = v1.y + v2.y;
	return (tmp);
}

t_v2	v2_addf(t_v2 v2, float f)
{
	t_v2 tmp;

	tmp.x = v2.x + f;
	tmp.y = v2.y + f;
	return (tmp);
}

t_v2	v2_subtract(t_v2 v1, t_v2 v2)
{
	t_v2 tmp;

	tmp.x = v1.x - v2.x;
	tmp.y = v1.y - v2.y;
	return (tmp);
}

t_v2	v2_multf(t_v2 v2, float f)
{
	t_v2 tmp;

	tmp.x = v2.x * f;
	tmp.y = v2.y * f;
	return (tmp);
}

float	distance(t_v2 p1, t_v2 p2)
{
	t_v2	tmp;
	float	distance;

	tmp.x = p2.x - p1.x;
	tmp.y = p2.y - p1.y;
	distance = sqrt((tmp.x * tmp.x) + (tmp.y * tmp.y));
	return (distance);
}
//math functions

int		detect_player(t_enemy *enemy)
{
	t_v2 player_pos;

	player_pos = (t_v2){0, 0};
	if (distance(player_pos, enemy->pos) > enemy->view_distance)
		return (0);
	//if player is within enemy's range and is seen		return 1
	//otherwise											return 0
	return (1);
}

int		can_move(t_v2 new_pos)
{
	//if new_pos is not in the wall		return 1
	//otherwise							return 0
	return (1);
}

void	enemy_on_attack(t_enemy *enemy)
{
	enemy->attack_cd = enemy->attack_speed;
	//launch projectile towards enemy rotation
}

void	enemy_on_hit(t_enemy *enemy)
{
	enemy->health -= 1;
	//change texture to enemy_hit, spawn particles, etc
	if (enemy->health <= 0)
		enemy->txt_index = 1; //change to enemy_dead texture
}

void	enemy_on_framestart(t_enemy *enemy)
{
	t_v2	move_pos;

	if (enemy->health <= 0)
		return ;
	if (enemy->state == 0)
	{
		move_pos = v2_add(enemy->pos, v2_multf(v2_multf(enemy->dir, enemy->move_speed), frametime));
		if (can_move(move_pos))
			enemy->pos = move_pos;
		else
		{
			//change dir, idk
			enemy->dir.x *= -1;
			enemy->dir.y *= -1;
		}
		if (detect_player(enemy))
			enemy->state = 1;
	}
	else if (enemy->state == 1)
	{
		//rotate towards player
		if (enemy->attack_cd > 0)
			enemy->attack_cd -= frametime;
		else
			enemy->on_attack(enemy);
	}
	enemy->rot = v2_to_rot(enemy->dir);
	draw_sprite(enemy->pos, enemy->txt_index);
}

t_enemy	create_enemy()
{
	t_enemy enemy;

	enemy.pos = (t_v2){0, 0};
	//dir is normalized vector and shouldn't be 0
	enemy.dir = (t_v2){1, 1};
	enemy.state = 0;
	enemy.health = 3;
	enemy.txt_index = 0;
	enemy.attack_speed = 3.0f;
	enemy.attack_damage = 5;
	enemy.on_framestart = enemy_on_framestart;
	enemy.on_attack = enemy_on_attack;
	enemy.on_hit = enemy_on_hit;
	return (enemy);
}

void	enemies_update()
{
	//foreach enemy in enemies_array
	//	enemy.on_framestart();
}