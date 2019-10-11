/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 14:19:59 by lminta            #+#    #+#             */
/*   Updated: 2019/10/11 17:40:23 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

static int		ft_nextline(const int fd, char **line, char **tab)
{
	char		*tmp;
	int			i;

	i = 0;
	while (tab[fd][i] != '\n' && tab[fd][i] != '\0')
		i++;
	if (tab[fd][i] == '\n')
	{
		*line = ft_strsub(tab[fd], 0, i);
		tmp = ft_strsub(tab[fd], i + 1, (ft_strlen(tab[fd]) - i - 1));
		free(tab[fd]);
		tab[fd] = tmp;
		return (2);
	}
	else
	{
		*line = ft_strdup(tab[fd]);
		ft_strdel(&tab[fd]);
		return (1);
	}
}

int				get_next_line(const int fd, char **line)
{
	static char	*tab[MAX_FD];
	char		buf[BUFF_SIZE + 1];
	char		*tmp;
	long		ret;

	if (fd < 0 || fd > MAX_FD || line == NULL)
		return (-1);
	if (tab[fd] == NULL)
		tab[fd] = ft_strnew(1);
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		tmp = ft_strjoin(tab[fd], buf);
		free(tab[fd]);
		tab[fd] = ft_strdup(tmp);
		free(tmp);
		if (ft_strchr(buf, '\n') != NULL)
			break ;
	}
	if (ret < 0)
		return (-1);
	else if (ret == 0 && ft_strlen(tab[fd]) == 0)
		return (0);
	return (ft_nextline(fd, line, tab));
}
