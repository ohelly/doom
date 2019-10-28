/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_weapon.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 16:51:55 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/28 17:14:42 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

int			load_ripper(t_txt *txt)
{
	if (!(txt->ripper[0] = IMG_Load("img/weapon/ripper1.png")))
		return (0);
	if (!(txt->ripper[1] = IMG_Load("img/weapon/ripper4.png")))
		return (0);
	if (!(txt->ripper[2] = IMG_Load("img/weapon/ripper3.png")))
		return (0);
	if (!(txt->ripper[3] = IMG_Load("img/weapon/ripper2.png")))
		return (0);
	if (!(txt->ripper[4] = IMG_Load("img/weapon/ripper5.png")))
		return (0);
	if (!(txt->ripper[5] = IMG_Load("img/weapon/ripper6.png")))
		return (0);
	if (!(txt->ripper[6] = IMG_Load("img/weapon/ripper7.png")))
		return (0);
	return (1);
}

int			load_shotgun(t_txt *txt)
{
	if (!(txt->shotgun[0] = IMG_Load("img/weapon/shotgun1.png")))
		return (0);
	if (!(txt->shotgun[1] = IMG_Load("img/weapon/shotgun2.png")))
		return (0);
	if (!(txt->shotgun[2] = IMG_Load("img/weapon/shotgun3.png")))
		return (0);
	if (!(txt->shotgun[3] = IMG_Load("img/weapon/shotgun4.png")))
		return (0);
	if (!(txt->shotgun[4] = IMG_Load("img/weapon/shotgun5.png")))
		return (0);
	if (!(txt->shotgun[5] = IMG_Load("img/weapon/shotgun6.png")))
		return (0);
	if (!(txt->shotgun[6] = IMG_Load("img/weapon/shotgun5.png")))
		return (0);
	if (!(txt->shotgun[7] = IMG_Load("img/weapon/shotgun4.png")))
		return (0);
	return (1);
}

int			load_pistol(t_txt *txt)
{
	if (!(txt->pistol[0] = IMG_Load("img/weapon/pistol1.png")))
		return (0);
	if (!(txt->pistol[1] = IMG_Load("img/weapon/pistol2.png")))
		return (0);
	if (!(txt->pistol[2] = IMG_Load("img/weapon/pistol3.png")))
		return (0);
	if (!(txt->pistol[3] = IMG_Load("img/weapon/pistol4.png")))
		return (0);
	if (!(txt->pistol[4] = IMG_Load("img/weapon/pistol5.png")))
		return (0);
	if (!(txt->pistol[5] = IMG_Load("img/weapon/pistol6.png")))
		return (0);
	if (!(txt->pistol[6] = IMG_Load("img/weapon/pistol7.png")))
		return (0);
	if (!(txt->pistol[7] = IMG_Load("img/weapon/pistol5.png")))
		return (0);
	if (!(txt->pistol[8] = IMG_Load("img/weapon/pistol8.png")))
		return (0);
	if (!(txt->pistol[9] = IMG_Load("img/weapon/pistol9.png")))
		return (0);
	if (!(txt->pistol[10] = IMG_Load("img/weapon/pistol10.png")))
		return (0);
	if (!(txt->pistol[11] = IMG_Load("img/weapon/pistol4.png")))
		return (0);
	return (1);
}

int			load_foot(t_txt *txt)
{
	if (!(txt->foot[0] = IMG_Load("img/weapon/foot1.png")))
		return (0);
	if (!(txt->foot[1] = IMG_Load("img/weapon/foot2.png")))
		return (0);
	if (!(txt->foot[2] = IMG_Load("img/weapon/foot1.png")))
		return (0);
	return (1);
}

int			load_weapon(t_doom *doom)
{
	if (!(load_foot(doom->txt)))
		return (0);
	if (!(load_pistol(doom->txt)))
		return (0);
	if (!(load_shotgun(doom->txt)))
		return (0);
	if (!(load_ripper(doom->txt)))
		return (0);
	return (1);
}
