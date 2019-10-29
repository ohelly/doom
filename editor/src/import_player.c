/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 04:05:50 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/29 04:08:21 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

void	import_player_p2(t_doom *doom, char *line, int i)
{
	doom->player->hp = ft_atoi(&line[i]);
	while (!ft_isdigit(line[i]))
		i++;
	while (line[i] != '\t')
		i++;
	doom->player->weapon = ft_atoi(&line[i]);
	while (!ft_isdigit(line[i]))
		i++;
	while (line[i] != '\t')
		i++;
	doom->player->end = ft_atoi(&line[i]);
}

void	import_player(t_doom *doom, char *line)
{
	int		i;

	i = 7;
	doom->player->pos.y = ft_atoi(&line[i]);
	while (line[i] != ' ')
		i++;
	doom->player->pos.x = ft_atoi(&line[i]);
	while (line[i] != '\t')
		i++;
	doom->player->angle = ft_atoi(&line[i]);
	while (!ft_isdigit(line[i]))
		i++;
	while (line[i] != '\t')
		i++;
	doom->player->sec = ft_atoi(&line[i]);
	while (!ft_isdigit(line[i]))
		i++;
	while (line[i] != '\t')
		i++;
	import_player_p2(doom, line, i);
}
