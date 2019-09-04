/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_and_mouse_press.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 22:12:24 by ohelly            #+#    #+#             */
/*   Updated: 2019/09/04 16:16:42 by ohelly           ###   ########.fr       */
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
	else
	{
		if (doom->verts->list[doom->verts->i].pos.x == doom->verts->list[doom->verts->sel_v].pos.x && doom->verts->list[doom->verts->i].pos.y == doom->verts->list[doom->verts->sel_v].pos.y)
		{
			doom->app = 0;
			doom->sects->sectors[doom->sects->i].end = doom->verts->i;
			doom->sects->i++;
			doom->sects->count++;
		}
	}
	if (doom->verts->count > 2 && doom->app == 0)
	{
		printf("dist to line is %f\n",line_distance(doom->verts->list[0].pos, doom->verts->list[1].pos, doom->mouse->pos, NULL));
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
		}
		if (doom->sdl->ev.type == SDL_MOUSEMOTION)
			*doom->mouse = (t_mouse){ doom->sdl->ev.motion.x, doom->sdl->ev.motion.y, 0 ,0 };
		output(doom);
	}
}