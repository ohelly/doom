/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_and_mouse_press.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 22:12:24 by ohelly            #+#    #+#             */
/*   Updated: 2019/09/10 16:33:29 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		check_wall(t_doom *doom, int ind)
{
	int		i;

	i = -1;
	while (++i < doom->walls->count)
	{
		if (ind != -1)
		{
			if ((doom->walls->wall[i].vert_one == doom->verts->order[ind] &&
			doom->walls->wall[i].vert_two == doom->verts->order[ind + 1]) ||
			(doom->walls->wall[i].vert_one == doom->verts->order[ind + 1] &&
			doom->walls->wall[i].vert_two == doom->verts->order[ind]))
				return (1);
		}
		else if (ind == -1)
		{
			if ((doom->walls->wall[i].vert_one == doom->verts->order[doom->sects->sectors[doom->sects->i].end] &&
			doom->walls->wall[i].vert_two == doom->verts->order[doom->sects->sectors[doom->sects->i].start]) ||
			(doom->walls->wall[i].vert_one == doom->verts->order[doom->sects->sectors[doom->sects->i].start] &&
			doom->walls->wall[i].vert_two == doom->verts->order[doom->sects->sectors[doom->sects->i].end]))
				return (1);
		}
	}
	return (0);
}

void	in_walls(t_doom *doom)
{
	int		i;

	i = doom->sects->sectors[doom->sects->i].start;
	while (i != doom->sects->sectors[doom->sects->i].end)
	{
		if (check_wall(doom, i))
			;
		else
		{
			doom->walls->count++;
			doom->walls->wall[doom->walls->i].vert_one = doom->verts->order[i];
			doom->walls->wall[doom->walls->i].vert_two = doom->verts->order[i + 1];
			doom->walls->wall[doom->walls->i].sectors = doom->sects->i;
			doom->walls->wall[doom->walls->i].portal = -1;
			doom->walls->i++;
		}
		i++;
	}
	if (check_wall(doom, -1))
		;
	else
	{
		doom->walls->count++;
		doom->walls->wall[doom->walls->i].vert_one = doom->verts->order[doom->sects->sectors[doom->sects->i].end];
		doom->walls->wall[doom->walls->i].vert_two = doom->verts->order[doom->sects->sectors[doom->sects->i].start];
		doom->walls->wall[doom->walls->i].sectors = doom->sects->i;
		doom->walls->wall[doom->walls->i].portal = -1;
		doom->walls->i++;
	}
}

int		check_vert(t_doom *doom)
{
	int		i;

	i = -1;
	while (++i < doom->verts->count)
	{
		if (doom->app == 0)
		{
			if (doom->mouse->ppos.x == doom->verts->list[i].pos.x &&
			doom->mouse->ppos.y == doom->verts->list[i].pos.y)
			{
				doom->verts->order[doom->verts->i_o] = i;
				doom->sects->sectors[doom->sects->i].start = doom->verts->i_o;
				doom->verts->sel_v = doom->verts->i_o;
				doom->app = 1;
				doom->verts->i_o++;
				return (1);
			}
		}
		else if (doom->app == 1)
		{
			if (doom->mouse->ppos.x == doom->verts->list[i].pos.x &&
			doom->mouse->ppos.y == doom->verts->list[i].pos.y)
			{
				doom->verts->order[doom->verts->i_o] = i;
				doom->verts->i_o++;
				return (1);
			}
		}
	}
	return (0);
}

void	in_list(t_doom *doom)
{
	if (doom->app == 1 &&
		lines_intersect_loop(doom,
		doom->verts->list[doom->verts->order[doom->verts->i_o - 1]].pos,
		doom->mouse->ppos))
	{
		printf("Line intersects with something!!!\n");
		//return ;
	}
	doom->verts->list[doom->verts->i].pos.x = doom->mouse->ppos.x;
	doom->verts->list[doom->verts->i].pos.y = doom->mouse->ppos.y;
	if (doom->app == 0)
	{
		if (check_vert(doom))
			return ;
		else
		{
			doom->verts->list[doom->verts->i].pos.x = doom->mouse->ppos.x;
			doom->verts->list[doom->verts->i].pos.y = doom->mouse->ppos.y;
			doom->verts->order[doom->verts->i_o] = doom->verts->i;
			doom->sects->sectors[doom->sects->i].start = doom->verts->i_o;
			doom->verts->sel_v = doom->verts->i_o;
			doom->app = 1;
			doom->verts->i_o++;
			doom->verts->count++;
		}
	}
	else if (doom->app == 1)
	{
		if (doom->mouse->ppos.x == doom->verts->list[doom->verts->order[doom->verts->sel_v]].pos.x && doom->mouse->ppos.y == doom->verts->list[doom->verts->order[doom->verts->sel_v]].pos.y)
		{
			doom->app = 0;
			doom->sects->sectors[doom->sects->i].end = doom->verts->i_o - 1;
			in_walls(doom);
			doom->sects->i++;
			doom->sects->count++;
			return ;
		}
		else
		{
			if (check_vert(doom))
				return ;
			else
			{
				doom->verts->list[doom->verts->i].pos.x = doom->mouse->ppos.x;
				doom->verts->list[doom->verts->i].pos.y = doom->mouse->ppos.y;
				doom->verts->order[doom->verts->i_o] = doom->verts->i;
				doom->verts->i_o++;
				doom->verts->count++;
			}
		}
	}
	doom->verts->i++;
}

void	key_and_mouse_press(t_doom *doom)
{
	while (SDL_PollEvent(&doom->sdl->ev))
	{
		if (doom->sdl->ev.type == SDL_KEYDOWN)
		{
			if (doom->sdl->ev.key.keysym.sym == '\033')
				exit (0);
			if (doom->sdl->ev.key.keysym.sym == '-')
				doom->sh += 1;
			if (doom->sdl->ev.key.keysym.sym == '=' && doom->sh > 5)
				doom->sh -= 1;
			if (doom->sdl->ev.key.keysym.sym == ' ')
				in_list(doom);
			if (doom->sdl->ev.key.keysym.sym == 'e')
				save(doom);
			if (doom->sdl->ev.key.keysym.sym == 'w')
				get_closest_wall(doom);
			if (doom->sdl->ev.key.keysym.sym == 's')
				get_closest_sector(doom);
		}
		if (doom->sdl->ev.type == SDL_MOUSEMOTION)
			*doom->mouse = (t_mouse){ doom->sdl->ev.motion.x, doom->sdl->ev.motion.y, 0 ,0 };
		output(doom);
	}
}