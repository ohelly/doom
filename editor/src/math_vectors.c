#include "doom.h"

t_v2	v2_add(t_v2 v1, t_v2 v2)
{
	t_v2 result;

	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	return (result);
}
