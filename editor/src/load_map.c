/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 16:27:03 by ohelly            #+#    #+#             */
/*   Updated: 2019/09/19 15:15:29 by ohelly           ###   ########.fr       */
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

int		get_wall(char *line, char *pr_line, t_doom *doom)
{
	int			i;
	int			p;
	char		**vert;
	char		**portal;
	static int	sect = 0;

	i = 0;
	p = 1;
	vert = ft_strsplit(line, ' ');
	portal = ft_strsplit(pr_line, ' ');
	while (vert[i + 1] != 0)
	{
		doom->walls->count++;
		doom->walls->wall[doom->walls->i].sectors = sect;
		doom->walls->wall[doom->walls->i].vert_one = atoi(vert[i]);
		doom->walls->wall[doom->walls->i].vert_two = atoi(vert[i + 1]);
		doom->walls->wall[doom->walls->i].portal = atoi(portal[p]);
		doom->walls->i++;
		p++;
		i++;
	}
	doom->walls->count++;
	doom->walls->wall[doom->walls->i].sectors = sect;
	doom->walls->wall[doom->walls->i].vert_one = atoi(vert[i]);
	doom->walls->wall[doom->walls->i].vert_two = atoi(vert[0]);
	doom->walls->wall[doom->walls->i].portal = atoi(portal[0]);
	doom->walls->i++;
	i = 0;
	while (vert[i] != 0)
	{
		free(vert[i]);
		free(portal[i]);
		vert[i] = 0;
		portal[i] = 0;
	}
	free(vert);
	free(portal);
	vert = 0;
	portal = 0;
	sect++;
	return (0);
}

int		read_line(char *line, t_doom *doom)
{
	int			i;
	int			imax;
	char		*sub_line;
	char		*pr_line;

	if (ft_strnstr(line, "vertex\t", 7))
	{
		i = 7;
		while (line[i] != '\t')
			i++;
		while (line[i] != '\0')
		{
			doom->verts->count++;
			doom->verts->list[doom->verts->i].pos.y = atoi(&line[7]);
			doom->verts->list[doom->verts->i].pos.x = atoi(&line[i]);
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
		pr_line = ft_strsub(line, imax, ft_strlen(line) - imax);
		if (get_wall(sub_line, pr_line, doom))
			return (1);
		free(sub_line);
		free(pr_line);
		doom->sects->count++;
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