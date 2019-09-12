/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 16:27:03 by ohelly            #+#    #+#             */
/*   Updated: 2019/09/12 19:52:38 by ohelly           ###   ########.fr       */
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

int		check_line(char *line)
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

int		read_line(char *line, t_doom *doom)
{
	int		i;

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
		//	printf("i = %d  y = %d   x = %d\n", doom->verts->i, doom->verts->list[doom->verts->i].pos.y, doom->verts->list[doom->verts->i].pos.x);
			doom->verts->i++;
			while (line[i++] != ' ')
				if (line[i] == '\0')
					break;
		}
	}
	//printf("%d\n", doom->verts->count);
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
	if (check_extension(av))
		return (1);
	doom->file->file_name = av;
	if ((doom->file->fd = open(av, O_RDONLY)) == -1)
		return (0);
	/*if (check_map(doom))
		return (2);*/
	if (read_map(doom->file->fd, doom))
		return (3);
	return (0);
}