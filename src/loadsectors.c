/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadsectors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 12:15:03 by dtoy              #+#    #+#             */
/*   Updated: 2019/10/11 18:26:56 by dtoy             ###   ########.fr       */
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
		//printf("vert y - %f, x - %f\n", vert[j + 1].y, vert[j + 1].x);
		j++;
	}
	vert[0] = vert[j];
	return (str);
}

char	*neighinsect(char *str, t_sectors *s, int vnum)
{
	int		j;
	float	tmp;

	j = 0;
	while (j < vnum)
	{
		str = todigit(str, &tmp);
		s->neighbors[j] = (int)tmp;
		//printf("neighb - %d\n", s->neighbors[j]);
		j++;
	}
	return (str);
}

char	*wallsinsect(char *str, t_sectors *s, int vnum)
{
	int		j;
	float	tmp;

	j = 0;
	while (j < vnum)
	{
		str = todigit(str, &tmp);
		s->txtw[j] = (int)tmp;
		//printf("txtw - %d\n", s->txtw[j]);
		j++;
	}
	return (str);
}

int		loadsectors(t_sectors *s, t_xy *v, char *str)
{
	static int	n = 0;
	float	tmp;
	int		vnum;
	int		j;

	printf("\n");
	vnum = ((takencount(str) - 2) / 2) - 4;
	//printf("vnum - %d\n", vnum);
	s[n].npoints = vnum;
	if (!(s[n].vert = ft_memalloc(sizeof(t_xy) * (vnum + 1))))
		return (0);
	if (!(s[n].neighbors = ft_memalloc(sizeof(int) * vnum)))
		return (0);
	if (!(s[n].txtw = ft_memalloc(sizeof(int) * vnum)))
		return (0);
	str = todigit(str, &s[n].floor);
	//printf("floor - %f\n", s[n].floor);
	str = todigit(str, &s[n].ceil);
	//printf("ceil - %f\n", s[n].ceil);
	//s[n].tmpceil = s[n].ceil;
	str = vertinsect(str, s[n].vert, v, vnum);
	str = neighinsect(str, &s[n], vnum);
	//gettxtind(str, &s[n]);
	str = todigit(str, &tmp);
	s[n].txtf = (int)tmp;
	//printf("txtf - %d\n", s->txtf);
	str = todigit(str, &tmp);
	s[n].txtc = (int)tmp;
	//printf("txtc - %d\n", s->txtc);
	str = wallsinsect(str, &s[n], vnum);
	str = todigit(str, &s[n].light);
	s[n].light = s[n].light / 100.0f;
	//printf("light - %f\n", s[n].light);
	str = todigit(str, &tmp);
	s[n].type = (int)tmp;
	//printf("type - %d\n", s[n].type);
	str = todigit(str, &tmp);
	s[n].sky = (int)tmp;
	//printf("sky - %d\n", s[n].sky);
	n++;
	return (1);
}
