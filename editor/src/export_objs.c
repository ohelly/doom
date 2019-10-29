/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_objs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 22:33:40 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/28 22:46:49 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

int			id_text_obj(t_doom *doom, int i)
{
	int		j;

	j = -1;
	while (++j < COUNT_STOBJ)
		if (doom->obj->obj[i].txt == doom->exp->stobj[j])
			return (j);
	return (0);
}

void		export_objs(t_doom *doom)
{
	int		i;

	i = -1;
	while (++i < doom->obj->count)
	{
		ft_putstr_fd("Objs\t", doom->file->fd);
		ft_putnbr_fd(id_text_obj(doom, i), doom->file->fd);
		ft_putstr_fd("\t\t", doom->file->fd);
		ft_putnbr_fd(doom->obj->obj[i].pos.y, doom->file->fd);
		ft_putstr_fd(" ", doom->file->fd);
		ft_putnbr_fd(doom->obj->obj[i].pos.x, doom->file->fd);
		ft_putstr_fd("\t\t", doom->file->fd);
		ft_putnbr_fd(doom->obj->obj[i].sector, doom->file->fd);
		ft_putstr_fd("\n", doom->file->fd);
	}
	ft_putstr_fd("\n", doom->file->fd);
}
