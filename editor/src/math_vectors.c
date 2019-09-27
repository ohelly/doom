#include "doom.h"

t_v2	v2_add(t_v2 v1, t_v2 v2)
{
	t_v2 result;

	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	return (result);
}

/*
**	Возвращает 1 если координаты точек v1 и v2 совпадают
*/

int			compare_v2(t_v2 v1, t_v2 v2)
{
	if (v1.x == v2.x && v1.y == v2.y)
		return (1);
	return (0);
}