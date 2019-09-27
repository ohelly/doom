/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_sectors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 14:48:27 by dtoy              #+#    #+#             */
/*   Updated: 2019/09/19 14:55:37 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		takencount(char *str)
{
	int 	j;
	int		count;

	j = 0;
	count = 0;
	while (str[j])
	{
		if (ft_isdigit(str[j]) || str[j] == '-')
		{
			count++;
			while (ft_isdigit(str[j]) || str[j] == '-')
				j++;
		}
		else
			j++;
	}
	return (count);
}

int		loadsectors(t_doom *doom, t_xy *vert, char *str)
{
	static int	n = 0;
	size_t		j;
	int			v;
	int			t;
	int			vnum;

	vnum = 0;
	t = 0;
	v = (takencount(str) - 2) / 2;
	doom->sectors[n].npoints = v;
	doom->sectors[n].vertex = ft_memalloc((v + 1) * sizeof(t_xy));
	doom->sectors[n].neighbors = ft_memalloc(v * sizeof(int));
	j = 0;
	while (j < ft_strlen(str))
	{
		if (vnum == v)
			vnum = 0;
		if (ft_isdigit(str[j]) && t == 0)
		{
			doom->sectors[n].floor = atof(&str[j]);
			printf("Floor - %f\n", doom->sectors[n].floor);
			while (ft_isdigit(str[j]))
				j++;
			t = 1;
		}
		else if (ft_isdigit(str[j]) && t == 1)
		{
			doom->sectors[n].ceil = atof(&str[j]);
			printf("Ceil - %f\n", doom->sectors[n].ceil);
			while (ft_isdigit(str[j]))
				j++;
			t = 2;
		}
		else if (ft_isdigit(str[j]) && vnum < v && t == 2)
		{
			doom->sectors[n].vertex[vnum + 1] = vert[atoi(&str[j])];
			printf("y - %f, x - %f\n", doom->sectors[n].vertex[vnum + 1].y, doom->sectors[n].vertex[vnum + 1].x);
			vnum++;
			while (ft_isdigit(str[j]))
				j++;
			if (vnum == v)
				t = 3;
		}
		else if ((ft_isdigit(str[j]) || str[j] == '-') && vnum < v && t == 3)
		{
			doom->sectors[n].neighbors[vnum] = atoi(&str[j]);
			printf("vnum - %d\n", vnum);
			printf("Neigb - %d\n", doom->sectors[n].neighbors[vnum]);
			vnum++;
			while (ft_isdigit(str[j]) || str[j] == '-')
				j++;
		}
		else
			j++;
	}
	doom->sectors[n].vertex[0] = doom->sectors[n].vertex[v];
	n++;
	return (0);
}