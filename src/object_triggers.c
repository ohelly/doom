#include "doom.h"

void	on_collision_key(t_doom *doom, t_obj *obj)
{
	if (obj->enabled == 0)
		return ;
	obj->enabled = 0;
}

int	check_player_collision(t_doom *doom, t_obj *obj)
{
	t_xy pl1;
	t_xy pl2;
	t_xy obj1;
	t_xy obj2;

	pl1 = (t_xy){doom->player.where.x, doom->player.where.y};
	pl2 = v2_addf(pl1, 3);
	pl1 = v2_addf(pl1, -3);
	obj1 = obj->p;
	obj2 = v2_addf(obj1, obj->col_size);
	obj1 = v2_addf(obj1, -obj->col_size);

	if (intersects_collider(pl1, pl2, obj1, obj2))
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