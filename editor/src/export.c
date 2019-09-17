#include "doom.h"

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

int		save(t_doom *doom)
{
	int			fd;
	char		*str;
	int			i;
	t_vertex	v;
	int			prev_y;

	if (open(doom->save_name, O_RDONLY))
		remove(doom->save_name);
	fd = open(doom->save_name, O_WRONLY | O_CREAT, 444);

	vertices_return_map_pos(doom);

	i = 0;
	prev_y = 0;
	str = ft_strnew(0);
	sort_vertecies_y(doom);
	sort_vertecies_x(doom);
	while (i < doom->verts->count)
	{
		v = doom->verts->list[i];
		if (prev_y == v.pos.y)
		{
			str = ft_strjoinc(str, " ");
			str = ft_strjoinfree(str, ft_itoa(v.pos.x));
		}
		else
		{
			prev_y = v.pos.y;
			if (i > 0)
				str = ft_strjoinc(str, "\n");
			str = ft_strjoinc(str, "vertex\t");
			str = ft_strjoinfree(str, ft_itoa(v.pos.y));
			str = ft_strjoinc(str, "\t");
			str = ft_strjoinfree(str, ft_itoa(v.pos.x));
		}
		i++;
	}
	str = ft_strjoinc(str, "\n");
	str = ft_strjoinc(str, "\0");
	write(fd, str, ft_strlen(str) * sizeof(char));
	close(fd);
	ft_putendl("Saved file!");
	exit(0);
}