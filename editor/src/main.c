/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 17:57:29 by ohelly            #+#    #+#             */
/*   Updated: 2019/09/04 16:39:09 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int			die_msg(char *msg)
{
	ft_putendl(msg);
	return (0);
}

int			sdl_init(t_doom *doom)
{
	if (SDL_Init(SDL_INIT_EVERYTHING))
		return (die_msg("SDL failed to init"));
	if (!(doom->sdl = (t_sdl*)ft_memalloc(sizeof(t_sdl))))
		return (die_msg("Failed to allocate sdl struct"));
	if (!(doom->sdl->win = SDL_CreateWindow("domm", 500, 500, WIDTH, HEIGHT, 0)))
		return (die_msg("SDL failed to create window"));
	if (!(doom->sdl->rend = SDL_CreateRenderer(doom->sdl->win, -1, 0)))
		return (die_msg("SDL failed to create rendered"));
	if (!(doom->sdl->tex = SDL_CreateTexture(doom->sdl->rend, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, WIDTH, HEIGHT)))
		return (die_msg("SDL failed to create texture"));
	if (!(doom->sdl->pix = (int*)ft_memalloc(sizeof(int) * (WIDTH * HEIGHT))))
		return (die_msg("Failed to allocate pix array"));
	if (!(doom->line = (t_line*)ft_memalloc(sizeof(t_line))))
		return (die_msg("Failed to allocate line struct"));
	if (!(doom->mouse = (t_mouse*)ft_memalloc(sizeof(t_mouse))))
		return (die_msg("Failed to allocate mouse struct"));
	if (!(doom->verts = (t_all_vert*)ft_memalloc(sizeof(t_all_vert))))
		return (die_msg("Failed to allocate verts struct"));
	if (!(doom->sects = (t_all_sect*)ft_memalloc(sizeof(t_all_sect))))
		return (die_msg("Failed to allocate sects struct"));
	doom->sh = 20;
	return (1);
}


int			main(int ac, char **av)
{
	t_doom		*doom;

	if (!(doom = (t_doom*)ft_memalloc(sizeof(t_doom))))
		return (die_msg("Failed to allocate doom struct"));
	if (!(sdl_init(doom)))
		return (die_msg("Failed to init doom"));
	while (1)
		key_and_mouse_press(doom);
	return (0);
}