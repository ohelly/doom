/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:47:36 by dtoy              #+#    #+#             */
/*   Updated: 2019/08/29 15:17:58 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int     mapinarr(t_doom *doom)
{  
    int     fd;
    int     i;
    char    *line;

    fd = open("map-clear.txt", O_RDONLY);
    i = 0;
    while (get_next_line(fd, &line))
        i++;
    doom->map = (char**)ft_memalloc(sizeof(char*) * (i + 1));
    close(fd);
    fd = open("map-clear.txt", O_RDONLY);
    i = 0;
    while (get_next_line(fd, &line))
    {
        doom->map[i] = ft_strdup(line);
        printf("%s\n", doom->map[i]);
        i++;
    }
    doom->map[i] = 0;
    close(fd);
    return (0);
}

int		countvertexes(char *str, t_doom *doom)
{
	int		j;

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

int		countall(t_doom *doom)
{
	int		i;
	int		j;

	i = 0;
	doom->numvertexes = 0;
	doom->numsectors = 0;
	while (doom->map[i])
    {	
		if (*doom->map[i] == 'v')
			countvertexes(doom->map[i], doom);
		if (*doom->map[i] == 's')
			doom->numsectors++;
		i++;
	}
	printf("NumVertexes - %d\n", doom->numvertexes);
	printf("NumSectors - %d\n", doom->numsectors);
	return (0);
}

int		loadvertexes(t_doom *doom, t_xy *vert, char *str)
{
	static int	n = 0;
	int			t;
	int			j;
	float		y;

	j = 0;
	t = 0;
	while (str[j])
	{
		if (ft_isdigit(str[j]) && t == 0)
		{
			t = 1;
			y = atof(&str[j]);
			while (ft_isdigit(str[j]) || str[j] == '.')
				j++;
		}
		else if (ft_isdigit(str[j]) && t == 1)
		{
			vert[n].y = y;
			vert[n].x = atof(&str[j]);
			while (ft_isdigit(str[j]) || str[j] == '.')
				j++;
			n++;
		}
		else
			j++;
	}
	return (0);
}

int		loadplayer(t_player *player, char *str)
{
	int		j;
	int		t;

	t = 0;
	j = 0;
	printf("\n");
	while (j < ft_strlen(str))
	{
		if (ft_isdigit(str[j]) && t == 0)
		{
			player->where.y = atoi(&str[j]);
			printf("Py - %f\n", player->where.y);
			t = 1;
			while (ft_isdigit(str[j]) || str[j] == '.')
				j++;
		}
		else if (ft_isdigit(str[j]) && t == 1)
		{
			player->where.x = atoi(&str[j]);
			printf("Px - %f\n", player->where.x);
			t = 2;
			while (ft_isdigit(str[j]) || str[j] == '.')
				j++;
		}
		else if (ft_isdigit(str[j]) && t == 2)
		{
			player->angle = atoi(&str[j]);
			printf("Angle - %f\n", player->angle);
			t = 3;
			while (ft_isdigit(str[j]) || str[j] == '.')
				j++;
		}
		else if (ft_isdigit(str[j]) && t == 3)
		{
			player->sector = atoi(&str[j]);
			printf("Sector - %d\n", player->sector);
			t = 4;
			while (ft_isdigit(str[j]) || str[j] == '.')
				j++;
		}
		else
			j++;
	}
	return (0);
}

int		loadall(t_doom *doom)
{
	int		i;
	int		j;
	t_xy	v[doom->numvertexes];

	doom->sectors = ft_memalloc(doom->numsectors * sizeof(t_sector));
	doom->player = ft_memalloc(sizeof(t_player));
	i = 0;
	while (doom->map[i])
	{
		if (*doom->map[i] == 'v')
			loadvertexes(doom, v, doom->map[i]);
		else if (*doom->map[i] == 's')
			loadsectors(doom, v, doom->map[i]);
		else if (*doom->map[i] == 'p')
		{
			loadplayer(doom->player, doom->map[i]);
			doom->player->where.z = doom->sectors[doom->player->sector].floor + EyeHeight;
		}
		i++;
	}
	return (0);
}

int		loadmap(t_doom *doom)
{
	mapinarr(doom);
	countall(doom);
	loadall(doom);
	return (0);
}