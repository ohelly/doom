/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_and_mouse_press.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 22:12:24 by ohelly            #+#    #+#             */
/*   Updated: 2019/09/04 17:44:05 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

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
			doom->sects->i++;
			doom->sects->count++;
		}
	}
	doom->verts->i++;
}

void	calc_dist(t_doom *doom)
{
	if (doom->app == 2)
	{
		t_v2 p1 = doom->verts->list[0].pos;
		t_v2 p2 = doom->verts->list[1].pos;
		t_v2 m = doom->mouse->pos;
		printf("point pos %d:%d, mouse pos %d:%d; ", p1.x, p1.y, m.x, m.y);
		printf("dist to line is %f\n", line_distance(p1, p2, m, NULL));
	}
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
		}
		if (doom->sdl->ev.type == SDL_MOUSEMOTION)
			*doom->mouse = (t_mouse){ doom->sdl->ev.motion.x, doom->sdl->ev.motion.y, 0 ,0 };
		calc_dist(doom);
		output(doom);
	}
}