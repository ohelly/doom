/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_sector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 20:18:47 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/25 20:26:01 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

void	output_neigh(t_doom *doom, int ind, int j, int count)
{
	int		i;
	int		x;

	i = -1;
	x = -1;
	ft_putstr_fd("\t\t", doom->file->fd);
	ft_putnbr_fd(doom->walls->wall[j].portal, doom->file->fd);
	while (++i < doom->walls->count)
		if (doom->walls->wall[i].sectors == ind && i != j)
			break ;
	while (++x < doom->walls->count && count > 0)
	{
		if ((doom->walls->wall[x].sectors == ind && i != j) &&
		(doom->walls->wall[i].vert_two == doom->walls->wall[x].vert_one))
		{
			ft_putstr_fd(" ", doom->file->fd);
			ft_putnbr_fd(doom->walls->wall[i].portal, doom->file->fd);
			i = x;
			x = -1;
			count--;
		}
	}
}

void	output_wall(t_doom *doom, int count, int ind)
{
	int		i;
	int		j;

	i = -1;
	j = -1;
	while (++i < doom->walls->count)
		if (doom->walls->wall[i].sectors == ind)
			break ;
	ft_putnbr_fd(sorted_vert(doom, doom->walls->wall[i].vert_one),
													doom->file->fd);
	while (++j < doom->walls->count && count > 1)
	{
		if (doom->walls->wall[j].sectors == ind &&
		doom->walls->wall[i].vert_two == doom->walls->wall[j].vert_one)
		{
			ft_putstr_fd(" ", doom->file->fd);
			ft_putnbr_fd(sorted_vert(doom, doom->walls->wall[j].vert_one),
														doom->file->fd);
			i = j;
			j = -1;
			count--;
		}
	}
	output_neigh(doom, ind, i, count_wall(doom, ind) - 1);
}

void	save_sectors(t_doom *doom)
{
	int		sector;
	int		i;

	sector = -1;
	while (++sector < doom->sects->count)
	{
		ft_putstr_fd("Sector\t", doom->file->fd);
		ft_putnbr_fd(doom->sects->sectors[sector].floor, doom->file->fd);
		ft_putstr_fd("\t\t", doom->file->fd);
		ft_putnbr_fd(doom->sects->sectors[sector].ceiling, doom->file->fd);
		ft_putstr_fd("\t\t", doom->file->fd);
		output_wall(doom, count_wall(doom, sector), sector);
		ft_putstr_fd("\n", doom->file->fd);
	}
}

void	export_sector(t_doom *doom)
{
	ft_putstr_fd("\n\n", doom->file->fd);
	save_sectors(doom);
}
