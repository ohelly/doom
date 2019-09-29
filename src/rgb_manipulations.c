#include "doom.h"

int	rgb_multiply(int color, float value)
{
	int r;
	int g;
	int b;

	r = (color & 0xFF0000) * value;
	g = (color & 0x00FF00) * value;
	b = (color & 0x0000FF) * value;
	return ((r & 0xFF0000) | (g & 0x00FF00) | (b & 0x0000FF));
}