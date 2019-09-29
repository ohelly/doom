#include "doom.h"

int	remove_built_sector(t_doom *doom)
{
	if (doom->verts->built_v_count == 0 || doom->app != 1)
		return (0);

	doom->verts->count -= doom->verts->built_v_count - doom->verts->built_v_count_used;
	doom->walls->count -= doom->verts->built_v_count - 1;
	doom->verts->built_v_count = 0;
	doom->verts->built_v_count_used = 0;
	doom->app = 0;
	return (1);
}
