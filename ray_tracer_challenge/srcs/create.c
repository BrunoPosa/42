#include "../inc/ray_tracer.h"

/*
	allocates, fills and returns a new tuple, or NULL on errors
*/
t_tuple *create_tuple(float x, float y, float z, float w)
{
	t_tuple *t;

	t = malloc(1 * sizeof(t_tuple));
	if (!t)
		return (NULL);
	t->x = x;
	t->y = y;
	t->z = z;
	t->w = w;
	return (t);
}
