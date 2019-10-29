/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_pics.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 20:50:37 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/28 21:25:54 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

void		out_vent(t_doom *doom)
{
	out_img_weapon(doom->txt->pics[9], doom->file);
	out_img_weapon(doom->txt->pics[10], doom->file);
	out_img_weapon(doom->txt->pics[11], doom->file);
	out_img_weapon(doom->txt->pics[12], doom->file);
	out_img_weapon(doom->txt->pics[13], doom->file);
}

void		output_text_pics(int ind, t_doom *doom)
{
	if (ind == 0 || ind == 1 || ind == 2)
	{
		out_img_weapon(doom->txt->pics[ind], doom->file);
		out_img_weapon(doom->txt->pics[3], doom->file);
	}
	else if (ind == 3)
	{
		out_img_weapon(doom->txt->pics[4], doom->file);
		out_img_weapon(doom->txt->pics[5], doom->file);
	}
	else if (ind == 4)
	{
		out_img_weapon(doom->txt->pics[6], doom->file);
		out_img_weapon(doom->txt->pics[7], doom->file);
		out_img_weapon(doom->txt->pics[8], doom->file);
		out_img_weapon(doom->txt->pics[3], doom->file);
	}
	else if (ind == 5)
		out_vent(doom);
}

void		out_pics(int c, int ind, t_doom *doom)
{
	ft_putstr_fd(".\n", doom->file->fd);
	ft_putnbr_fd(c, doom->file->fd);
	if (ind == 0 || ind == 1 || ind == 2)
		ft_putstr_fd("\t\t0\t\t2\t\t1 1\n", doom->file->fd);
	else if (ind == 3)
		ft_putstr_fd("\t\t1\t\t2\t\t1 1\n", doom->file->fd);
	else if (ind == 4)
		ft_putstr_fd("\t\t0\t\t2\t\t3 1\n", doom->file->fd);
	else if (ind == 5)
		ft_putstr_fd("\t\t0\t\t2\t\t4 1\n", doom->file->fd);
	output_text_pics(ind, doom);
}

int			count_pics(t_doom *doom, t_export *exp)
{
	int		count;
	int		i;
	int		j;
	int		x;

	count = 0;
	i = -1;
	j = -1;
	x = -1;
	while (++j < COUNT_SP)
	{
		i = -1;
		while (++i < doom->aspr->count)
		{
			if (doom->aspr->spr[i].txt == j)
			{
				count++;
				exp->pics[++x] = j;
				i = -1;
				break ;
			}
		}
	}
	return (count);
}

void		export_pics(t_doom *doom)
{
	int		count;
	int		i;

	i = -1;
	ft_putstr_fd("pic_data\n", doom->file->fd);
	count = count_pics(doom, doom->exp);
	if (count == 0)
	{
		ft_putstr_fd("0\n#\n\n", doom->file->fd);
		return ;
	}
	ft_putnbr_fd(count, doom->file->fd);
	ft_putstr_fd("\n\n", doom->file->fd);
	while (++i < count)
		out_pics(i, doom->exp->pics[i], doom);
	ft_putstr_fd("#\n\n", doom->file->fd);
}
