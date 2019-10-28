/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_stobj_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 17:54:41 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/28 19:59:53 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

void		out_st_obj_p2(int c, int ind, t_doom *doom)
{
	if (ind == 9)
		ft_putstr_fd("\t\t23\t\t1\t\t1\n", doom->file->fd);
	else if (ind == 10)
		ft_putstr_fd("\t\t20\t\t1\t\t1\n", doom->file->fd);
	else if (ind == 11)
		ft_putstr_fd("\t\t22\t\t1\t\t1\n", doom->file->fd);
	else if (ind == 12)
		ft_putstr_fd("\t\t21\t\t1\t\t1\n", doom->file->fd);
	else if (ind == 13)
		ft_putstr_fd("\t\t2\t\t2\t\t1 2\n", doom->file->fd);
	else if (ind == 14)
		ft_putstr_fd("\t\t1\t\t2\t\t1 1\n", doom->file->fd);
	else if (ind == 15)
		ft_putstr_fd("\t\t10\t\t11\t\t1 1 1 1 1 1 1 1 1 1 4\n",
													doom->file->fd);
}

void		out_st_obj(int c, int ind, t_doom *doom)
{
	ft_putstr_fd(".\n", doom->file->fd);
	ft_putnbr_fd(c, doom->file->fd);
	if (ind == 0 || ind == 1 || ind == 7)
		ft_putstr_fd("\t\t0\t\t1\t\t1\n", doom->file->fd);
	else if (ind == 2)
		ft_putstr_fd("\t\t24\t\t1\t\t1\n", doom->file->fd);
	else if (ind == 3)
		ft_putstr_fd("\t\t25\t\t1\t\t1\n", doom->file->fd);
	else if (ind == 4)
		ft_putstr_fd("\t\t26\t\t1\t\t1\n", doom->file->fd);
	else if (ind == 5)
		ft_putstr_fd("\t\t27\t\t1\t\t1\n", doom->file->fd);
	else if (ind == 6)
		ft_putstr_fd("\t\t28\t\t1\t\t1\n", doom->file->fd);
	else if (ind == 8)
		ft_putstr_fd("\t\t29\t\t1\t\t1\n", doom->file->fd);
	else
		out_st_obj_p2(c, ind, doom);
	output_text_stobj(ind, doom);
}

int			count_stobj(t_doom *doom, t_export *exp)
{
	int		count;
	int		i;
	int		j;
	int		x;

	count = 0;
	i = -1;
	j = -1;
	x = -1;
	while (++j < COUNT_OP)
	{
		i = -1;
		while (++i < doom->obj->count)
		{
			if (doom->obj->obj[i].txt == j)
			{
				count++;
				exp->stobj[++x] = j;
				i = -1;
				break ;
			}
		}
	}
	return (count);
}

void		export_stobj_data(t_doom *doom)
{
	int		count;
	int		i;

	i = -1;
	ft_putstr_fd("obj_data\n", doom->file->fd);
	count = count_stobj(doom, doom->exp);
	if (count == 0)
	{
		ft_putstr_fd("0\n#\n\n", doom->file->fd);
		return ;
	}
	ft_putnbr_fd(count, doom->file->fd);
	ft_putstr_fd("\n\n", doom->file->fd);
	while (++i < count)
		out_st_obj(i, doom->exp->stobj[i], doom);
	ft_putstr_fd("#\n\n", doom->file->fd);
}
