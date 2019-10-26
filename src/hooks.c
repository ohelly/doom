/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 18:28:42 by dtoy              #+#    #+#             */
/*   Updated: 2019/10/26 10:14:59 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		find_door(t_doom *doom, t_player player)
{
	t_sectors	*s;
	t_xy		*v;
	int			n;
	t_xy		p = (t_xy){player.where.x, player.where.y};
	t_xy		d = (t_xy){player.pcos * 8, player.psin * 8};

	s = &doom->sectors[player.sector];
	if (s->type == 2 && !player.key)
		return (0);
	v = s->vert;
	n = 0;
	while (n < s->npoints)
	{
		if (s->neighbors[n] >= 0 && collision_box_dir(p, v2_add(p, d), v[n], v[n + 1]))
		{
			doom->sectors[s->neighbors[n]].active = 1;
			return (1);
		}
		n++;
	}
	return (0);
}

void	change_light(t_player player, t_sectors *s, t_pics *pic)
{	
	static int t = 0;

	if (sqrt(pow(player.where.x - pic->p.x, 2) + pow(player.where.y - pic->p.y, 2)) > 15)
		return ;
	if (t == 0)
	{
		s->light = 15 / 100.f;
		pic->states_frame = 1;
		t = 1;
	}
	else
	{
		s->light = 80 / 100.f;
		pic->states_frame = 0;
		t = 0;
	}
}

int		find_pic_interaction(t_doom *doom)
{
	int		i;
	
	i = 0;
	while (i < doom->num.pics)
	{
		if (doom->pic_interaction[i] == 1)
		{
			if (doom->pics[i].type == PIC_TYPE_SWITCH)
			{
				change_light(doom->player, &doom->sectors[doom->player.sector], &doom->pics[i]);
				return (1);
			}
			if (doom->pics[i].type == PIC_TYPE_DECOR)
			{
				doom->pics[i].states_frame = 1;
				doom->pics[i].anim_frame = 0;
			}
		}
		i++;
	}
	return (0);
}

void	change_weapon(t_player *player, t_weapon *weapon, int n)
{
	player->weapon = n;
	weapon[player->weapon].anim_frame = 0;
	weapon[player->weapon].states_frame = 0;
}

void	change_all_weapons(t_weapon *weapon, SDL_Event ev, t_player *player, int	*allweapons)
{
	if (ev.key.keysym.sym == '1' && allweapons[WEAPON_FOOT])
		change_weapon(player, weapon, WEAPON_FOOT);
	if (ev.key.keysym.sym == '2' && allweapons[WEAPON_PISTOL])
		change_weapon(player, weapon, WEAPON_PISTOL);
	if (ev.key.keysym.sym == '3' && allweapons[WEAPON_SHOTGUN])
		change_weapon(player, weapon, WEAPON_SHOTGUN);
	if (ev.key.keysym.sym == '4' && allweapons[WEAPON_RIPPER])
		change_weapon(player, weapon, WEAPON_RIPPER);
}

void	reload_pistol(SDL_Event ev, t_weapon weapon, t_player *player)
{
	if (ev.key.keysym.sym == 'r' && player->weapon == WEAPON_PISTOL && weapon.ammo > 10 && player->shoots != 0)
	{
		player->reload = 1;
		player->shoots = 0;
	}
}

void	player_move_keydown(SDL_Event ev, int *wsad)
{
	if (ev.key.keysym.sym == 'w')
		wsad[0] = 1;
	if (ev.key.keysym.sym == 's')
		wsad[1] = 1;
	if (ev.key.keysym.sym == 'a')
		wsad[2] = 1;
	if (ev.key.keysym.sym == 'd')
		wsad[3] = 1;
}

void	jump_sprint_crouch(SDL_Event ev, t_player *player, t_sectors *s)
{
	if (ev.key.keysym.sym == SDLK_SPACE)
	{
		if (player->ground)
		{
			player->velocity.z = 2.f;
			player->fall = 1;
		}
	}
	if (ev.key.keysym.sym == SDLK_LCTRL)
	{
		player->sit = 1;
		player->where.z = s[player->sector].floor + DuckHeight;
	}
	if (ev.key.keysym.sym == SDLK_LSHIFT)
		player->sprint = 1;
}

void	close_program(SDL_Event ev, t_doom *doom)
{
	if (ev.key.keysym.sym == '\033')
	{
		sound_free_everything(doom);
		Mix_Quit();
		SDL_Quit();
		exit(0);
	}
}

int		keydown(t_doom *doom, SDL_Event ev)
{
	close_program(ev, doom);
	change_all_weapons(doom->weapon, ev, &doom->player, doom->player.allweapons);
	reload_pistol(ev, doom->weapon[WEAPON_PISTOL], &doom->player);
	player_move_keydown(ev, doom->wsad);
	if (ev.key.keysym.sym == 'e')
		if (find_door(doom, doom->player) || find_pic_interaction(doom) || find_obj_interaction(doom))
			play_sound(doom, SOUND_INTERACT);
	jump_sprint_crouch(ev, &doom->player, doom->sectors);
	if (ev.key.keysym.sym == 'p')
		profile_output(doom);

	return (0);
}

void	player_move_keyup(SDL_Event ev, int *wsad)
{
	if (ev.key.keysym.sym == 'w')
		wsad[0] = 0;
	if (ev.key.keysym.sym == 's')
		wsad[1] = 0;
	if (ev.key.keysym.sym == 'a')
		wsad[2] = 0;
	if (ev.key.keysym.sym == 'd')
		wsad[3] = 0;
}

int		keyup(t_doom *doom, SDL_Event ev)
{
	player_move_keyup(ev, doom->wsad);
	if (ev.button.button == SDL_BUTTON_LEFT)
		doom->lkey = 0;
	if (ev.button.button == SDL_BUTTON_RIGHT)
		doom->rkey = 0;
	if (ev.key.keysym.sym == SDLK_LCTRL)
	{
		doom->player.sit = 0;
		doom->player.where.z = doom->sectors[doom->player.sector].floor + EyeHeight;
	}
	if (ev.key.keysym.sym == SDLK_LSHIFT)
		doom->player.sprint = 0;
	return (0);
}

t_xyz 	find_wall_intersection(t_xy t, t_xy w1, t_xy w2, t_xyz p)
{
	t_xyz	i;
	t_xy	s1;
	t_xy	s2;
	float	s;
	float	f;

    s1.x = w2.x - w1.x;
	s1.y = w2.y - w1.y;
    s2.x = t.x - p.x;
	s2.y = t.y - p.y;
    s = (-s1.y * (w1.x - p.x) + s1.x * (w1.y - p.y)) / (-s2.x * s1.y + s1.x * s2.y);
    f = ( s2.x * (w1.y -p.y) - s2.y * (w1.x - p.x)) / (-s2.x * s1.y + s1.x * s2.y);
    if (s >= 0 && s <= 1 && f >= 0 && f <= 1)
    {
        i.x = w1.x + (f * s1.x);
        i.y = w1.y + (f * s1.y);
        return (i);
    }
	i.x = -1;
	i.y = -1;
	return (i);
}

t_xy	find_t(t_player player, t_xyz p)
{
	t_xy	t;

	t.x = p.x + 10000 * player.pcos;
	t.y = p.y + 10000 * player.psin;
	return (t);
}

int		shoot_wall(t_doom *doom, t_player player, t_sectors *sect, t_pics *pic)
{
	int		sector;
	t_sectors	*s;
	t_xyz	p;
	t_xyz	i;

 	if (doom->num_shots == SHOTS_NUM)
	 	doom->num_shots = 0;
	sector = player.sector;
	p = player.where;
	s = &sect[sector];
	if (doom->lookwall[sector] == -1)
		return (0);
	i = find_wall_intersection(find_t(player, p), s->vert[doom->lookwall[sector]], s->vert[doom->lookwall[sector] + 1], p);
	if (!i.x && !i.y)
		return (0);
	doom->shot_pics.p = i;	
	doom->shot_pics.p.z = player.where.z + tanf(atanf(-player.yaw)) * (sqrtf(powf(i.x - doom->player.where.x, 2) + powf(i.y - doom->player.where.y, 2)));
	doom->shot_pics.wall = doom->lookwall[sector];
	doom->shot_pics.sector = sector;
	if (s->neighbors[doom->lookwall[sector]] < 0)
	{
		if (doom->shot_pics.p.z > s->ceil || doom->shot_pics.p.z < s->floor)
			return (0);
		findpicpoints(doom, &doom->shot_pics, (float)(doom->img[doom->shot_pics.images[0][0]].w) / 256.f);
	}
	else
	{
		return (0);
	}
	pic[doom->num.pics + doom->num_shots] = doom->shot_pics;
	doom->num_shots++;
	
	return (0);
}

/*
int		shoot_wall(t_doom *doom, t_player player, t_sectors *sectors)
{
	static int n = 0;
	int 	x;
	int		sector;
	float	pz;
	float	y;
	t_xy	t;
	t_xy	w1;
	t_xy	w2;
	t_xyz	p;
	t_xyz	d;
	t_sectors	*s;

	if (n >= 32)
		n = n % 32;
	sector = player.sector;
	pz = player.where.z;
	s = &sectors[sector];
	d = player.where;
	while (1)
	{
		if (doom->lookwall[sector] == -1)
			return (0);
		t.x = d.x + 10000 * player.pcos;
		t.y = d.y + 10000 * player.psin;	
		w1 = s->vert[doom->lookwall[sector]];
		w2 = s->vert[doom->lookwall[sector] + 1];
		p = find_wall_intersection(t, d, w1, w2);
		doom->shot_pics[n].p = p;
		doom->shot_pics[n].wall = doom->lookwall[sector];
		doom->shot_pics[n].p.z = pz + tanf(atanf(-player.yaw)) * (sqrtf(powf(p.x - doom->player.where.x, 2) + powf(p.y - doom->player.where.y, 2)));
		doom->shot_pics[n].sector = sector;
		doom->shot_pics[n].wall = doom->lookwall[sector];
		if (s->neighbors[doom->lookwall[sector]] < 0)
		{
			if (doom->shot_pics[n].p.z > s->ceil || doom->shot_pics[n].p.z < s->floor)
				return (0);
			findpicpoints(doom, &doom->shot_pics[n], (float)(doom->img[doom->shot_pics[n].images[0][0]].w) / 64);
			doom->shot_pics[n].neighbor = -1;
			break ;
		}
		else
		{
			doom->shot_pics[n].neighbor = s->neighbors[doom->lookwall[sector]];
			doom->shot_pics[n].sector = sector;
			if ((doom->shot_pics[n].p.z > sectors[s->neighbors[doom->lookwall[sector]]].ceil && doom->shot_pics[n].p.z < s->ceil)
			|| (doom->shot_pics[n].p.z < sectors[s->neighbors[doom->lookwall[sector]]].floor && doom->shot_pics[n].p.z > s->floor))
			{
				findpicpoints(doom, &doom->shot_pics[n], (float)(doom->img[doom->shot_pics[n].images[0][0]].w) / 64);
				break ;
			}
			sector = s->neighbors[doom->lookwall[sector]];
			s = &sectors[sector];
			d = p;
			d.x = d.x + 0.0001 * player.pcos;
			d.y = d.y + 0.0001 * player.psin;
			p.z = doom->shot_pics[n].p.z;
			continue ;
		}
		
	}
	doom->num_shots = n + 1;
	n++;
	return (0);
}
*/
int		find_on_hit_obj(t_doom *doom)
{
	int		j;
	int		t;

	t = 0;
	j = 0;
	while (j < doom->num.objs)
	{
		if (doom->obj_ind[j] == 1 && doom->objs[j].on_hit != NULL)
		{
			t++;
			doom->objs[j].on_hit(doom, &doom->objs[j]);
		}
		j++;
	}
	return (t);
}

int		shoot(t_doom *doom)
{
	int		i;
	int		j;

	play_sound(doom, SOUND_SHOOT);
	i = -1;
	while (++i < 32)
	{
		if (doom->obj_ind[i] == 1)
			if (find_on_hit_obj(doom) >= 3)
				break ;
	}
	if (doom->player.weapon)
		shoot_wall(doom, doom->player, doom->sectors, doom->pics);
	find_pic_interaction(doom);
	return (0);
}

void	left_mouse_keydown(t_doom *doom, SDL_Event ev, t_weapon *weapon, t_player *player)
{
	if (ev.button.button == SDL_BUTTON_LEFT && !player->reload && weapon->ammo && !weapon->states_frame)
	{
		doom->lkey = 1;
		if (player->weapon)
			weapon->ammo--;
		if (weapon->anim_frame == 0)
			weapon->states_frame = 1;
		if (player->weapon == WEAPON_PISTOL)	//перезарядка после 10 выстрелов у пистолета
		{
			player->shoots++;
			if (player->shoots == 10)
			{
				player->shoots = 0;
				player->reload = 1;
			}
		}
		shoot(doom);
	}
}

int		hooks(t_doom *doom, SDL_Event ev)
{	
	if (ev.type == SDL_MOUSEBUTTONDOWN)
	{
		left_mouse_keydown(doom, ev, &doom->weapon[doom->player.weapon], &doom->player);
		if (ev.button.button == SDL_BUTTON_RIGHT)
			doom->rkey = 1;
	}
	if (ev.type == SDL_MOUSEBUTTONUP)
	{
		if (ev.button.button == SDL_BUTTON_LEFT)
			doom->lkey = 0;
		if (ev.button.button == SDL_BUTTON_RIGHT)
			doom->rkey = 0;
	}
	if (ev.type == SDL_KEYDOWN)
		keydown(doom, ev);
	if (ev.type == SDL_KEYUP)
		keyup(doom, ev);
	return (0);
}
