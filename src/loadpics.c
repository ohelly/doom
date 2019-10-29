/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadpics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 13:47:25 by dtoy              #+#    #+#             */
/*   Updated: 2019/10/29 05:34:21 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_img	pic_get_image(t_doom *doom, t_pics *pic)
{
	return (doom->img[pic->images[pic->states_frame][pic->anim_frame]]);
}

void	pic_anim_next(t_pics *pic)
{
	pic->anim_frame++;
	if (pic->anim_frame >= pic->anim_count[pic->states_frame] ||
		pic->images[pic->states_frame][pic->anim_frame] == -1)
		pic->anim_frame = 0;
}

int		findvx(t_xy *v1, t_xy *v2, t_xy *vert, int wall)
{
	v1->x = vert[wall].x;
	v1->y = vert[wall].y;
	v2->x = vert[wall + 1].x;
	v2->y = vert[wall + 1].y;
	return (0);
}

int		findpicpoints(t_doom *doom, t_pics *pic, float w)
{
	t_xy	d1;
	t_xy	d2;
	t_xy	v1;
	t_xy	v2;
	t_xy	dist;

	findvx(&v1, &v2, doom->sectors[pic->sector].vert, pic->wall);
	d1.x = v1.x - pic->p.x;
	d1.y = v1.y - pic->p.y;
	d2.x = pic->p.x - v2.x;
	d2.y = pic->p.y - v2.y;
	dist.x = sqrtf(powf(d1.x, 2) + powf(d1.y, 2));
	dist.y = sqrtf(powf(d2.x, 2) + powf(d2.y, 2));
	pic->p1.x = pic->p.x - ((w * (pic->p.x - v1.x)) / dist.x);
	pic->p1.y = pic->p.y - ((w * (pic->p.y - v1.y)) / dist.x);
	pic->p2.x = pic->p.x - ((w * (pic->p.x - v2.x)) / dist.y);
	pic->p2.y = pic->p.y - ((w * (pic->p.y - v2.y)) / dist.y);
	return (0);
}

int		loadpics(t_doom *doom, t_pics *pic, t_data *pics_data, char *str)
{
	static int	n = 0;
	float		tmp;
	int			id;

	str = todigit(str, &tmp);
	id = (int)tmp;
	str = todigit(str, &tmp);
	pic[n].p.y = tmp / 4.f;
	str = todigit(str, &tmp);
	pic[n].p.x = tmp / 4.f;
	str = todigit(str, &pic[n].p.z);
	str = todigit(str, &tmp);
	pic[n].wall = (int)tmp;
	str = todigit(str, &tmp);
	pic[n].sector = (int)tmp;
	int		i;

	i = 0;
	while (i < pic[n].sector)
	{
		pic[n].wall -= doom->sectors[i].npoints;
		i++;
	}
	pic[n].wall++;
	printf("wall - %d\n", pic[n].wall);
	pic[n].type = pics_data[id].type;
	pic[n].images = pics_data[id].images;
	pic[n].anim_count = pics_data[id].anim_count;
	pic[n].states_count = pics_data[id].states_count;
	findpicpoints(doom, &pic[n],
	(float)(doom->img[pic[n].images[0][0]].w) / (64.f));
	n++;
	return (0);
}
