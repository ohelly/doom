/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 17:57:29 by ohelly            #+#    #+#             */
/*   Updated: 2019/09/17 17:49:56 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int			die_msg(char *msg)
{
	ft_putendl(msg);
	exit(0);
	return (0);
}

int			puts_error(int err)
{
	if (err == 1)
		return (die_msg("Usage [.map] file"));
	if (err == 2)
		return (die_msg("Not a valid map"));
	if (err == 3)
		return (die_msg("Failed to read map"));
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
	if (!(doom->walls = (t_all_walls*)ft_memalloc(sizeof(t_all_walls))))
		return (die_msg("Failed to allocate walls struct"));
	if (!(doom->file = (t_file*)ft_memalloc(sizeof(t_file))))
		return (die_msg("Failed to allocate file struct"));
	doom->sh = 20;
	doom->save_name = "test.map";
	doom->sects->selected_sector = -1;
	doom->walls->selected_wall = -1;
	doom->walls->adjacent_wall = -1;
	return (1);
}

int			main(int ac, char **av)
{
	t_doom		*doom;
	int			err;

	if (ac == 1)
		return (die_msg("Usage [.map] file"));
	if (ac > 2)
		return (die_msg("Too many arguments"));
	if (!(doom = (t_doom*)ft_memalloc(sizeof(t_doom))))
		return (die_msg("Failed to allocate doom struct"));
	if (!(sdl_init(doom)))
		return (die_msg("Failed to init doom"));
	err = load_map(av[1], doom);
	if (err != 0)
		return (puts_error(err));
	while (1)
		key_and_mouse_press(doom);
	return (0);
}