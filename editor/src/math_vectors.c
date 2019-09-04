#include "doom.h"

t_v2	v2_add(t_v2 v1, t_v2 v2)
{
	t_v2 result;

	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	return (result);
}

t_v2	v2_sub(t_v2 v1, t_v2 v2)
{
	t_v2 result;

	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	return (result);
}

t_v2	v2_dot(t_v2 v1, t_v2 v2)
{
	float result;

	result = v1.x * v2.x + v1.y * v2.y;
}

t_v2	v2_addf(t_v2 v, float f)
{
	t_v2 result;

	result.x = v.x + f;
	result.y = v.y + f;
	return (result);
}

t_v2	v2_mult(t_v2 v1, t_v2 v2)
{
	t_v2 result;

	result.x = v1.x * v2.x;
	result.y = v1.y * v2.y;
	return (result);
}