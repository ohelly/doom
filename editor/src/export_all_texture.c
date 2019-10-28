/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_all_texture.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 15:46:55 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/28 18:17:03 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

void	export_all_texture(t_doom *doom)
{
	export_sky_tx(doom);
	export_wall_tx(doom);
	export_ceil_tx(doom);
	export_floor_tx(doom);
	export_shot_tx(doom);
	export_weapon_data(doom);
	export_stobj_data(doom);
}
