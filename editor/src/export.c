/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 14:03:00 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/29 15:26:32 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

void	save(t_doom *doom)
{
	if (doom->player->end == -1)
	{
		doom->hud->msg = "Set player";
		return ;
	}
	if (open(doom->file->file_name, O_RDONLY))
		remove(doom->file->file_name);
	doom->file->fd = open(doom->file->file_name, O_WRONLY | O_CREAT, 444);
	export_all_texture(doom);
	export_vert(doom);
	export_sector(doom);
	export_objs(doom);
	export_pospics(doom);
	export_player(doom);
	close(doom->file->fd);
	doom->hud->msg = "Saved file!";
	return (0);
}
