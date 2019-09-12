/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_and_mouse_press.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 22:12:24 by ohelly            #+#    #+#             */
/*   Updated: 2019/09/10 20:10:35 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
**	Возвращает 1 если v1 и v2 имеют общие координаты
*/

int			compare_v2(t_v2 v1, t_v2 v2)
{
	if (v1.x == v2.x && v1.y == v2.y)
		return (1);
	return (0);
}

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
		if (compare_v2(v, v2))
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
		doom->verts->built_v_index[doom->verts->built_v_count] = v_index;
		doom->verts->built_v_count++;
	}
	return (1);
}

void	build_sector(t_doom *doom)
{
	t_v2	start_v;
	t_v2	curr_v;

	if (doom->app == 1 &&
		lines_intersect_loop(doom,
		doom->verts->list[doom->verts->built_v_index[doom->verts->built_v_count - 1]].pos,
		doom->mouse->ppos))
	{
		printf("Line intersects with something!!!\n");
		//return ;
	}
	if (doom->app == 0)
	{
		put_vert(doom);
		doom->app = 1;
	}
	else if (doom->app == 1)
	{
		put_vert(doom);
		put_wall(doom);
		start_v = doom->verts->list[doom->verts->built_v_index[0]].pos;
		curr_v = doom->verts->list[doom->verts->built_v_index[doom->verts->built_v_count - 1]].pos;
		if (compare_v2(start_v, curr_v) == 1)
		{
			if (create_sector(doom) != -1)
			{
				doom->app = 0;
				doom->verts->built_v_count = 0;
			}
		}
	}
}

void	kek(t_doom *doom)
{
	int i = -1;
	while (++i < doom->walls->count)
		printf("i = %d  sect = %d  vert1 = %d  vert2 = %d  portal = %d\n", i, doom->walls->wall[i].sectors, doom->walls->wall[i].vert_one, doom->walls->wall[i].vert_two, doom->walls->wall[i].portal);
}

void	key_and_mouse_press(t_doom *doom)
{
	while (SDL_PollEvent(&doom->sdl->ev))
	{
		if (doom->sdl->ev.type == SDL_KEYDOWN)
		{
			if (doom->sdl->ev.key.keysym.sym == '\033')
				exit (0);
			if (doom->sdl->ev.key.keysym.sym == '-')
				doom->sh += 1;
			if (doom->sdl->ev.key.keysym.sym == '=' && doom->sh > 5)
				doom->sh -= 1;
			if (doom->sdl->ev.key.keysym.sym == ' ')
				build_sector(doom);
			if (doom->sdl->ev.key.keysym.sym == 'e')
				save(doom);
			if (doom->sdl->ev.key.keysym.sym == 'w')
				get_closest_wall(doom);
			if (doom->sdl->ev.key.keysym.sym == 's')
				get_closest_sector(doom);
			if (doom->sdl->ev.key.keysym.sym == 'k')
				kek(doom);
		}
		if (doom->sdl->ev.type == SDL_MOUSEMOTION)
			*doom->mouse = (t_mouse){ doom->sdl->ev.motion.x, doom->sdl->ev.motion.y, 0 ,0 };
		output(doom);
	}
}