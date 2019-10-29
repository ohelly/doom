/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadall.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 11:21:04 by dtoy              #+#    #+#             */
/*   Updated: 2019/10/29 18:08:59 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		load_shot_pics(t_pics *shots, t_texture *bullet)
{
	shots->images = (int**)ft_memalloc(sizeof(int*) * 1);
	shots->images[0] = (int*)ft_memalloc(sizeof(int) * 1);
	shots->anim_count = (int*)ft_memalloc(sizeof(int) * 1);
	shots->images[0][0] = bullet->image;
	shots->type = 5;
	shots->anim_count[0] = 1;
	shots->states_frame = 0;
	shots->states_count = 1;
	shots->anim_frame = 0;
	return (0);
}

int		load_data(t_doom *doom, char **map)
{
	int		i;

	i = 0;
	while (map[i])
	{
		if (ft_strcmp(map[i], "texture_data") == 0)
			load_texture_data(map, doom, i + 1);
		else if (ft_strcmp(map[i], "weapon_data") == 0)
			load_weapon_data(map, doom, i + 1);
		else if (ft_strcmp(map[i], "obj_data") == 0)
			load_obj_data(map, doom, i + 1);
		else if (ft_strcmp(map[i], "pic_data") == 0)
			load_pic_data(map, doom, i + 1);
		else
			i += 0;
		i++;
	}
	return (0);
}

int		load_all(t_doom *doom, char **av)
{
	if (!(load_map(doom, av[1])))
		return (0);
	load_data(doom, doom->map);
	load_params(doom, doom->map);
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024) < 0)
		printf("Error opening audio! %s\n", Mix_GetError());
	else
		printf("Audio loaded successfully!\n");
	load_music(doom);
	play_music(doom, 0);
	load_game(doom);
	return (1);
}
