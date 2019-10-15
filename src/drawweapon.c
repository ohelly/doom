/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawweapon.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glormell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 18:08:49 by glormell          #+#    #+#             */
/*   Updated: 2019/10/15 18:37:32 by glormell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void		drawweapon(t_doom *doom, t_weapon *weapon)
{
	int		y;
	int		x;
	t_xy 	scale;
	t_xy	t;
	t_img	set;

	set = weapon_get_image(doom, weapon);
	x = 0;
	while (x < WIDTH)
	{
		scale.x = (float)set.w / (WIDTH);
		scale.y = (float)set.h / (HEIGHT);
		t.y
		t.x
		//t.y = player.yaw * 25;
		//t.x = (x * scale.x) + player.angle * 50;
		/*if (t.x >= set.w)
		{
			while (t.x >= set.w)
				t.x -= set.w;
		}
		else if (t.x < 0)
		{
			while (t.x < 0)
				t.x += set.w;
		}*/
		y = 0;
		while (y < HEIGHT)
		{
			/*if (t.y > set.h)
				t.y = set.h - t.y;
			else if (t.y < 0)
				t.y = set.h + t.y;*/
			if (doom->visible[y][x] == 1)
				doom->sdl->pix[y * WIDTH + x] = set.data[(int)t.y * set.w + (int)t.x];
			t.y += scale.y;
			y++;
		}
		x++;
	}
	return (0);
}
