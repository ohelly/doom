/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_object.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 18:42:53 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/11 15:04:01 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

void		set_object(t_doom *doom)
{
	get_closest_wall(doom);
	if (doom->walls->wall[doom->verts->projected_v.num].sectors != doom->sects->selected_sector)
	{
		doom->hud->msg = "Select sector";
		doom->sects->selected_sector = -1;
		doom->verts->projected_v = (t_vertex) { -1, -1, -1 };
		return ;
	}
	doom->obj->obj[doom->obj->count].sector = doom->sects->selected_sector;
	doom->obj->obj[doom->obj->count].pos = doom->mouse->ppos;
	doom->obj->count++;
	doom->verts->projected_v = (t_vertex) { -1, -1, -1 };
	doom->sects->selected_sector = -1;
}