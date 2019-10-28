/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_attr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 22:23:13 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/28 22:31:11 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

int			id_text_ceil(t_doom *doom, int ind)
{
	int		i;

	i = -1;
	while (++i < COUNT_T)
		if (doom->exp->ceil[i] == doom->sects->sectors[ind].txtc)
			return (i);
	return (0);
}

int			id_text_floor(t_doom *doom, int ind)
{
	int		i;

	i = -1;
	while (++i < COUNT_T)
		if (doom->exp->floor[i] == doom->sects->sectors[ind].txtf)
			return (i);
	return (0);
}

void		export_attr(t_doom *doom, int ind)
{
	ft_putstr_fd("\t\t", doom->file->fd);
	ft_putnbr_fd(id_text_floor(doom, ind), doom->file->fd);
	ft_putstr_fd("\t\t", doom->file->fd);
	ft_putnbr_fd(id_text_ceil(doom, ind), doom->file->fd);
	ft_putstr_fd("\t\t", doom->file->fd);
	ft_putnbr_fd(doom->sects->sectors[ind].light, doom->file->fd);
	ft_putstr_fd("\t\t", doom->file->fd);
	ft_putnbr_fd(doom->sects->sectors[ind].door, doom->file->fd);
	ft_putstr_fd("\t\t", doom->file->fd);
	ft_putnbr_fd(doom->sects->sectors[ind].skyb, doom->file->fd);
}
