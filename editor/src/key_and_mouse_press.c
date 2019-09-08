/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_and_mouse_press.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 22:12:24 by ohelly            #+#    #+#             */
/*   Updated: 2019/09/04 18:45:15 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	in_walls(t_doom *doom)
{
	int		i;

	i = doom->sects->sectors[doom->sects->i].start;
	while (i != doom->sects->sectors[doom->sects->i].end)
	{
		doom->walls->count++;
		doom->walls->wall[doom->walls->i].vert_one = i;
		doom->walls->wall[doom->walls->i].vert_two = i + 1;
		doom->walls->wall[doom->walls->i].sectors = doom->sects->i;
		doom->walls->wall[doom->walls->i].portal = -1;
		doom->walls->i++;
		i++;
	}
}

void	in_list(t_doom *doom)
{
	if (lines_intersect_loop(doom, doom->verts->list[doom->verts->count - 1].pos, doom->verts->list[doom->verts->count].pos))
	{
		printf("Line intersects with something!!!\n");
		return ;
	}
	doom->verts->list[doom->verts->i].pos.x = doom->mouse->ppos.x;
	doom->verts->list[doom->verts->i].pos.y = doom->mouse->ppos.y;
	if (doom->app == 0)
	{
		doom->sects->sectors[doom->sects->i].start = doom->verts->i;
		doom->verts->sel_v = doom->verts->i;
		doom->app = 1;
	}
	else if (doom->app == 1)
	{
		if (doom->verts->list[doom->verts->i].pos.x == doom->verts->list[doom->verts->sel_v].pos.x && doom->verts->list[doom->verts->i].pos.y == doom->verts->list[doom->verts->sel_v].pos.y)
		{
			doom->app = 0;
			doom->sects->sectors[doom->sects->i].end = doom->verts->i;
			in_walls(doom);
			doom->sects->i++;
			doom->sects->count++;
		}
		doom->verts->count++;
	}
	doom->verts->count++;
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