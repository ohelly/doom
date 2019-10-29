/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_pospics.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 22:41:26 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/28 22:57:21 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

int			id_wall_pics(t_doom *doom, int i)
{
	int		j;

	j = -1;
	while (++j < doom->walls->count)
		if (doom->exp->order[j] == doom->aspr->spr[i].wall)
			return (j);
	return (0);
}

int			id_text_pics(t_doom *doom, int i)
{
	int		j;

	j = -1;
	while (++j < COUNT_PICS)
		if (doom->aspr->spr[i].txt == doom->exp->pics[j])
			return (j);
	return (0);
}

void		export_pospics(t_doom *doom)
{
	int		i;

	i = -1;
	while (++i < doom->aspr->count)
	{
		ft_putstr_fd("Pics\t", doom->file->fd);
		ft_putnbr_fd(id_text_pics(doom, i), doom->file->fd);
		ft_putstr_fd("\t\t", doom->file->fd);
		ft_putnbr_fd(doom->aspr->spr[i].pos.y, doom->file->fd);
		ft_putstr_fd(" ", doom->file->fd);
		ft_putnbr_fd(doom->aspr->spr[i].pos.x, doom->file->fd);
		ft_putstr_fd("\t\t", doom->file->fd);
		ft_putnbr_fd(doom->aspr->spr[i].z, doom->file->fd);
		ft_putstr_fd("\t\t", doom->file->fd);
		ft_putnbr_fd(id_wall_pics(doom, i), doom->file->fd);
		ft_putstr_fd("\t\t", doom->file->fd);
		ft_putnbr_fd(doom->aspr->spr[i].sector, doom->file->fd);
		ft_putstr_fd("\n", doom->file->fd);
	}
	ft_putstr_fd("\n", doom->file->fd);
}
