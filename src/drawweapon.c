/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawweapon.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glormell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 18:08:49 by glormell          #+#    #+#             */
/*   Updated: 2019/10/15 19:09:41 by glormell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void		drawweapon(t_doom *doom, t_weapon *weapon)
{
	int		y;
	int		x;
	t_xy	scale;
	t_xy	t;
	t_img	img;

	img = weapon_get_image(doom, weapon);
	x = -1;
	while (++x < WIDTH)
	{
		scale.x = (float)img.w / (WIDTH);
		scale.y = (float)img.h / (HEIGHT);
		t.y = 0;
		t.x = x * scale.x;
		y = -1;
		while (++y < HEIGHT)
		{
			if (doom->visible[y][x] == 1)
				doom->sdl->pix[y * WIDTH + x] =
					img.data[(int)t.y * img.w + (int)t.x];
			t.y += scale.y;
		}
	}
}
