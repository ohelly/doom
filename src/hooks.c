/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 18:28:42 by dtoy              #+#    #+#             */
/*   Updated: 2019/10/20 17:40:23 by dtoy             ###   ########.fr       */
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

int		find_pic_interaction(t_doom *doom)
{
	int		i;
	static int t = 0;

	i = 0;
	while (i < doom->num.pics)
	{
		if (doom->pic_interaction[i] == 1)
		{
			printf("Ok %d\n", i);
			if (doom->pics[i].type == 1)
			{
				if (sqrt(pow(doom->player.where.x - doom->pics[i].p.x, 2) + pow(doom->player.where.y - doom->pics[i].p.y, 2)) > 15)
					return (0);
				if (t == 0)
				{
					doom->sectors[doom->player.sector].light = 15 / 100.f;
					t = 1;
				}
				else
				{
					doom->sectors[doom->player.sector].light = 80 / 100.f;
					t = 0;
				}
				break ;
			}
		}
		i++;
	}
	
	return (0);
}

int		keydown(t_doom *doom, SDL_Event ev)
{
	if (ev.key.keysym.sym == '\033')
	{
		sound_free_everything(doom);
		Mix_Quit();
		SDL_Quit();
		exit(0);
	}
	if (ev.key.keysym.sym == '1')
	{
		doom->player.weapon = 0;
		doom->weapon[doom->player.weapon].anim_frame = 0;
		doom->weapon[doom->player.weapon].states_frame = 0;
		//doom->weapon_change = 1;
		//doom->change_y = 0;
	}
	if (ev.key.keysym.sym == '2')
	{
		doom->player.weapon = 1;
		doom->weapon[doom->player.weapon].anim_frame = 0;
		doom->weapon[doom->player.weapon].states_frame = 0;

	}
	if (ev.key.keysym.sym == '3')
	{
		doom->player.weapon = 2;
		doom->weapon[doom->player.weapon].anim_frame = 0;
		doom->weapon[doom->player.weapon].states_frame = 0;

	}
	if (ev.key.keysym.sym == '4')
	{
		doom->player.weapon = 3;
		doom->weapon[doom->player.weapon].anim_frame = 0;
		doom->weapon[doom->player.weapon].states_frame = 0;

	}
	if (ev.key.keysym.sym == 'r' && doom->player.weapon == 1 && doom->weapon[1].ammo > 10 && doom->player.shoots != 0)
	{
		doom->player.reload = 1;
		doom->player.shoots = 0;
	}
	if (ev.key.keysym.sym == 'w')
		doom->wsad[0] = 1;
	if (ev.key.keysym.sym == 's')
		doom->wsad[1] = 1;
	if (ev.key.keysym.sym == 'a')
		doom->wsad[2] = 1;
	if (ev.key.keysym.sym == 'd')
		doom->wsad[3] = 1;
	if (ev.key.keysym.sym == 'e')
	{
		find_door(doom, doom->player);
		find_pic_interaction(doom);
		find_obj_interaction(doom);
	}
	if (ev.key.keysym.sym == '\t')
	{
		//в разработке
		//drawmap(doom, doom->sector, doom->sdl);
	}
	if (ev.key.keysym.sym == SDLK_SPACE)
	{
		doom->player.velocity.z = 3.f;
		doom->player.fall = 1;
	}
	if (ev.key.keysym.sym == 'p')
	{
		profile_output(doom);
	}
	if (ev.key.keysym.sym == 'm')
		doom->sectors[doom->player.sector].light += 0.1f;
	if (ev.key.keysym.sym == 'n')
		doom->sectors[doom->player.sector].light -= 0.1f;
	if (ev.key.keysym.sym == '=')
		doom->sectors[doom->player.sector].ceil += 1;
	if (ev.key.keysym.sym == '-')
		doom->sectors[doom->player.sector].ceil -= 1;
	return (0);
}

int		keyup(t_doom *doom, SDL_Event ev)
{
	if (ev.button.button == SDL_BUTTON_LEFT)
		doom->lkey = 0;
	if (ev.button.button == SDL_BUTTON_RIGHT)
		doom->rkey = 0;
	if (ev.key.keysym.sym == 'w')
		doom->wsad[0] = 0;
	if (ev.key.keysym.sym == 's')
		doom->wsad[1] = 0;
	if (ev.key.keysym.sym == 'a')
		doom->wsad[2] = 0;
	if (ev.key.keysym.sym == 'd')
		doom->wsad[3] = 0;
	return (0);
}

int		shoot(t_doom *doom)
{
	int		i;
	int		t;

	play_sound(doom, SOUND_SHOOT);
	t = 0;
	i = 0;
	while (i < 32)
	{
		if (t == 3)
			break ;
		if (doom->obj_ind[i] == 1)
		{
			t++;
			enemy_on_hit(doom, &doom->enemies[i]);
		}
		i++;
	}
	return (0);
}

t_xyz 	find_wall_intersection(t_xy t, t_xyz p, t_xy w1, t_xy w2)
{
	t_xyz	i;
	float s1_x, s1_y, s2_x, s2_y;

    s1_x = w2.x - w1.x;
	s1_y = w2.y - w1.y;

    s2_x = t.x - p.x;
	s2_y = t.y - p.y;

    float s, f;
    s = (-s1_y * (w1.x - p.x) + s1_x * (w1.y - p.y)) / (-s2_x * s1_y + s1_x * s2_y);
    f = ( s2_x * (w1.y -p.y) - s2_y * (w1.x - p.x)) / (-s2_x * s1_y + s1_x * s2_y);

    if (s >= 0 && s <= 1 && f >= 0 && f <= 1)
    {
        // Collision detected
        i.x = w1.x + (f * s1_x);
        i.y = w1.y + (f * s1_y);
        return (i);
    }
	i.x = -1;
	i.y = -1;
	return (i);
}

int		shoot_wall(t_doom *doom, t_player player, t_sectors *sectors)
{
	int 	x;
	float	y;
	t_xy	t;
	t_xy	w1;
	t_xy	w2;
	t_xyz	p;
	t_sectors	*s;

	s = &sectors[player.sector];
	t.x = player.where.x + 10000 * player.pcos;
	t.y = player.where.y + 10000 * player.psin;
	
	w1 = s->vert[doom->lookwall];
	w2 = s->vert[doom->lookwall + 1];
	printf("wall - %d\n", doom->lookwall);
	printf("w1x - %f, w1y - %f\n", w1.x, w1.y);
	printf("w2x - %f, w2y - %f\n", w2.x, w2.y);
	p = find_wall_intersection(t, player.where, w1, w2);
	printf("x - %f, y - %f\n", p.x, p.y);
	doom->pics[0].p = p;
	doom->pics[0].wall = doom->lookwall;
	doom->pics[0].p.z = player.where.z + tan(-player.yaw) * (sqrt(pow(p.x - doom->player.where.x, 2) + pow(p.y - doom->player.where.y, 2)));
	findpicpoints(doom, &doom->pics[0], 10);
	//doom->shot_pics[n].p1 = w1;
	//doom->shot_pics[n].p2 = w2;
	//printf("x - %f, y - %f\n",doom->pics[0].p.x, doom->pics[0].p.y);
	return (0);
}

int		hooks(t_doom *doom, SDL_Event ev)
{	
	if (ev.type == SDL_MOUSEBUTTONDOWN)
	{
		if (ev.button.button == SDL_BUTTON_LEFT && !doom->player.reload && !doom->weapon[doom->player.weapon].states_frame && doom->weapon[doom->player.weapon].ammo)
		{
			doom->lkey = 1;
			if (doom->player.weapon)
				doom->weapon[doom->player.weapon].ammo--;
			if (doom->weapon[doom->player.weapon].anim_frame == 0)
				doom->weapon[doom->player.weapon].states_frame = 1;
			//перезарядка после 10 выстрелов у пистолета
			if (doom->player.weapon == 1)
			{
				doom->player.shoots++;
				if (doom->player.shoots == 10)
				{
					doom->player.shoots = 0;
					doom->player.reload = 1;
				}
			}
			if (doom->player.weapon == 0)
				find_pic_interaction(doom);
			shoot(doom);
			shoot_wall(doom, doom->player, doom->sectors);
			//printf("Weapon %d, Ammo - %d\n", doom->player.weapon, doom->weapon[doom->player.weapon].ammo);
		}
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
