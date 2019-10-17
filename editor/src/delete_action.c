/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_action.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 18:51:16 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/13 18:51:31 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

int	remove_built_sector(t_doom *doom)
{
	if (doom->verts->built_v_count == 0 || doom->app != 1)
		return (0);
	doom->verts->count -= doom->verts->built_v_count -
	doom->verts->built_v_count_used;
	doom->walls->count -= doom->verts->built_v_count - 1;
	doom->verts->built_v_count = 0;
	doom->verts->built_v_count_used = 0;
	doom->app = 0;
	return (1);
}
