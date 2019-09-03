/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 17:57:29 by ohelly            #+#    #+#             */
/*   Updated: 2019/09/03 17:35:39 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int			sdl_init(t_doom *doom)
{
	if (SDL_Init(SDL_INIT_EVERYTHING))
		return (0);
	if (!(doom->sdl = (t_sdl*)ft_memalloc(sizeof(t_sdl))))
		return (0);
	if (!(doom->sdl->win = SDL_CreateWindow("domm", 500, 500, WIDTH, HEIGHT, SDL_WINDOW_SHOWN)))
		return (0);
	if (!(doom->sdl->rend = SDL_CreateRenderer(doom->sdl->win, -1, 0)))
		return (0);
	if (!(doom->sdl->tex = SDL_CreateTexture(doom->sdl->rend, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, WIDTH, HEIGHT)))
		return (0);
	if (!(doom->sdl->pix = (int*)ft_memalloc(sizeof(int) * (WIDTH * HEIGHT))))
		return (0);
	if (!(doom->line = (t_line*)ft_memalloc(sizeof(t_line))))
		return (0);
	if (!(doom->mouse = (t_mouse*)ft_memalloc(sizeof(t_mouse))))
		return (0);
	if (!(doom->verts = (t_all_vert*)ft_memalloc(sizeof(t_all_vert))))
		return (0);
	doom->sh = 20;
	return (1);
}


int			main(int ac, char **av)
{
	t_doom		*doom;

	if (!(doom = (t_doom*)ft_memalloc(sizeof(t_doom))))
		return (0);
	if (!(sdl_init(doom)))
		return (0);
	while (1)
		key_and_mouse_press(doom);
	return (0);
}