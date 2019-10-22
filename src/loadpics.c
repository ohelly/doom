/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadpics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 13:47:25 by dtoy              #+#    #+#             */
/*   Updated: 2019/10/21 16:37:27 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		findvx(t_xy *v1, t_xy *v2, t_xy *vert, int wall)
{
	v1->x = vert[wall].x;
	v1->y = vert[wall].y;
	v2->x = vert[wall + 1].x;
	v2->y = vert[wall + 1].y;
	return (0);
}

int		findpicpoints(t_doom *doom, t_pics *pic, int w)
{
	t_xy	d1;
	t_xy	d2;
	t_xy	v1;
	t_xy	v2;
	float	dist1;
	float	dist2;

	findvx(&v1, &v2, doom->sectors[pic->sector].vert, pic->wall);
	d1.x = v1.x - pic->p.x;
	d1.y = v1.y - pic->p.y;
	d2.x = pic->p.x - v2.x;
	d2.y = pic->p.y - v2.y;
	
	dist1 = sqrtf(powf(d1.x, 2) + powf(d1.y, 2));
	dist2 = sqrtf(powf(d2.x, 2) + powf(d2.y, 2));
	//printf("dist1 - %f, dist2 - %f\n", dist1, dist2);
	pic->p1.x = pic->p.x - ((w * (pic->p.x - v1.x)) / dist1);
	pic->p1.y = pic->p.y - ((w * (pic->p.y - v1.y)) / dist1);
	pic->p2.x = pic->p.x - ((w * (pic->p.x - v2.x)) / dist2);
	pic->p2.y = pic->p.y - ((w * (pic->p.y - v2.y)) / dist2);
	//printf("p1.y - %f, p1.x - %f\n", pic->p1.y, pic->p1.x);
	//printf("p2.y - %f, p2.x - %f\n", pic->p2.y, pic->p2.x);

	return (0);
}

int		loadpics(t_doom *doom, t_pics *pic, t_data *pics_data, char *str)
{
	static int	n = 0;
	float	tmp;
	int		id;
	
	str = todigit(str, &tmp);
	id = (int)tmp;
	str = todigit(str, &pic[n].p.y);
	str = todigit(str, &pic[n].p.x);
	str = todigit(str, &pic[n].p.z);
	//printf("pic y - %f, pic x - %f, pic z - %f\n", pic[n].p.y, pic[n].p.x, pic[n].p.z);
	str = todigit(str, &tmp);
	pic[n].wall = (int)tmp;
	//printf("wall - %d\n", pic[n].wall);
	str = todigit(str, &tmp);
	pic[n].sector = (int)tmp;
	pic[n].type = pics_data[id].type;
	pic[n].images = pics_data[id].images;
	pic[n].anim_count = pics_data[id].anim_count;
	pic[n].states_count = pics_data[id].states_count;
	findpicpoints(doom, &pic[n], doom->img[pic[n].images[0][0]].w / 40);
	//printf("sector - %d\n", pic[n].sector);
	n++;
	return (0);
}