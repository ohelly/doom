/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 16:27:03 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/30 17:36:23 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

int		check_extension(char *av)
{
	int		i;

	i = ft_strlen(av) - 4;
	if (!(ft_strcmp(&av[i], ".map")))
		return (0);
	return (1);
}

void	load_vertex(t_doom *doom, char *line)
{
	int		i;
	int		y;

	i = 7;
	y = ft_atoi(&line[i]);
	while (line[i] != '\t')
		i++;
	while (line[i] != '\0')
	{
		doom->verts->list[doom->verts->count].pos.y = y;
		doom->verts->list[doom->verts->count].pos.x = ft_atoi(&line[i]);
		while (line[i] != ' ' && line[i] != '\0')
			i++;
		doom->verts->count++;
		if (line[i] == '\0')
			break ;
		i++;
	}
}

int		read_map(int fd, t_doom *doom)
{
	char	*line;
	int		tr;

	tr = 1;
	while (get_next_line(fd, &line))
	{
		if (ft_strnstr(line, "Vertex", 6))
			load_vertex(doom, line);
		else if (ft_strnstr(line, "Sector", 6))
			load_sector(doom, line);
		else if (ft_strnstr(line, "Objs", 4))
			load_obj(doom, line);
		else if (ft_strnstr(line, "Pics", 4))
			load_spr(doom, line);
		else if (ft_strnstr(line, "Player", 6))
			import_player(doom, line);
		else if (ft_strnstr(line, "CVerts", 6))
			doom->verts->cs = ft_atoi(&line[7]);
		free(line);
	}
	return (0);
}

int		load_map(char *av, t_doom *doom)
{
	if (check_extension(av))
		return (1);
	doom->file->file_name = av;
	if ((doom->file->fd = open(av, O_RDONLY)) == -1)
		return (0);
	if (read_map(doom->file->fd, doom))
		return (3);
	close(doom->file->fd);
	return (0);
}
