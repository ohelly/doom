/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadparams.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 17:31:34 by dtoy              #+#    #+#             */
/*   Updated: 2019/10/29 12:41:44 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		init_structs(t_doom *doom)
{
	if (!(doom->hud = (t_hud*)ft_memalloc(sizeof(t_hud))))
		return (0);
	if (!(doom->enemies = malloc(sizeof(t_enemy) * 64)))
		return (0);
	if (!(doom->sectors = (t_sectors*)ft_memalloc(
		sizeof(t_sectors) * doom->num.sectors)))
		return (0);
	if (!(doom->item = (t_item*)ft_memalloc(
		sizeof(t_item) * doom->num.sectors)))
		return (0);
	if (!(doom->objs = (t_obj*)ft_memalloc(sizeof(t_obj) * doom->num.objs)))
		return (0);
	if (!(doom->obj_ind = (int*)ft_memalloc(sizeof(int) * doom->num.objs)))
		return (0);
	if (!(doom->order = (int*)ft_memalloc(sizeof(int) * doom->num.objs)))
		return (0);
	if (!(doom->pics = (t_pics*)ft_memalloc(
		sizeof(t_pics) * (doom->num.pics + SHOTS_NUM))))
		return (0);
	if (!(doom->len = (float*)ft_memalloc(sizeof(float) * doom->num.objs)))
		return (0);
	if (!(doom->lookwall = (int*)ft_memalloc(sizeof(int) * doom->num.sectors)))
		return (0);
	return (1);
}

int		load_all_params(t_doom *doom, char **map, t_xy *v)
{
	int		i;

	i = 0;
	while (map[i])
	{
		if (ft_strncmp(map[i], "Vertex", 5) == 0)
			loadvertexes(v, map[i]);
		else if (ft_strncmp(map[i], "Sector", ft_strlen("sector")) == 0)
		{
			if (!(loadsectors(doom->sectors, v, map[i])))
				return (0);
		}
		else if (ft_strncmp(map[i], "Objs", ft_strlen("objs")) == 0)
			loadobjs(doom, map[i]);
		else if (ft_strncmp(map[i], "Pics", ft_strlen("pics")) == 0)
			loadpics(doom, doom->pics, doom->pics_data, map[i]);
		else if (ft_strncmp(map[i], "Player", ft_strlen("player")) == 0)
			loadplayer(&doom->player, map[i]);
		i++;
	}
	return (0);
}

int		load_params(t_doom *doom, char **map)
{
	t_xy	*v;

	countall(doom, map);
	if (!(v = (t_xy*)ft_memalloc(sizeof(t_xy) * doom->num.vertexes)))
		return (0);
	if (!(init_structs(doom)))
		return (0);
	load_all_params(doom, map, v);
	doom->player.where.z = doom->sectors[doom->player.sector].floor + EYEHEIGHT;
	doom->wall_col_size = 0.1f;
	load_shot_pics(&doom->shot_pics, &doom->bullet[0]);
	free(v);
	return (0);
}
