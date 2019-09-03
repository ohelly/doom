/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 17:57:29 by ohelly            #+#    #+#             */
/*   Updated: 2019/09/03 16:43:48 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int			sdl_init(t_doom *doom)
{
	if (SDL_Init(SDL_INIT_EVERYTHING))
		return (0);
	if (!(doom->sdl = (t_sdl*)ft_memalloc(sizeof(t_sdl))))
		return (0);
	SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &doom->sdl->win, &doom->sdl->rend);
	if (!(doom->line = (t_line*)ft_memalloc(sizeof(t_line))))
		return (0);
	if (!(doom->mouse = (t_mouse*)ft_memalloc(sizeof(t_mouse))))
		return (0);
	if (!(doom->verts = (t_all_vert*)ft_memalloc(sizeof(t_all_vert))))
		return (0);
/*	if (!(doom->verts->list = (t_vertex*)ft_memalloc(sizeof(t_vertex))))
		return (0);*/
//	doom->verts->start = doom->verts->list;
	doom->sh = 20;
//	doom->verts->sel_x = -1;
//	doom->verts->sel_y = -1;
	return (1);
}


int			main(int ac, char **av)
{
	t_doom		*doom;
	int			i;

	i = -1;
	if (!(doom = (t_doom*)ft_memalloc(sizeof(t_doom))))
		return (0);
	if (!(sdl_init(doom)))
		return (0);
	while (1)
		key_and_mouse_press(doom);
	return (0);
}