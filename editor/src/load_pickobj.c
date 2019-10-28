/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_pickobj.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 19:04:14 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/28 20:07:38 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

int		load_enemy_p2(t_txt *txt)
{
	if (!(txt->stobj[27] = IMG_Load("img/enemy/headHit.png")))
		return (0);
	if (!(txt->stobj[28] = IMG_Load("img/enemy/headAttack1.png")))
		return (0);
	if (!(txt->stobj[29] = IMG_Load("img/enemy/headAttack2.png")))
		return (0);
	if (!(txt->stobj[30] = IMG_Load("img/enemy/headAttack3.png")))
		return (0);
	if (!(txt->stobj[31] = IMG_Load("img/enemy/headAttack4.png")))
		return (0);
	return (1);
}

int		load_enemy(t_txt *txt)
{
	if (!(txt->stobj[18] = IMG_Load("img/enemy/headN.png")))
		return (0);
	if (!(txt->stobj[19] = IMG_Load("img/enemy/headNE.png")))
		return (0);
	if (!(txt->stobj[20] = IMG_Load("img/enemy/headE.png")))
		return (0);
	if (!(txt->stobj[21] = IMG_Load("img/enemy/headSE.png")))
		return (0);
	if (!(txt->stobj[22] = IMG_Load("img/enemy/headS.png")))
		return (0);
	if (!(txt->stobj[23] = IMG_Load("img/enemy/headSW.png")))
		return (0);
	if (!(txt->stobj[24] = IMG_Load("img/enemy/headW.png")))
		return (0);
	if (!(txt->stobj[25] = IMG_Load("img/enemy/headNW.png")))
		return (0);
	if (!(txt->stobj[26] = IMG_Load("img/enemy/headDead.png")))
		return (0);
	if (!(load_enemy_p2(txt)))
		return (0);
	return (1);
}

int		load_medkit(t_txt *txt)
{
	if (!(txt->stobj[14] = IMG_Load("img/stobject/9.png")))
		return (0);
	if (!(txt->stobj[15] = IMG_Load("img/stobject/10.png")))
		return (0);
	if (!(txt->stobj[16] = IMG_Load("img/stobject/11.png")))
		return (0);
	if (!(txt->stobj[17] = IMG_Load("img/stobject/card.png")))
		return (0);
	return (1);
}

int		load_weap(t_txt *txt)
{
	if (!(txt->stobj[8] = IMG_Load("img/stobject/pistol.png")))
		return (0);
	if (!(txt->stobj[9] = IMG_Load("img/stobject/shotgun.png")))
		return (0);
	if (!(txt->stobj[10] = IMG_Load("img/stobject/ripper.png")))
		return (0);
	if (!(txt->stobj[11] = IMG_Load("img/stobject/ammo.png")))
		return (0);
	if (!(txt->stobj[12] = IMG_Load("img/stobject/7.png")))
		return (0);
	if (!(txt->stobj[13] = IMG_Load("img/stobject/8.png")))
		return (0);
	return (1);
}

int		load_pickobj(t_doom *doom)
{
	if (!(load_weap(doom->txt)))
		return (0);
	if (!(load_medkit(doom->txt)))
		return (0);
	if (!(load_enemy(doom->txt)))
		return (0);
	return (1);
}
