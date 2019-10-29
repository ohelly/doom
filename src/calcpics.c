/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcpics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 20:18:01 by dtoy              #+#    #+#             */
/*   Updated: 2019/10/29 17:51:31 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int			find_t_pic_points(t_pics *pic, t_player player, t_cood *cood)
{
	cood->v1.x = pic->p1.x - player.where.x;
	cood->v1.y = pic->p1.y - player.where.y;
	cood->v2.x = pic->p2.x - player.where.x;
	cood->v2.y = pic->p2.y - player.where.y;
	cood->t1.x = cood->v1.x * player.psin - cood->v1.y * player.pcos;
	cood->t1.z = cood->v1.x * player.pcos + cood->v1.y * player.psin;
	cood->t2.x = cood->v2.x * player.psin - cood->v2.y * player.pcos;
	cood->t2.z = cood->v2.x * player.pcos + cood->v2.y * player.psin;
	return (0);
}

int			find_pic_points(t_cood *cood, t_pics *pic, t_doom *doom)
{
	t_img	img;
	float	tmp;

	if (cood->num >= doom->num.pics)
		tmp = 70.f;
	else
		tmp = 9.f;
	img = pic_get_image(doom, pic);
	cood->yceil = pic->p.z +
	(float)(img.h) / tmp - doom->player.where.z;
	cood->yfloor = pic->p.z - doom->player.where.z;
	cood->w1y.a = HEIGHT / 2 -
	(int)(yaw(cood->yceil, cood->t1.z, doom->player) * cood->scale1.y);
	cood->w1y.b = HEIGHT / 2 -
	(int)(yaw(cood->yfloor, cood->t1.z, doom->player) * cood->scale1.y);
	cood->w2y.a = HEIGHT / 2 -
	(int)(yaw(cood->yceil, cood->t2.z, doom->player) * cood->scale2.y);
	cood->w2y.b = HEIGHT / 2 -
	(int)(yaw(cood->yfloor, cood->t2.z, doom->player) * cood->scale2.y);
	pic->vis = 1;
	return (0);
}

int			intersect_pics(t_doom *doom, t_pics *pic, t_cood *cood)
{
	if (doom->a == 1)
		pic_anim_next(pic);
	find_t_pic_points(pic, doom->player, cood);
	if (cood->t1.z <= 0 && cood->t2.z <= 0)
		return (0);
	cood->u0 = 0;
	cood->u1 = doom->img[pic->images[pic->states_frame][pic->anim_frame]].w;
	if (cood->t1.z <= 0 || cood->t2.z <= 0)
		intersect(&cood->t1, &cood->t2, cood);
	return (1);
}

int			calc_pics2(t_doom *doom, t_pics *pic, t_cood *cood)
{
	if (!(intersect_pics(doom, pic, cood)))
		return (0);
	if (!(find_scales(cood)))
		return (0);
	find_pic_points(cood, pic, doom);
	return (1);
}

int			calc_pics(t_doom *doom, t_pics *pic)
{
	int		i;
	t_cood	cood;

	i = 0;
	while (i < doom->num.pics + doom->num_shots)
	{
		pic[i].vis = 0;
		if (pic[i].wall == doom->cood.n && pic[i].sector == doom->now.sector)
		{
			cood.num = i;
			if (!(calc_pics2(doom, &pic[i], &cood)))
			{
				i++;
				continue ;
			}
			pic[i].pcood = cood;
		}
		i++;
	}
	return (0);
}
