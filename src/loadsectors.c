/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadsectors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 12:15:03 by dtoy              #+#    #+#             */
/*   Updated: 2019/10/29 18:30:24 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		takencount(char *str)
{
	int		j;
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

char	*neighinsect(char *str, t_sectors *s, int vnum)
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

char	*wallsinsect(char *str, t_sectors *s, int vnum)
{
	int		j;
	float	tmp;

	j = 0;
	while (j < vnum)
	{
		str = todigit(str, &tmp);
		s->txtw[j] = (int)tmp;
		j++;
	}
	return (str);
}

int		loadsectors(t_sectors *s, t_xy *v, char *str)
{
	static int	n = 0;
	float		tmp;
	int			vnum;

	vnum = ((takencount(str) - 7) / 3);
	s[n].npoints = vnum;
	if (!(s[n].vert = ft_memalloc(sizeof(t_xy) * (vnum + 1))))
		return (0);
	if (!(s[n].neighbors = ft_memalloc(sizeof(int) * vnum)))
		return (0);
	if (!(s[n].txtw = ft_memalloc(sizeof(int) * vnum)))
		return (0);
	str = todigit(str, &s[n].floor);
	str = todigit(str, &s[n].ceil);
	s[n].constceil = s[n].ceil;
	str = vertinsect(str, s[n].vert, v, vnum);
	str = neighinsect(str, &s[n], vnum);
	str = wallsinsect(str, &s[n], vnum);
	str = todigit(str, &tmp);
	s[n].txtf = (int)tmp;
	str = todigit(str, &tmp);
	s[n].txtc = (int)tmp;
	str = todigit(str, &s[n].light);
	s[n].light = s[n].light / 100.0f;
	str = todigit(str, &tmp);
	s[n].type = (int)tmp;
	if (s[n].type == 1 || s[n].type == 2)
		s[n].ceil = s[n].floor;
	str = todigit(str, &tmp);
	s[n].sky = (int)tmp;
	s[n].open = 0;
	s[n].close = 1;
	n++;
	return (1);
}
