/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 14:03:00 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/23 18:15:56 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

char	*ft_strjoinc(char const *s1, char const *s2)
{
	char	*join;

	if (!s1 || !s2 || !(join = ft_strnew(ft_strlen(s1) + ft_strlen(s2))))
		return (0);
	ft_strcpy(join, s1);
	ft_strcat(join, s2);
	free((void*)s1);
	return (join);
}

int		vertex_copy(t_vertex *source, t_vertex *dest)
{
	dest->pos = source->pos;
	dest->num = source->num;
	return (1);
}

int		sort_vertecies_x(t_doom *doom)
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
	return (1);
}

int		sort_vertecies_y(t_doom *doom)
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
	return (1);
}

int		save_vertecies(t_doom *doom, char **str, t_vertex *ver)
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
			*str = ft_strjoinc(*str, " ");
			*str = ft_strjoinfree(*str, ft_itoa(v.pos.x));
		}
		else
		{
			prev_y = v.pos.y;
			if (i > 0)
				*str = ft_strjoinc(*str, "\n");
			*str = ft_strjoinc(*str, "Vertex\t");
			*str = ft_strjoinfree(*str, ft_itoa(v.pos.y));
			*str = ft_strjoinc(*str, "\t\t");
			*str = ft_strjoinfree(*str, ft_itoa(v.pos.x));
		}
		ver[i].pos.y = v.pos.y;
		ver[i].pos.x = v.pos.x;
	}
}

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

int		save_vert_indexes(t_doom *doom)
{
	int i;

	i = 0;
	while (i < doom->verts->count)
	{
		doom->verts->list[i].num = i;
		i++;
	}
	return (1);
}

int		save_sectors(t_doom *doom, char **str)
{
	int		sector;
	int		i;
	t_wall	walls[512];
	int		walls_total;

	sector = 0;
	while (sector < doom->sects->count)
	{
		*str = ft_strjoinc(*str, "Sector\t");
		*str = ft_strjoinc(*str, "0\t\t20\t\t");
		i = 0;
		walls_total = 0;
		while (i < doom->walls->count)
		{
			if (doom->walls->wall[i].sectors == sector)
			{
				*str = ft_strjoinfree(*str, ft_itoa(sorted_vert(doom, doom->walls->wall[i].vert_one)));
				if (walls_total + 1 < doom->walls->count)
					*str = ft_strjoinc(*str, " ");
				walls[walls_total] = doom->walls->wall[i];
				walls_total++;
			}
			i++;
		}
		*str = ft_strjoinc(*str, "\t\t");
		i = 0;
		while (i < walls_total)
		{
			if (i != 0)
				*str = ft_strjoinc(*str, " ");
			*str = ft_strjoinfree(*str, ft_itoa(walls[i].portal));
			i++;
		}
		*str = ft_strjoinc(*str, "\n");
		sector++;
	}
}

int		save(t_doom *doom)
{
	int			fd;
	char		*str;
	t_vertex	ver[doom->verts->count];

	if (open(doom->file->file_name, O_RDONLY))
		remove(doom->file->file_name);
	doom->file->fd = open(doom->file->file_name, O_WRONLY | O_CREAT, 444);
	vertices_return_map_pos(doom);
	str = ft_strnew(0);
	save_vert_indexes(doom);
	sort_vertecies_y(doom);
	sort_vertecies_x(doom);
	save_vertecies(doom, &str, ver);
	printf("saved vertecies	\n");
	str = ft_strjoinc(str, "\n\n");
	save_sectors(doom, &str);
	printf("saved sectors	\n");
	
	str = ft_strjoinc(str, "\0");
	write(doom->file->fd, str, ft_strlen(str) * sizeof(char));
	close(doom->file->fd);
	doom->hud->msg = "Saved file!";
	exit(0);
}
