/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 16:27:03 by ohelly            #+#    #+#             */
/*   Updated: 2019/09/15 21:10:00 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		check_extension(char *av)
{
	int		i;

	i = ft_strlen(av) - 4;
	if (!(ft_strcmp(&av[i], ".map")))
		return (0);
	return (1);
}

/*int		check_line(char *line)
{
	static int		tr = 1;
	
	if (!(ft_strnstr(line, "vertex\t", 7)) && tr == 1)
		return (1);
	printf("kek\n");
	return (0);
}

int		check_map(t_doom *doom)
{
	char	*line;

	while (get_next_line(doom->file->fd, &line))
		if (check_line(line))
			return (1);
	return (0);
}
*/
int		get_range(char *line, char c)
{
	int		i = 13;

	if (c == 'e')
	{
		while (line[i] != '\t')
			i++;
		return (i);
	}
	else if (c == 's')
	{
		while (line[i] == ' ')
			i++;
		return (i);
	}
	return (0);
}

int		get_wall(char *line, t_doom *doom)
{
	int			i;
	int			j;
	char		**vert;
	static int	sect = 0;

	i = 0;
	j = 0;
	vert = ft_strsplit(line, ' ');
	while (vert[i + 1] != 0)
	{
		doom->walls->count++;
		doom->walls->wall[doom->walls->i].sectors = sect;
		doom->walls->wall[doom->walls->i].vert_one = atoi(vert[i]);
		doom->walls->wall[doom->walls->i].vert_two = atoi(vert[i + 1]);
		doom->walls->i++;
		i++;
	}
	doom->walls->count++;
	doom->walls->wall[doom->walls->i].sectors = sect;
	doom->walls->wall[doom->walls->i].vert_one = atoi(vert[i]);
	doom->walls->wall[doom->walls->i].vert_two = atoi(vert[0]);
	doom->walls->i++;
	i = 0;
	while (vert[i] != 0)
	{
		free(vert[i]);
		vert[i] = 0;
	}
	free(vert);
	vert = 0;
	sect++;
	return (0);
}

int		read_line(char *line, t_doom *doom)
{
	int			i;
	int			imax;
	char		*sub_line;

	if (ft_strnstr(line, "vertex\t", 7))
	{
		i = 7;
		while (line[i] != '\t')
			i++;
		while (line[i] != '\0')
		{
			doom->verts->count++;
			doom->verts->list[doom->verts->i].pos.y = atoi(&line[7]) * 10;
			doom->verts->list[doom->verts->i].pos.x = atoi(&line[i]) * 10;
			doom->verts->i++;
			while (line[i++] != ' ')
				if (line[i] == '\0')
					break;
		}
	}
	if (ft_strnstr(line, "sector\t", 7))
	{
		i = get_range(line, 's');
		imax = get_range(line, 'e');
		sub_line = ft_strsub(line, i, imax - i);
		if (get_wall(sub_line, doom))
			return (1);
		free(sub_line);
	}
	free(line);
	return (0);
}

int		read_map(int fd, t_doom *doom)
{
	char	*line;

	while (get_next_line(fd, &line))
		if (read_line(line, doom))
			return (1);
	return (0);
}

int		load_map(char *av, t_doom *doom)
{
	int		i = -1;

	if (check_extension(av))
		return (1);
	doom->file->file_name = av;
	if ((doom->file->fd = open(av, O_RDONLY)) == -1)
		return (0);
	/*if (check_map(doom))
		return (2);*/
	if (read_map(doom->file->fd, doom))
		return (3);
	close(doom->file->fd);
	return (0);
}