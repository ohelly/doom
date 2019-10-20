/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_sprite_on_wall.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 14:46:25 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/16 20:02:08 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

void		set_sprite_on_wall(t_doom *doom)
{
	get_closest_wall(doom);
	if (check_portal(doom))
		return ;
	if (doom->walls->wall[doom->verts->projected_v.num].sectors !=
	doom->sects->selected_sector)
	{
		doom->hud->msg = "Select sector";
		doom->sects->selected_sector = -1;
		doom->verts->projected_v = (t_vertex) { -1, -1, -1 };
		return ;
	}
	doom->aspr->spr[doom->aspr->count].wall = doom->verts->projected_v.num;
	doom->aspr->spr[doom->aspr->count].sector = doom->sects->selected_sector;
	doom->aspr->spr[doom->aspr->count].pos = doom->verts->projected_v.pos;
	doom->aspr->spr[doom->aspr->count].z =
	doom->sects->sectors[doom->sects->selected_sector].floor;
	doom->aspr->count++;
	doom->verts->projected_v = (t_vertex) { -1, -1, -1 };
	doom->sects->selected_sector = -1;
}
