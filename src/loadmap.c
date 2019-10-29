                                                                         /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 16:46:56 by dtoy              #+#    #+#             */
/*   Updated: 2019/10/29 00:59:40 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static int	count_map_lines(char *av)
{
	int		i;
	int		fd;
	char	*line;

	i = 0;
	if ((fd = open(av, O_RDONLY)) == -1)
		return (0);
	while (get_next_line(fd, &line))
	{
		free(line);
		i++;
	}
	close(fd);
	return (i);
}

int			load_map(t_doom *doom, char *av)
{
	int		fd;
	int		i;
	char	*line;

	i = count_map_lines(av);
	if (!(doom->map = (char**)ft_memalloc(sizeof(char*) * (i + 1))))
		return (0);
	fd = open(av, O_RDONLY);
	
	i = 0;
	while (get_next_line(fd, &line))
	{
		if (!(doom->map[i] = ft_strdup(line)))
			return (0);
		free(line);
		i++;
	}
	doom->map[i] = NULL;
	close(fd);
	return (1);
}
