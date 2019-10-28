/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_sky_tx.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 16:31:13 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/28 16:42:45 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

void		output_text_sky(t_doom *doom)
{
	int		i;
	int		*pix;

	i = -1;
	ft_putnbr_fd(doom->txt->ssky[doom->txt->ind_sky]->w, doom->file->fd);
	ft_putstr_fd(" ", doom->file->fd);
	ft_putnbr_fd(doom->txt->ssky[doom->txt->ind_sky]->h, doom->file->fd);
	pix = doom->txt->ssky[doom->txt->ind_sky]->pixels;
	while (++i < doom->txt->ssky[doom->txt->ind_sky]->w *
									doom->txt->ssky[doom->txt->ind_sky]->h)
	{
		ft_putstr_fd(" ", doom->file->fd);
		ft_putnbr_fd(pix[i], doom->file->fd);
	}
	ft_putstr_fd("\n", doom->file->fd);
}

void		export_sky_tx(t_doom *doom)
{
	ft_putstr_fd("S\t\t1\n", doom->file->fd);
	output_text_sky(doom);
	ft_putstr_fd("\n", doom->file->fd);
}
