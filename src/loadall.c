/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadall.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 11:21:04 by dtoy              #+#    #+#             */
/*   Updated: 2019/10/03 20:09:18 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

char		**loadmap(void)
{
	int		fd;
	int		i;
	char	**map;
	char	*line;

	fd = open("map-clear.txt", O_RDONLY);
	i = 0;
	while (get_next_line(fd, &line))
		i++;
	if (!(map = (char**)ft_memalloc(sizeof(char*) * (i + 1))))
		return (NULL);
	close(fd);
	fd = open("map-clear.txt", O_RDONLY);
	i = 0;
	while (get_next_line(fd, &line))
	{
		if (!(map[i] = ft_strdup(line)))
			return (NULL);
		i++;
	}
	map[i] = 0;
	close(fd);
	return (map);
}

int		loaddata(t_doom *doom, char **map)
{
	int		i;
	t_xy	v[doom->numvertexes];

	i = 0;
	while (map[i])
	{
		if (ft_strncmp(map[i], "vertex", ft_strlen("vertex")) == 0)
			loadvertexes(v, map[i]);
		else if (ft_strncmp(map[i], "sector", ft_strlen("sector")) == 0)
		{
			if (!(loadsectors(doom->sector, v, map[i])))
				return (0);
		}
		else if (ft_strncmp(map[i], "obj", ft_strlen("obj")) == 0)
			loadobjs(doom->obj, map[i]);
		else if (ft_strncmp(map[i], "pic", ft_strlen("pic")) == 0)
			loadpics(doom->pic, map[i]);
		else if (ft_strncmp(map[i], "player", ft_strlen("player")) == 0)
			loadplayer(&doom->player, map[i]);
		i++;
	}
	doom->player.where.z = doom->sector[doom->player.sector].floor + EyeHeight;
	return (1);
}

int		loadall(t_doom *doom)
{
	char	**map;
	int		j;

	j = 0;
	if (!(map = loadmap()))
		return (0);
	countall(doom, map);
	if (!(doom->sector = (t_sector*)ft_memalloc(sizeof(t_sector) * doom->numsectors)))
		return (0);
	if (!(doom->obj = (t_obj*)ft_memalloc(sizeof(t_obj) * doom->numobjs)))
		return (0);
	if (!(doom->len = (float*)ft_memalloc(sizeof(float) * doom->numobjs)))
		return (0);
	if (!(doom->item = (t_item*)ft_memalloc(sizeof(t_item) * doom->numsectors)))
		return (0);
	if (!(doom->pic = (t_pic*)ft_memalloc(sizeof(t_pic) * doom->numpics)))
		return (0);
	if (!(doom->txt = (t_texture*)ft_memalloc(sizeof(t_texture) * 1))) //нужно посчитать кол-во текстур
		return (0);
	if (!(loaddata(doom, map)))
		return (0);
	while (j < doom->numsectors)
	{
		printf("txtw - %d\n", doom->sector[j].txtw);		
		j++;
	}
	doom->wall_col_size = 0.2f;
	return (1);
}