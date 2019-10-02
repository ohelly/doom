/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadsectors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 12:15:03 by dtoy              #+#    #+#             */
/*   Updated: 2019/10/02 17:53:12 by dtoy             ###   ########.fr       */
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

char	*vertinsect(char *str, t_xy *vert, t_xy *v, int vnum)
{
	int		j;
	float	tmp;

	j = 0;
	while (j < vnum)
	{
		str = todigit(str, &tmp);
		vert[j + 1] = v[(int)tmp];
		j++;
	}
	vert[0] = vert[j];
	return (str);
}

char	*neighinsect(char *str, t_sector *s, int vnum)
{
	int		j;
	float	tmp;

	j = 0;
	while (j < vnum)
	{
		str = todigit(str, &tmp);
		s->neighbors[j] = (int)tmp;
		j++;
	}
	return (str);
}

int		gettxtind(char *str, t_sector *s)
{
	float		tmp;

	str = todigit(str, &tmp);
	s->txtf = (int)tmp;
	str = todigit(str, &tmp);
	s->txtc = (int)tmp;
	str = todigit(str, &tmp);
	s->txtw = (int)tmp;
//	printf("txtw - %d\n", s->txtw);
	return (0);
}

int		loadsectors(t_sector *s, t_xy *v, char *str)
{
	static int	n = 0;
	int		vnum;
	int		j;

	vnum = ((takencount(str) - 2) / 2) - 1;
	printf("vnum - %d\n",vnum);
	printf("%s\n", str);
	s[n].npoints = vnum;
	if (!(s[n].vert = ft_memalloc(sizeof(t_xy) * (vnum + 1))))
		return (0);
	if (!(s[n].neighbors = ft_memalloc(sizeof(int) * vnum)))
		return (0);
	str = todigit(str, &s[n].floor);
	str = todigit(str, &s[n].ceil);
	str = vertinsect(str, s[n].vert, v, vnum);
	j = 0;
	
	while (j < s[n].npoints)
	{
		printf("y - %f, x - %f\n", s[n].vert[j].y, s[n].vert[j].x);
		printf("y - %f, x - %f\n", s[n].vert[j].y, s[n].vert[j].x);
		j++;
	}
	str = neighinsect(str, &s[n], vnum);
	gettxtind(str, &s[n]);
	n++;
	return (1);
}
