/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_header.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 20:02:16 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/27 12:38:09 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

void	load_txt_wall(t_doom, char *line, int i, int ind)
{
	return ;
}

void	value_sector(t_doom *doom, char *line)
{
	int		i;
	int		ind;

	i = 7;
	ind = ft_atoi(&line[i]);
	while (line[i] != '\t')
		i++;
	while (!(ft_isdigit(line[i])))
		i++;
	doom->sects->sectors[ind].txtf = ft_atoi(&line[i]);
	while (line[i] != '\t')
		i++;
	while (!(ft_isdigit(line[i])))
		i++;
	doom->sects->sectors[ind].txtc = ft_atoi(&line[i]);
	while (line[i] != '\t')
		i++;
	while (!(ft_isdigit(line[i])))
		i++;
	load_txt_wall(doom, line, i, ind);
}

int		load_header(t_doom *doom, char *line)
{
	if (ft_strnstr(line, "header {", 8))
		return (1);
	else if (ft_strnstr(line, "}", 1))
		return (0);
	else if (ft_strnstr(line, "Hsector", 7))
		value_sector(doom, line);
	return (1);
}
