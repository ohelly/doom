/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_st_obj.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 18:00:22 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/28 23:24:42 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

int			load_slippy(t_txt *txt)
{
	if (!(txt->stobj[7] = IMG_Load("img/stobject/14.png")))
		return (0);
	return (1);
}

int			load_toilet(t_txt *txt)
{
	if (!(txt->stobj[5] = IMG_Load("img/obj/12.png")))
		return (0);
	if (!(txt->stobj[6] = IMG_Load("img/obj/13.png")))
		return (0);
	return (1);
}

int			load_exp_propane(t_txt *txt)
{
	if (!(txt->stobj[2] = IMG_Load("img/obj/3.png")))
		return (0);
	if (!(txt->stobj[3] = IMG_Load("img/obj/4.png")))
		return (0);
	if (!(txt->stobj[4] = IMG_Load("img/obj/5.png")))
		return (0);
	return (1);
}

int			load_table_chair(t_txt *txt)
{
	if (!(txt->stobj[0] = IMG_Load("img/stobject/1.png")))
		return (0);
	if (!(txt->stobj[1] = IMG_Load("img/stobject/2.png")))
		return (0);
	return (1);
}

int			load_st_obj(t_doom *doom)
{
	if (!(load_table_chair(doom->txt)))
		return (0);
	if (!(load_exp_propane(doom->txt)))
		return (0);
	if (!(load_toilet(doom->txt)))
		return (0);
	if (!(load_slippy(doom->txt)))
		return (0);
	return (1);
}
