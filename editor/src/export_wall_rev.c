/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_wall_rev.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 15:39:00 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/29 05:18:37 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

static int	id_text(t_doom *doom, int j)
{
	int		i;

	i = -1;
	while (++i < COUNT_T)
		if (doom->exp->wall[i] == doom->walls->wall[j].txt)
			return (i);
	return (0);
}

static void	out_text_wall(t_doom *doom, int ind, int j, int count)
{
	int		i;
	int		x;

	i = -1;
	x = -1;
	ft_putstr_fd("\t\t", doom->file->fd);
	ft_putnbr_fd(id_text(doom, j), doom->file->fd);
	while (++i < doom->walls->count)
		if (doom->walls->wall[i].sectors == ind && i != j)
			break ;
	while (++x < doom->walls->count && count > 0)
	{
		if ((doom->walls->wall[x].sectors == ind && i != j) &&
		(doom->walls->wall[i].vert_one == doom->walls->wall[x].vert_two))
		{
			ft_putstr_fd(" ", doom->file->fd);
			ft_putnbr_fd(id_text(doom, i), doom->file->fd);
			i = x;
			x = -1;
			count--;
		}
	}
}

static void	output_neigh(t_doom *doom, int ind, int j, int count)
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
		(doom->walls->wall[i].vert_one == doom->walls->wall[x].vert_two))
		{
			ft_putstr_fd(" ", doom->file->fd);
			ft_putnbr_fd(doom->walls->wall[i].portal, doom->file->fd);
			i = x;
			x = -1;
			count--;
		}
	}
	out_text_wall(doom, ind, j, count_wall(doom, ind) - 1);
}

void		output_wall_rev(t_doom *doom, int count, int ind)
{
	int		i;
	int		j;

	i = 0;
	j = -1;
	while (doom->walls->wall[i].sectors != ind && i < doom->walls->count)
		i++;
	doom->exp->order[doom->exp->count++] = i;
	ft_putnbr_fd(sorted_vert(doom, doom->walls->wall[i].vert_two),
													doom->file->fd);
	while (++j < doom->walls->count && count > 1)
	{
		if (doom->walls->wall[j].sectors == ind &&
		doom->walls->wall[i].vert_one == doom->walls->wall[j].vert_two)
		{
			ft_putstr_fd(" ", doom->file->fd);
			ft_putnbr_fd(sorted_vert(doom, doom->walls->wall[j].vert_two),
														doom->file->fd);
			doom->exp->order[doom->exp->count++] = j;
			i = j;
			j = -1;
			count--;
		}
	}
	output_neigh(doom, ind, i, count_wall(doom, ind) - 1);
}
