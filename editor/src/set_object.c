/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_object.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 18:42:53 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/29 00:58:13 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

static void		error(char *str, t_doom *doom)
{
	doom->hud->msg = str;
	doom->sects->selected_sector = -1;
	doom->verts->projected_v = (t_vertex) { -1, { -1, -1 } };
}

void			set_object(t_doom *doom)
{
	get_closest_wall(doom);
	if (doom->walls->wall[doom->verts->projected_v.num].sectors !=
	doom->sects->selected_sector)
	{
		error("Select sector", doom);
		return ;
	}
	if (doom->verts->projected_v.pos.x == doom->mouse->ppos.x &&
	doom->verts->projected_v.pos.y == doom->mouse->ppos.y)
	{
		error("Set on floor", doom);
		return ;
	}
	doom->obj->obj[doom->obj->count].sector = doom->sects->selected_sector;
	doom->obj->obj[doom->obj->count].pos = doom->mouse->ppos;
	doom->obj->count++;
	doom->verts->projected_v = (t_vertex) { -1, { -1, -1 } };
	doom->sects->selected_sector = -1;
}
