#include "doom_editor.h"

float	calc_dist(t_doom *doom, int vert1, int vert2, t_v2 *hit)
{
	t_v2 p1;
	t_v2 p2;
	t_v2 m;

	p1 = doom->verts->list[vert1].pos;
	p2 = doom->verts->list[vert2].pos;
	m = doom->mouse->pos;
	return (line_distance(p1, p2, m, hit));
}

void	get_closest_sector(t_doom *doom)
{
	int wall;
	int i;

	if (doom->sects->selected_sector != -1)
	{
		doom->sects->selected_sector = -1;
		return ;
	}
	if (doom->walls->selected_wall != -1)
		doom->walls->selected_wall = -1;
	wall = get_closest_wall(doom);
	if (wall == -1)
	{
		doom->sects->selected_sector = -1;
		return ;
	}
	printf("Selected sector %d\n", doom->walls->wall[wall].sectors);
	doom->sects->selected_sector = doom->walls->wall[wall].sectors;
}

int		get_closest_wall(t_doom *doom)
{
	int		i;
	float	dist;
	int		saved_wall;
	float	saved_dist;
	t_v2	curr_vertices;	//current wall vertices index
	t_v2	hit;
	t_v2	saved_hit;
	
	i = 0;
	saved_wall = -1;
	saved_dist = 1000;
	while (i < doom->walls->count)
	{
		curr_vertices.x = doom->walls->wall[i].vert_one;
		curr_vertices.y = doom->walls->wall[i].vert_two;
		dist = calc_dist(doom, curr_vertices.x, curr_vertices.y, &hit);
		if (dist < saved_dist)
		{
			saved_wall = i;
			saved_dist = dist;
			saved_hit = hit;
		}
		i++;
	}
	//if (saved_dist < 30)
	//{
		doom->verts->projected_v.num = saved_wall;
		doom->verts->projected_v.pos = saved_hit;
		return (saved_wall);
	//}
	//return (-1);
}