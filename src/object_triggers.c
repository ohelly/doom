#include "doom.h"

void	on_collision_key(t_doom *doom, t_obj *obj)
{
	if (obj->enabled == 0)
		return ;
	obj->enabled = 0;
	printf("obj %d has been triggered\n", obj->id);
}

int	check_player_collision(t_doom *doom, t_obj *obj)
{
	t_xy pl;
	t_xy pos;

	pl = (t_xy){doom->player.where.x, doom->player.where.y};
	pos = obj->p;

	//if (intersects_collider(pl1, pl2, obj1, obj2))
	if (collision_circle(pl, doom->player.col_size, pos, obj->col_size))
		return (1);
	return (0);
}

int	objects_update(t_doom *doom)
{
	int		i;
	t_obj	*o;

	i = 0;
	while (i < doom->numobjs)
	{
		o = &doom->obj[i];
		if (o->enabled)
		{
			if (o->on_collision != NULL)
				if (check_player_collision(doom, o))
					o->on_collision(doom, o);
		}
		i++;
	}
}