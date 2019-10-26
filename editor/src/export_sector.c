/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_sector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 20:18:47 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/26 15:55:51 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

void	save_sectors(t_doom *doom)
{
	int		sector;
	int		i;

	sector = -1;
	i = -1;
	while (++sector < doom->sects->count)
	{
		ft_putstr_fd("Sector\t", doom->file->fd);
		ft_putnbr_fd(doom->sects->sectors[sector].floor, doom->file->fd);
		ft_putstr_fd("\t\t", doom->file->fd);
		ft_putnbr_fd(doom->sects->sectors[sector].ceiling, doom->file->fd);
		ft_putstr_fd("\t\t", doom->file->fd);
		printf("%d\n", check_rotation(doom, sector, doom->verts->list));
		if (!(check_rotation(doom, sector, doom->verts->list)))
			output_wall(doom, count_wall(doom, sector), sector);
		else
			output_wall_rev(doom, count_wall(doom, sector), sector);
		ft_putstr_fd("\n", doom->file->fd);
	}
}

void	export_sector(t_doom *doom)
{
	ft_putstr_fd("\n\n", doom->file->fd);
	save_sectors(doom);
}
