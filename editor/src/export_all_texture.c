/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_all_texture.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 15:46:55 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/27 18:15:18 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

void	export_all_texture(t_doom *doom)
{
	//export_sky
	export_wall_tx(doom);
	export_ceil_tx(doom);
	export_floor_tx(doom);
}
