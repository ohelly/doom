/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_surface.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 18:17:56 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/28 20:01:27 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

int		load_surface(t_doom *doom)
{
	if (!(doom->txt->shot = IMG_Load("img/stsprite/shot.png")))
		return (0);
	if (!(doom->txt->ssky[0] = IMG_Load("img/skybox/skybox1.png")))
		return (0);
	if (!(load_weapon(doom)))
		return (0);
	if (!(load_st_obj(doom)))
		return (0);
	if (!(load_pickobj(doom)))
		return (0);
	return (1);
}