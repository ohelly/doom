/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   countall.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 11:26:30 by dtoy              #+#    #+#             */
/*   Updated: 2019/09/27 12:12:09 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		countvertexes(char *str, t_doom *doom)
{
	size_t		j;

	j = 0;
	doom->numvertexes--;
	while (j < ft_strlen(str))
	{
		if (ft_isdigit(str[j]))
		{
			doom->numvertexes++;
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

	i = 0;
	while (map[i])
	{
		if (*map[i] == '#')
			i++;
		if (ft_strncmp(map[i], "vertex", ft_strlen("vertex")) == 0)
			countvertexes(map[i], doom);
		if (ft_strncmp(map[i], "sector", ft_strlen("sector")) == 0)
			doom->numsectors++;
		if (ft_strncmp(map[i], "obj", ft_strlen("obj")) == 0)
			doom->numobjs++;
		if (ft_strncmp(map[i], "pic", ft_strlen("pic")) == 0)
			doom->numpics++;
		if (ft_strncmp(map[i], "txt", ft_strlen("txt")) == 0)
			doom->numtxts++;
		i++;
	}
	printf("NumVertexes - %d\n", doom->numvertexes);//<----------------------
	printf("NumSectors - %d\n", doom->numsectors);
	printf("NumObjs - %d\n", doom->numobjs);
	printf("NumPics - %d\n", doom->numpics);
	printf("NumTxts - %d\n", doom->numtxts);
	return (0);
}
