/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_sprite_on_wall.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 14:46:25 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/29 00:57:41 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

int				check_sprite(t_doom *doom, int sw, int aw)
{
	int		i;

	i = -1;
	while (++i < doom->aspr->count)
	{
		if (doom->aspr->spr[i].wall == sw || doom->aspr->spr[i].wall == aw)
		{
			doom->hud->msg = "Sprite on wall";
			doom->walls->selected_wall = -1;
			doom->walls->adjacent_wall = -1;
			return (1);
		}
	}
	return (0);
}

static void		error(char *str, t_doom *doom)
{
	doom->hud->msg = str;
	doom->sects->selected_sector = -1;
	doom->verts->projected_v = (t_vertex) { -1, { -1, -1 } };
}

void			set_sprite_on_wall(t_doom *doom)
{
	get_closest_wall(doom);
	if (doom->walls->wall[doom->verts->projected_v.num].sectors !=
	doom->sects->selected_sector)
	{
		error("Select sector", doom);
		return ;
	}
	if (doom->walls->wall[doom->verts->projected_v.num].portal != -1 ||
	doom->walls->wall[doom->verts->projected_v.num].portal == -2)
	{
		error("Remove portal", doom);
		return ;
	}
	doom->aspr->spr[doom->aspr->count].wall = doom->verts->projected_v.num;
	doom->aspr->spr[doom->aspr->count].sector = doom->sects->selected_sector;
	doom->aspr->spr[doom->aspr->count].pos = doom->verts->projected_v.pos;
	doom->aspr->spr[doom->aspr->count].z =
	doom->sects->sectors[doom->sects->selected_sector].floor;
	doom->aspr->count++;
	doom->verts->projected_v = (t_vertex) { -1, { -1, -1 } };
	doom->sects->selected_sector = -1;
}
