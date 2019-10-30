/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 16:02:38 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/30 17:34:58 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

static void	init_default_value(t_doom *doom)
{
	*doom->swall = (t_swall){ -1, -1, -1, -1, -1 };
	*doom->player = (t_player){ { -1, -1 }, 0, -1, 100, 0, -1};
	doom->sh = 20;
	doom->sects->selected_sector = -1;
	doom->walls->selected_wall = -1;
	doom->walls->adjacent_wall = -1;
	doom->aspr->select_spr = -1;
	doom->obj->select_obj = -1;
	doom->hud->msg = 0;
	doom->verts->cs = -1;
}

static int	sdl_init_part_two(t_doom *doom)
{
	if (!(doom->file = (t_file*)ft_memalloc(sizeof(t_file))))
		return (die_msg("Failed to allocate file struct"));
	if (!(doom->swall = (t_swall*)ft_memalloc(sizeof(t_swall))))
		return (die_msg("Failed to allocate swall struct"));
	if (!(doom->hud = (t_hud*)ft_memalloc(sizeof(t_hud))))
		return (die_msg("Failed to allocate hud struct"));
	if (!(doom->txt = (t_txt*)ft_memalloc(sizeof(t_txt))))
		return (die_msg("Failed to allocate txt struct"));
	if (!(load_img_for_hud(doom->hud, doom->sdl, doom->txt)))
		return (die_msg("Failed to load IMG for hud"));
	if (!(load_img_for_txt(doom->txt, doom->sdl)))
		return (die_msg("Failed to load IMG for txt"));
	if (!(doom->aspr = (t_all_spr_wall*)ft_memalloc(sizeof(t_all_spr_wall))))
		return (die_msg("Failed to allocate aspr struct"));
	if (!(doom->obj = (t_all_spr_floor*)ft_memalloc(sizeof(t_all_spr_floor))))
		return (die_msg("Failed to allocate obj struct"));
	if (!(doom->sects = (t_all_sect*)ft_memalloc(sizeof(t_all_sect))))
		return (die_msg("Failed to allocate sects struct"));
	if (!(doom->walls = (t_all_walls*)ft_memalloc(sizeof(t_all_walls))))
		return (die_msg("Failed to allocate walls struct"));
	if (!(doom->mouse = (t_mouse*)ft_memalloc(sizeof(t_mouse))))
		return (die_msg("Failed to allocate mouse struct"));
	if (!(doom->verts = (t_all_vert*)ft_memalloc(sizeof(t_all_vert))))
		return (die_msg("Failed to allocate verts struct"));
	return (1);
}

int			sdl_init(t_doom *doom)
{
	if (SDL_Init(SDL_INIT_EVERYTHING))
		return (die_msg("SDL failed to init"));
	if ((TTF_Init()) == -1)
		return (die_msg("Failed to init TTF"));
	if (!(doom->sdl = (t_sdl*)ft_memalloc(sizeof(t_sdl))))
		return (die_msg("Failed to allocate sdl struct"));
	if (!(doom->sdl->win = SDL_CreateWindow("doom", 500, 500,
	WIDTH, HEIGHT, 0)))
		return (die_msg("SDL failed to create window"));
	if (!(doom->sdl->rend = SDL_CreateRenderer(doom->sdl->win, -1, 0)))
		return (die_msg("SDL failed to create rendered"));
	if (!(doom->sdl->tex = SDL_CreateTexture(doom->sdl->rend,
	SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, WIDTH, HEIGHT)))
		return (die_msg("SDL failed to create texture"));
	if (!(doom->sdl->pix = (int*)ft_memalloc(sizeof(int) * (WIDTH * HEIGHT))))
		return (die_msg("Failed to allocate pix array"));
	if (!(doom->line = (t_line*)ft_memalloc(sizeof(t_line))))
		return (die_msg("Failed to allocate line struct"));
	if (!(sdl_init_part_two(doom)))
		return (0);
	if (!(init_preview(doom)))
		return (0);
	init_default_value(doom);
	return (1);
}
