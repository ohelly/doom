/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_floor_tx.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 18:02:47 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/27 18:21:13 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

static void	out_pix_text(int i, t_txt *txt, t_doom *doom)
{
	int		j;
	int		*pix;

	j = -1;
	ft_putnbr_fd(txt->swall[i]->w, doom->file->fd);
	ft_putstr_fd(" ", doom->file->fd);
	ft_putnbr_fd(txt->swall[i]->h, doom->file->fd);
	pix = txt->swall[i]->pixels;
	while (++j < txt->swall[i]->w * txt->swall[i]->h)
	{
		ft_putstr_fd(" ", doom->file->fd);
		ft_putnbr_fd(pix[j], doom->file->fd);
	}
	ft_putstr_fd("\n", doom->file->fd);
}

void		output_text_floor(t_doom *doom, int count)
{
	int		i;

	i = -1;
	while (++i < count)
		out_pix_text(doom->exp->floor[i], doom->txt, doom);
}

int			count_t_floor(t_doom *doom, t_export *exp)
{
	int		count;
	int		i;
	int		j;
	int		x;

	count = 0;
	i = -1;
	j = -1;
	x = -1;
	while (++j < COUNT_T)
	{
		i = -1;
		while (++i < doom->sects->count)
		{
			if (doom->sects->sectors[i].txtf == j)
			{
				count++;
				exp->floor[++x] = j;
				i = -1;
				break ;
			}
		}
	}
	return (count);
}

void		export_floor_tx(t_doom *doom)
{
	int		count;

	ft_putstr_fd("F\t\t", doom->file->fd);
	count = count_t_floor(doom, doom->exp);
	ft_putnbr_fd(count, doom->file->fd);
	ft_putstr_fd("\n", doom->file->fd);
	output_text_floor(doom, count);
	ft_putstr_fd("\n", doom->file->fd);
}
