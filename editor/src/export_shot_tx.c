/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_shot_tx.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 16:39:23 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/28 16:45:26 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

void		output_text_shot(t_doom *doom)
{
	int		i;
	int		*pix;

	i = -1;
	ft_putnbr_fd(doom->txt->shot->w, doom->file->fd);
	ft_putstr_fd(" ", doom->file->fd);
	ft_putnbr_fd(doom->txt->shot->h, doom->file->fd);
	pix = doom->txt->shot->pixels;
	while (++i < doom->txt->shot->w * doom->txt->shot->h)
	{
		ft_putstr_fd(" ", doom->file->fd);
		ft_putnbr_fd(pix[i], doom->file->fd);
	}
	ft_putstr_fd("\n", doom->file->fd);
}

void		export_shot_tx(t_doom *doom)
{
	ft_putstr_fd("B\t\t1\n", doom->file->fd);
	output_text_shot(doom);
	ft_putstr_fd("#\n\n", doom->file->fd);
}
