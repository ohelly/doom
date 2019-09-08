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

float	calc_dist(t_doom *doom, int vert1, int vert2)
{
	t_v2 p1 = doom->verts->list[vert1].pos;
	t_v2 p2 = doom->verts->list[vert2].pos;
	t_v2 m = doom->mouse->pos;
	return (line_distance(p1, p2, m, NULL));
	//printf("point pos %d:%d, mouse pos %d:%d; ", p1.x, p1.y, m.x, m.y);
	//printf("dist to line is %f\n", line_distance(p1, p2, m, NULL));
}

void	get_closest_sector(t_doom *doom)
{
	int wall;
	int i;

	wall = get_closest_wall(doom);
	printf("Selected sector %d\n", doom->walls->wall[wall].sectors);
	doom->sects->selected_sector = doom->walls->wall[wall].sectors;
}

int		get_closest_wall(t_doom *doom)
{
	int		i;
	float	dist;
	int		saved_wall;
	float	saved_dist;
	t_v2	curr_vertices;	//current wall vertices index
	
	i = 0;
	saved_wall = -1;
	saved_dist = 1000;
	while (i < doom->walls->count)
	{
		curr_vertices.x = doom->walls->wall[i].vert_one;
		curr_vertices.y = doom->walls->wall[i].vert_two;
		dist = calc_dist(doom, curr_vertices.x, curr_vertices.y);
		if (dist < saved_dist)
		{
			saved_wall = i;
			saved_dist = dist;
		}
		i++;
	}
	if (saved_dist < 30)
		printf("Closest wall is %d, with distance %f\n", saved_wall, saved_dist);
	return (saved_wall);
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