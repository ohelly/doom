/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 14:29:21 by dtoy              #+#    #+#             */
/*   Updated: 2019/09/23 12:24:27 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		mapinarr(t_doom *doom)
{
	int		fd;
	int		i;
	char	*line;
	fd = open("map-clear.txt", O_RDONLY);
	i = 0;
	while (get_next_line(fd, &line))
		i++;
	doom->map = (char**)ft_memalloc(sizeof(char*) * (i + 1));
	close(fd);
	fd = open("map-clear.txt", O_RDONLY);
	i = 0;
	while (get_next_line(fd, &line))
	{
		doom->map[i] = ft_strdup(line);
		printf("%s\n", doom->map[i]);
		i++;
	}
	doom->map[i] = 0;
	close(fd);
	return (0);
}

int		countvertexes(char *str, t_doom *doom)
{
	size_t		j;

	j = 0;
	doom->numvertices--;
	while (j < ft_strlen(str))
	{
		if (ft_isdigit(str[j]))
		{
			doom->numvertices++;
			while (ft_isdigit(str[j]) || str[j] == '.')
				j++;
		}
		else
			j++;
	}
	return (0);
}

int		countall(t_doom *doom)
{
	int		i;

	i = 0;
	doom->numvertices = 0;
	doom->numsectors = 0;
	doom->numsprites = 0;
	while (doom->map[i])
	{
		if (*doom->map[i] == 'v')
			countvertexes(doom->map[i], doom);
		if (*doom->map[i] == 's')
			doom->numsectors++;
		if (*doom->map[i] == 'o')
			doom->numsprites++;
		i++;
	}
	printf("NumVertexes - %d\n", doom->numvertices);
	printf("NumSectors - %d\n", doom->numsectors);
	return (0);
}

int		loadall(t_doom *doom)
{
	int		i;
	t_xy	v[doom->numvertices];

	doom->sectors = ft_memalloc(doom->numsectors * sizeof(t_sector));
	doom->player = ft_memalloc(sizeof(t_player));
	doom->spr_stock = ft_memalloc(sizeof(t_xyzwh) * doom->numsprites);
	i = 0;
	while (doom->map[i])
	{
		if (*doom->map[i] == 'v')
			loadvertices(doom, v, doom->map[i]);
		else if (*doom->map[i] == 's')
			loadsectors(doom, v, doom->map[i]);
		else if (*doom->map[i] == 'o')
			loadsprites(doom->spr_stock, doom->map[i]);
		else if (*doom->map[i] == 'p')
		{
			loadplayer(doom->player, doom->map[i]);
			doom->player->where.z = doom->sectors[doom->player->sector].floor + EyeHeight;
		}
		i++;
	}
	return (0);
}

int		loadmap(t_doom *doom)
{
	mapinarr(doom);
	countall(doom);
	loadall(doom);
	doom->rensects = (int*)ft_memalloc(sizeof(int) * doom->numsectors);
	doom->item = (t_item*)ft_memalloc(sizeof(t_item) * doom->numsectors);
	return (0);
}