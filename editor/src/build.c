#include "doom_editor.h"

/*
**	Проверяет, не лежит ли в позиции v какая-либо вершина
**	Возвращает номер вершины, если координаты v и вершины совпадают
**	Возвращает -1 в других случаях
*/
int		vertex_is_free(t_doom *doom, t_v2 v)
{
	int		i;
	t_v2	v2;

	i = 0;
	while (i < doom->verts->count)
	{
		v2 = doom->verts->list[i].pos;
		if (v2_compare(v, v2))
			return (i);
		i++;
	}
	return (-1);
}

/*
**	Создает сектор по точкам из built_v_index,
**	назначает стенам внутри сектора номер сектора.
**	Возвращает номер сектора, если удалось построить сектор
**	Возвращает -1 в других ситуациях
*/

int		create_sector(t_doom *doom)
{
	int i;
	int	w_index;

	if (doom->verts->built_v_count <= 2)
		return (-1);
	i = 0;
	while (i < doom->verts->built_v_count)
	{
		w_index = (doom->walls->count - 1) - (doom->verts->built_v_count - 2 - i);
		doom->walls->wall[w_index].sectors = doom->sects->count;
		i++;
	}
	doom->sects->count++;
	return (doom->sects->count - 1);
}

/*
**	Строит стену между предпоследней и последней точкой в built_v_index
**	Не назначает стенам номер сектора
*/

int		put_wall(t_doom *doom)
{
	int		v1_index;
	int		v2_index;
	t_wall	w;

	v1_index = doom->verts->built_v_index[doom->verts->built_v_count - 2];
	v2_index = doom->verts->built_v_index[doom->verts->built_v_count - 1];
	doom->walls->wall[doom->walls->count].vert_one = v1_index;
	doom->walls->wall[doom->walls->count].vert_two = v2_index;
	doom->walls->wall[doom->walls->count].sectors = -1;
	doom->walls->wall[doom->walls->count].portal = -1;
	doom->walls->count++;
	return (1);
}

/*
**	Ставит вершину в точке mouse->ppos
**	Добавляет индекс вершины в verts->built_v_index
*/

int		put_vert(t_doom *doom)
{
	int v_index;
	int i;

	v_index = vertex_is_free(doom, doom->mouse->ppos);
	if (v_index == -1)
	{
		v_index = doom->verts->count;
		doom->verts->list[v_index].pos = doom->mouse->ppos;
		doom->verts->built_v_index[doom->verts->built_v_count] = v_index;
		doom->verts->count++;
		doom->verts->built_v_count++;
	}
	else
	{
		i = 1;
		while (i < doom->verts->built_v_count)
		{
			if (doom->verts->built_v_index[i] == v_index)
				return (-1);
			i++;
		}
		doom->verts->built_v_index[doom->verts->built_v_count] = v_index;
		doom->verts->built_v_count++;
		doom->verts->built_v_count_used++;
	}
	return (1);
}

void	build_sector(t_doom *doom)
{
	t_v2	start_v;
	t_v2	curr_v;

	if (doom->app == 1)
	{
		if (lines_intersect_loop(doom,
			doom->verts->list[doom->verts->built_v_index[doom->verts->built_v_count - 1]].pos,
			doom->mouse->ppos))
				return ;
	}
	if (doom->app == 0)
	{
		put_vert(doom);
		doom->app = 1;
	}
	else if (doom->app == 1)
	{
		if (put_vert(doom) == -1)
			return ;
		put_wall(doom);
		start_v = doom->verts->list[doom->verts->built_v_index[0]].pos;
		curr_v = doom->verts->list[doom->verts->built_v_index[doom->verts->built_v_count - 1]].pos;
		if (v2_compare(start_v, curr_v) == 1)
		{
			if (create_sector(doom) != -1)
			{
				doom->app = 0;
				doom->verts->built_v_count = 0;
				doom->verts->built_v_count_used = 0;
			}
		}
	}
}