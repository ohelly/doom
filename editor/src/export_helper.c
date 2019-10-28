/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 20:13:43 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/28 17:26:17 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

/*
** Выводит пиксели из сурфейса в файл
*/

void	out_img_weapon(SDL_Surface *sur, t_file *file)
{
	int		i;
	int		*pix;

	i = -1;
	pix = sur->pixels;
	ft_putnbr_fd(sur->w, file->fd);
	ft_putstr_fd(" ", file->fd);
	ft_putnbr_fd(sur->h, file->fd);
	while (++i < sur->w * sur->h)
	{
		ft_putstr_fd(" ", file->fd);
		ft_putnbr_fd(pix[i], file->fd);
	}
	ft_putstr_fd("\n", file->fd);
}

/*
** Определяет в какую сторону нарисован сектор при экспорте.
** От этого зависит порядок экспорта стен.
*/

int		check_rotation(t_doom *doom, int ind, t_vertex *list)
{
	int		j;
	int		i;

	j = -1;
	i = -1;
	while (++j < doom->walls->count)
		if (doom->walls->wall[j].sectors == ind)
			break ;
	while (++i < doom->walls->count)
		if (doom->walls->wall[i].sectors == ind && i != j &&
		sorted_vert(doom, doom->walls->wall[j].vert_two) ==
		sorted_vert(doom, doom->walls->wall[i].vert_one))
			break ;
	return (scalar_product(list[sorted_vert(doom,
	doom->walls->wall[j].vert_one)].pos,
	list[sorted_vert(doom, doom->walls->wall[j].vert_two)].pos,
	list[sorted_vert(doom, doom->walls->wall[i].vert_two)].pos));
}

/*
** Возвращает количество стен данного сектора
*/

int		count_wall(t_doom *doom, int ind)
{
	int		i;
	int		count;

	i = -1;
	count = 0;
	while (++i < doom->walls->count)
		if (doom->walls->wall[i].sectors == ind)
			count++;
	return (count);
}

/*
** Возвращает номер верщины в сортированном порядке
*/

int		sorted_vert(t_doom *doom, int index)
{
	int i;

	i = 0;
	while (i < doom->verts->count)
	{
		if (doom->verts->list[i].num == index)
			return (i);
		i++;
	}
	return (-1);
}
