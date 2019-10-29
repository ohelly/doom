/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_obj_spr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 04:03:53 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/29 04:04:48 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

void	load_spr(t_doom *doom, char *line)
{
	int		i;

	i = 8;
	doom->aspr->spr[doom->aspr->count].pos.y = ft_atoi(&line[i]);
	while (line[i] != ' ')
		i++;
	doom->aspr->spr[doom->aspr->count].pos.x = ft_atoi(&line[i]);
	while (line[i] != '\t')
		i++;
	doom->aspr->spr[doom->aspr->count].z = ft_atoi(&line[i]);
	while (!ft_isdigit(line[i]))
		i++;
	while (line[i] != '\t')
		i++;
	doom->aspr->spr[doom->aspr->count].wall = ft_atoi(&line[i]);
	while (!ft_isdigit(line[i]))
		i++;
	while (line[i] != '\t')
		i++;
	doom->aspr->spr[doom->aspr->count].sector = ft_atoi(&line[i]);
	doom->aspr->count++;
}

void	load_obj(t_doom *doom, char *line)
{
	int		i;

	i = 8;
	doom->obj->obj[doom->obj->count].pos.y = ft_atoi(&line[i]);
	while (line[i] != ' ')
		i++;
	doom->obj->obj[doom->obj->count].pos.x = ft_atoi(&line[i]);
	while (line[i] != '\t')
		i++;
	doom->obj->obj[doom->obj->count].sector = ft_atoi(&line[i]);
	doom->obj->count++;
}
