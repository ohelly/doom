/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_surface.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 16:34:13 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/27 16:45:49 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

int		load_txt_to_surface_p3(t_txt *txt)
{
	if (!(txt->swall[10] = IMG_Load("img/wall/wall11.png")))
		return (0);
	if (!(txt->swall[11] = IMG_Load("img/wall/wall12.png")))
		return (0);
	if (!(txt->swall[12] = IMG_Load("img/wall/wall13.png")))
		return (0);
	if (!(txt->swall[13] = IMG_Load("img/wall/wall14.png")))
		return (0);
	if (!(txt->swall[14] = IMG_Load("img/wall/wall15.png")))
		return (0);
	return (1);
}

int		load_txt_to_surface_p2(t_txt *txt)
{
	if (!(txt->swall[15] = IMG_Load("img/wall/wall16.png")))
		return (0);
	if (!(txt->swall[16] = IMG_Load("img/wall/wall17.png")))
		return (0);
	if (!(txt->swall[17] = IMG_Load("img/wall/wall18.png")))
		return (0);
	if (!(txt->swall[18] = IMG_Load("img/wall/wall19.png")))
		return (0);
	if (!(txt->swall[19] = IMG_Load("img/wall/wall20.png")))
		return (0);
	if (!(txt->swall[20] = IMG_Load("img/wall/wall21.png")))
		return (0);
	if (!(txt->swall[21] = IMG_Load("img/wall/1.png")))
		return (0);
	if (!(txt->swall[22] = IMG_Load("img/wall/2.png")))
		return (0);
	if (!(txt->swall[23] = IMG_Load("img/wall/3.png")))
		return (0);
	if (!(txt->swall[24] = IMG_Load("img/wall/4.png")))
		return (0);
	if (!(txt->swall[25] = IMG_Load("img/wall/5.png")))
		return (0);
	if (!(txt->swall[26] = IMG_Load("img/wall/6.png")))
		return (0);
	return (1);
}

int		load_txt_to_surface(t_txt *txt)
{
	if (!(txt->swall[0] = IMG_Load("img/wall/wall1.png")))
		return (0);
	if (!(txt->swall[1] = IMG_Load("img/wall/wall2.png")))
		return (0);
	if (!(txt->swall[2] = IMG_Load("img/wall/wall3.png")))
		return (0);
	if (!(txt->swall[3] = IMG_Load("img/wall/wall4.png")))
		return (0);
	if (!(txt->swall[4] = IMG_Load("img/wall/wall5.png")))
		return (0);
	if (!(txt->swall[5] = IMG_Load("img/wall/wall6.png")))
		return (0);
	if (!(txt->swall[6] = IMG_Load("img/wall/wall7.png")))
		return (0);
	if (!(txt->swall[7] = IMG_Load("img/wall/wall8.png")))
		return (0);
	if (!(txt->swall[8] = IMG_Load("img/wall/wall9.png")))
		return (0);
	if (!(txt->swall[9] = IMG_Load("img/wall/wall10.png")))
		return (0);
	if (!load_txt_to_surface_p2(txt) || !load_txt_to_surface_p3(txt))
		return (0);
	return (1);
}
