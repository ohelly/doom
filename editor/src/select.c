#include "doom.h"

float	calc_dist(t_doom *doom, int vert1, int vert2)
{
	t_v2 p1 = doom->verts->list[vert1].pos;
	t_v2 p2 = doom->verts->list[vert2].pos;
	t_v2 m = doom->mouse->pos;
	return (line_distance(p1, p2, m, NULL));
	//printf("point pos %d:%d, mouse pos %d:%d; ", p1.x, p1.y, m.x, m.y);
	//printf("dist to line is %f\n", line_distance(p1, p2, m, NULL));
}

void	get_closest_sector(t_doom *doom)
{
	int wall;
	int i;

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
	
	i = 0;
	saved_wall = -1;
	saved_dist = 1000;
	while (i < doom->walls->count)
	{
		curr_vertices.x = doom->walls->wall[i].vert_one;
		curr_vertices.y = doom->walls->wall[i].vert_two;
		dist = calc_dist(doom, curr_vertices.x, curr_vertices.y);
		if (dist < saved_dist)
		{
			saved_wall = i;
			saved_dist = dist;
		}
		i++;
	}
	if (saved_dist < 30)
	{
		printf("Closest wall is %d, with distance %f. Linked sector %d.\n", saved_wall, saved_dist, doom->walls->wall[saved_wall].sectors);
		return (saved_wall);
	}
	return (-1);
}