/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_sector.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 04:01:37 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/29 04:57:37 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

void	load_attr(t_doom *doom, char *line, int i)
{
	while (!(ft_isdigit(line[i])))
		i++;
	while (line[i] != '\t')
		i++;
	while (!(ft_isdigit(line[i])))
		i++;
	while (line[i] != '\t')
		i++;
	while (!(ft_isdigit(line[i])))
		i++;
	while (line[i] != '\t')
		i++;
	doom->sects->sectors[doom->sects->count].light = ft_atoi(&line[i]);
	while (!(ft_isdigit(line[i])))
		i++;
	while (line[i] != '\t')
		i++;
	doom->sects->sectors[doom->sects->count].door = ft_atoi(&line[i]);
	while (!(ft_isdigit(line[i])))
		i++;
	i++;
	doom->sects->sectors[doom->sects->count].skyb = ft_atoi(&line[i]);
}

int		load_portal(t_doom *doom, char *line, int i, int count)
{
	doom->walls->wall[doom->walls->count].portal = ft_atoi(&line[i]);
	while (line[i] != ' ')
		i++;
	while (line[i] != '\t' || line[i] != '\0')
	{
		doom->walls->wall[count].portal = ft_atoi(&line[++i]);
		while (line[i] != ' ' && line[i] != '\t' && line[i] != '\0')
			i++;
		count++;
		if (line[i] == '\t' || line[i] == '\0')
			break ;
	}
	return (i);
}

int		load_wall(t_doom *doom, char *line, int i)
{
	int		count;

	count = doom->walls->count;
	while (line[i] != '\t')
	{
		doom->walls->wall[doom->walls->count].sectors = doom->sects->count;
		doom->walls->wall[doom->walls->count].vert_one = ft_atoi(&line[i]);
		while (line[i] != ' ' && line[i] != '\t')
			i++;
		if (line[i] == '\t')
			break ;
		doom->walls->wall[doom->walls->count].vert_two = ft_atoi(&line[i]);
		while (!(ft_isdigit(line[i])))
			i++;
		doom->walls->count++;
	}
	doom->walls->wall[doom->walls->count].vert_two =
					doom->walls->wall[count].vert_one;
	i = load_portal(doom, line, i, count);
	doom->walls->count++;
	return (i);
}

void	load_sector(t_doom *doom, char *line)
{
	int		i;

	i = 7;
	doom->sects->sectors[doom->sects->count].floor = ft_atoi(&line[i++]);
	while (line[i] != '\t')
		i++;
	doom->sects->sectors[doom->sects->count].ceiling = ft_atoi(&line[i++]);
	while (!(ft_isdigit(line[i])))
		i++;
	while (line[i] != '\t')
		i++;
	while (!(ft_isdigit(line[i])))
		i++;
	i = load_wall(doom, line, i);
	load_attr(doom, line, i);
	doom->sects->count++;
}
