#include "../inc/ray_tracer.h"

/*
	allocates, fills and returns a new tuple, or NULL on errors.
	pass in VECTOR or POINT macro as 'w' parameter to specify the type of tuple.
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

t_tuple *create_point(float x, float y, float z)
{
	return (create_tuple(x, y, z, POINT));
}

t_tuple *create_vector(float x, float y, float z)
{
	return (create_tuple(x, y, z, VECTOR));
}


t_colour	*create_colour(float r, float g, float b)
{
	t_colour *c;

	c = malloc(1 * sizeof(t_colour));
	if (!c)
		return (NULL);
	c->r = r;
	c->g = g;
	c->b = b;
	return (c);
}