#include "doom.h"

int		split_wall(t_doom *doom)
{
	int		i;
	int		w1;
	int		w2;
	t_v2	pos;

	if (doom->verts->projected_v.num == -1 || doom->app != 0)
		return (-1);

	w1 = doom->verts->projected_v.num;
	w2 = get_duplicate_wall(doom, doom->walls->wall[w1]);
	if (doom->walls->wall[w1].portal != -1 || (w2 != -1 && doom->walls->wall[w2].portal != -1))
	{
		printf("Error adding new vertex: remove portal first!\n");
		return (-1);
	}
	pos = doom->verts->projected_v.pos;
	//добавляем новую вершину на позицию
	i = doom->verts->count;
	doom->verts->list[i].pos = pos;
	doom->verts->count++;
	//разбиваем первую стену на две
	doom->walls->wall[doom->walls->count].vert_one = doom->verts->count - 1;
	doom->walls->wall[doom->walls->count].vert_two = doom->walls->wall[w1].vert_two;
	doom->walls->wall[doom->walls->count].sectors = doom->walls->wall[w1].sectors;
	doom->walls->wall[doom->walls->count].portal = -1;
	doom->walls->count++;
	doom->walls->wall[w1].vert_two = doom->verts->count - 1;
	//разбиваем вторую стену на две
	if (w2 != -1)
	{
		doom->walls->wall[doom->walls->count].vert_one = doom->verts->count - 1;
		doom->walls->wall[doom->walls->count].vert_two = doom->walls->wall[w2].vert_two;
		doom->walls->wall[doom->walls->count].sectors = doom->walls->wall[w2].sectors;
		doom->walls->wall[doom->walls->count].portal = -1;
		doom->walls->wall[w2].vert_two = doom->verts->count - 1;
		doom->walls->count++;
	}

	doom->verts->projected_v.num = -1;
	return (1);
}