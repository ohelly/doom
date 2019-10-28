/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_vert.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 20:09:42 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/25 20:18:17 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

void	save_vertecies(t_doom *doom)
{
	int			prev_y;
	int			i;
	t_vertex	v;

	i = -1;
	while (++i < doom->verts->count)
	{
		v = doom->verts->list[i];
		if (prev_y == v.pos.y)
		{
			ft_putstr_fd(" ", doom->file->fd);
			ft_putnbr_fd(v.pos.x, doom->file->fd);
		}
		else
		{
			prev_y = v.pos.y;
			if (i > 0)
				ft_putstr_fd("\n", doom->file->fd);
			ft_putstr_fd("Vertex\t", doom->file->fd);
			ft_putnbr_fd(v.pos.y, doom->file->fd);
			ft_putstr_fd("\t\t", doom->file->fd);
			ft_putnbr_fd(v.pos.x, doom->file->fd);
		}
	}
}

void	sort_vertecies_x(t_doom *doom)
{
	t_vertex	v1;
	t_vertex	v2;
	int			select;
	int			index;

	select = -1;
	while (++select < doom->verts->count - 1)
	{
		v1 = doom->verts->list[select];
		index = select;
		while (++index < doom->verts->count)
		{
			v2 = doom->verts->list[index];
			if (v1.pos.y == v2.pos.y && v1.pos.x > v2.pos.x)
			{
				doom->verts->list[select] = v2;
				doom->verts->list[index] = v1;
				v1 = v2;
			}
		}
	}
}

void	sort_vertecies_y(t_doom *doom)
{
	t_vertex	v1;
	t_vertex	v2;
	int			select;
	int			index;

	select = -1;
	while (++select < doom->verts->count - 1)
	{
		v1 = doom->verts->list[select];
		index = select;
		while (++index < doom->verts->count)
		{
			v2 = doom->verts->list[index];
			if (v1.pos.y > v2.pos.y)
			{
				doom->verts->list[select] = v2;
				doom->verts->list[index] = v1;
				v1 = v2;
			}
		}
	}
}

void	save_vert_indexes(t_doom *doom)
{
	int i;

	i = 0;
	while (i < doom->verts->count)
	{
		doom->verts->list[i].num = i;
		i++;
	}
}

void	export_vert(t_doom *doom)
{
	vertices_return_map_pos(doom);
	save_vert_indexes(doom);
	sort_vertecies_y(doom);
	sort_vertecies_x(doom);
	save_vertecies(doom);
}
