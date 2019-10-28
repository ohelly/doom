/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 16:27:03 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/28 21:55:56 by ohelly           ###   ########.fr       */
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

int		load_portal(t_doom *doom, char *line, int i, int count)
{
	doom->walls->wall[doom->walls->count].portal = ft_atoi(&line[i]);
	while (line[i] != ' ')
		i++;
	while (line[i] != '\t' || line[i] != '\0')
	{
		doom->walls->wall[count].portal = ft_atoi(&line[++i]);
		while (line[i] != ' ' && line[i] != '\t' && line[i] != '\0')
			i++;
		count++;
		if (line[i] == '\t' || line[i] == '\0')
			break ;
	}
	return (i);
}

int		load_wall(t_doom *doom, char *line, int i)
{
	int		count;

	count = doom->walls->count;
	while (line[i] != '\t')
	{
		doom->walls->wall[doom->walls->count].sectors = doom->sects->count;
		doom->walls->wall[doom->walls->count].vert_one = ft_atoi(&line[i]);
		while (line[i] != ' ' && line[i] != '\t')
			i++;
		if (line[i] == '\t')
			break ;
		doom->walls->wall[doom->walls->count].vert_two = ft_atoi(&line[i]);
		while (!(ft_isdigit(line[i])))
			i++;
		doom->walls->count++;
	}
	doom->walls->wall[doom->walls->count].vert_two =
					doom->walls->wall[count].vert_one;
	i = load_portal(doom, line, i, count);
	doom->walls->count++;
	return (i);
}

void	load_attr(t_doom *doom, char *line, int i)
{
	int		type;

	while (!(ft_isdigit(line[i])))
		i++;
	doom->sects->sectors[doom->sects->count].light = ft_atoi(&line[i]);
	while (line[i] != '\t')
		i++;
	doom->sects->sectors[doom->sects->count].door = ft_atoi(&line[i]);
	while (!(ft_isdigit(line[i])))
		i++;
	i++;
	doom->sects->sectors[doom->sects->count].skyb = ft_atoi(&line[i]);
}

void	load_sector(t_doom *doom, char *line)
{
	int		i;

	i = 7;
	doom->sects->sectors[doom->sects->count].floor = ft_atoi(&line[i++]);
	while (line[i] != '\t')
		i++;
	doom->sects->sectors[doom->sects->count].ceiling = ft_atoi(&line[i++]);
	while (!(ft_isdigit(line[i])))
		i++;
	while (line[i] != '\t')
		i++;
	while (!(ft_isdigit(line[i])))
		i++;
	i = load_wall(doom, line, i);
	//load_attr(doom, line, i);
	doom->sects->count++;
}

void	load_obj(t_doom *doom, char *line)
{
	int		i;

	i = 5;
	doom->obj->obj[doom->obj->count].pos.y = ft_atoi(&line[i]);
	while (line[i] != ' ')
		i++;
	doom->obj->obj[doom->obj->count].pos.x = ft_atoi(&line[i]);
	while (line[i] != '\t')
		i++;
	doom->obj->obj[doom->obj->count].sector = ft_atoi(&line[i]);
	doom->obj->count++;
}

void	load_spr(t_doom *doom, char *line)
{
	int		i;

	i = 5;
	doom->aspr->spr[doom->aspr->count].pos.y = ft_atoi(&line[i]);
	while (line[i] != ' ')
		i++;
	doom->aspr->spr[doom->aspr->count].pos.x = ft_atoi(&line[i]);
	while (line[i] != '\t')
		i++;
	doom->aspr->spr[doom->aspr->count].z = ft_atoi(&line[i]);
	while (!ft_isdigit(line[i]))
		i++;
	while (line[i] != '\t')
		i++;
	doom->aspr->spr[doom->aspr->count].wall = ft_atoi(&line[i]);
	while (!ft_isdigit(line[i]))
		i++;
	while (line[i] != '\t')
		i++;
	doom->aspr->spr[doom->aspr->count].sector = ft_atoi(&line[i]);
	doom->aspr->count++;
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
		//else if (ft_strnstr(line, "header {", 8) && tr == 1)
		//	tr = load_header(doom, line);
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
