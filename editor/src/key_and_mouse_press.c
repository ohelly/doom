/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_and_mouse_press.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 22:12:24 by ohelly            #+#    #+#             */
/*   Updated: 2019/09/03 16:43:53 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	in_list(t_doom *doom)
{
	doom->verts->list[doom->verts->i].x = doom->mouse->ppos_x;
	doom->verts->list[doom->verts->i].y = doom->mouse->ppos_y;
	if (doom->app == 0)
	{
		doom->verts->sel_v = doom->verts->i;
		doom->app = 1;
	}
	else
		if (doom->verts->list[doom->verts->i].x == doom->verts->list[doom->verts->sel_v].x && doom->verts->list[doom->verts->i].y == doom->verts->list[doom->verts->sel_v].y)
			doom->app = 0;
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