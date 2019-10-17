/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 18:28:42 by dtoy              #+#    #+#             */
/*   Updated: 2019/10/17 12:50:33 by dtoy             ###   ########.fr       */
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

int		keydown(t_doom *doom, SDL_Event ev)
{
	if (ev.key.keysym.sym == '\033')
	{
		SDL_Quit();
		exit(0);
	}
	if (ev.key.keysym.sym == '1')
	{
		doom->player.weapon = 0;
		doom->weapon[doom->player.weapon].anim_frame = 0;
		doom->weapon[doom->player.weapon].states_frame = 0;
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
	if (ev.key.keysym.sym == 'r' && doom->player.weapon != 0)
		doom->player.reload = 1;
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
		profile_output(doom);
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
	//if (ev.button.button == SDL_BUTTON_LEFT)
	//	doom->lkey = 0;
	//if (ev.button.button == SDL_BUTTON_RIGHT)
	//	doom->rkey = 0;
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

int		hooks(t_doom *doom, SDL_Event ev)
{	
	if (ev.type == SDL_MOUSEBUTTONDOWN)
		if (ev.button.button == SDL_BUTTON_LEFT)
		{
			if (doom->weapon[doom->player.weapon].anim_frame == 0)
				doom->weapon[doom->player.weapon].states_frame = 1;
			doom->lkey = 1;
		}
		if (ev.button.button == SDL_BUTTON_RIGHT)
			doom->rkey = 1;
	if (ev.type == SDL_MOUSEBUTTONUP)
		if (ev.button.button == SDL_BUTTON_LEFT)
		{
			//doom->weapon[doom->player.weapon].states_frame = 0;
			//doom->weapon[doom->player.weapon].anim_frame = 0;
			doom->lkey = 0;
		}
		if (ev.button.button == SDL_BUTTON_RIGHT)
			doom->rkey = 0;
	if (ev.type == SDL_KEYDOWN)
		keydown(doom, ev);
	if (ev.type == SDL_KEYUP)
		keyup(doom, ev);
	return (0);
}
