/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_pics.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 20:57:22 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/28 21:03:54 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

int			load_animspr(t_txt *txt)
{
	if (!(txt->pics[6] = IMG_Load("img/sprite/t1.png")))
		return (0);
	if (!(txt->pics[7] = IMG_Load("img/sprite/t2.png")))
		return (0);
	if (!(txt->pics[8] = IMG_Load("img/sprite/t3.png")))
		return (0);
	if (!(txt->pics[9] = IMG_Load("img/sprite/v2.png")))
		return (0);
	if (!(txt->pics[10] = IMG_Load("img/sprite/v3.png")))
		return (0);
	if (!(txt->pics[11] = IMG_Load("img/sprite/v4.png")))
		return (0);
	if (!(txt->pics[12] = IMG_Load("img/sprite/v5.png")))
		return (0);
	if (!(txt->pics[13] = IMG_Load("img/sprite/v1.png")))
		return (0);
	return (1);
}

int			load_switch(t_txt *txt)
{
	if (!(txt->pics[4] = IMG_Load("img/stsprite/p5.png")))
		return (0);
	if (!(txt->pics[5] = IMG_Load("img/stsprite/p6.png")))
		return (0);
	return (1);
}

int			load_stsprite(t_txt *txt)
{
	if (!(txt->pics[0] = IMG_Load("img/stsprite/p1.png")))
		return (0);
	if (!(txt->pics[1] = IMG_Load("img/stsprite/p2.png")))
		return (0);
	if (!(txt->pics[2] = IMG_Load("img/stsprite/p3.png")))
		return (0);
	if (!(txt->pics[3] = IMG_Load("img/stsprite/p4.png")))
		return (0);
	return (1);
}

int			load_pics(t_doom *doom)
{
	if (!(load_stsprite(doom->txt)))
		return (0);
	if (!(load_switch(doom->txt)))
		return (0);
	if (!(load_animspr(doom->txt)))
		return (0);
	return (1);
}
