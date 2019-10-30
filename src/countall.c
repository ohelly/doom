/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   countall.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 11:26:30 by dtoy              #+#    #+#             */
/*   Updated: 2019/10/30 21:35:59 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		countvertexes(char *str, t_doom *doom)
{
	size_t		j;

	j = 0;
	doom->num.vertexes--;
	while (j < ft_strlen(str))
	{
		if (ft_isdigit(str[j]))
		{
			doom->num.vertexes++;
			while (ft_isdigit(str[j]) || str[j] == '.')
				j++;
		}
		else
			j++;
	}
	return (0);
}

int		countall(t_doom *doom, char **map)
{
	int		i;

	i = -1;
	while (map[++i])
	{
		if (*map[i] == '#')
			i++;
		if (ft_strncmp(map[i], "Vertex", ft_strlen("vertex")) == 0)
			countvertexes(map[i], doom);
		if (ft_strncmp(map[i], "Sector", ft_strlen("sector")) == 0)
			doom->num.sectors++;
		if (ft_strncmp(map[i], "Objs", ft_strlen("objs")) == 0)
			doom->num.objs++;
		if (ft_strncmp(map[i], "Pics", ft_strlen("pics")) == 0)
			doom->num.pics++;
	}
	return (0);
}
