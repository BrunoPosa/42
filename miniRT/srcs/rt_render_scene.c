/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_render_scene.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 20:01:23 by bposa             #+#    #+#             */
/*   Updated: 2024/12/11 19:34:45 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/file_to_list.h"

int clamp(float n)
{
	if (n > 255)
		return 255;
	if (n < 0)
		return 0;
	return n;
}

/*
	-'a' of the quadratic formula is 1, as 'ray' is a normalized vector, so we leave it out
	TODO:
		- move the sphere's radius to the shape struct and precalculate it
*/
float fsphere(t_vec ray, t_vec ray_origin, t_shape sphere)
{
	t_vec ray_origin_to_sphere_center;
	float	t;
	float	b;
	float	c;
	float	discriminant;

	ray_origin_to_sphere_center = subtract(ray_origin, sphere.xyz);
	t = -1.0f;
	b = 2 * dot(ray, ray_origin_to_sphere_center);
	c = dot(ray_origin_to_sphere_center, ray_origin_to_sphere_center) - sphere.r * sphere.r;
	discriminant = b * b - 4 * c;
	if (discriminant < 0)
		return (-1);
	t = (-b - sqrt(discriminant)) / 2;
	if (t < EPSILON)
		t = (-b + sqrt(discriminant)) / 2;
	return (t);
}

float	fplane(t_vec ray, t_vec ray_origin, t_shape plane)
{
	t_vec	origin_to_plane;
	float	dividend;
	float	divisor;
	float	t;

	origin_to_plane = subtract(plane.xyz, ray_origin);
	dividend = dot(plane.xyz3d, origin_to_plane);
	divisor = dot(ray, plane.xyz3d);
	if (fabs(divisor) < EPSILON)
		return (0);
	t = dividend / divisor;
	if (t < EPSILON)
		return (0);
	return (t);
}

int	circle(int x, int y, int center, int radius)
{
	int dx = x - center;
	int dy = y - center;
	int distance = sqrt(dx * dx + dy * dy);
	if (distance < radius)
		return (0xFFFF0000);
	else
		return (0x00000000);
}

float top_bottom_cyl(t_vec ray, t_vec ray_origin, t_shape cylinder)
{
	t_shape top;
	t_shape bottom;
	float t_top;
	float t_bottom;
	t_vec hit_point_top;
	t_vec hit_point_bottom;

	ft_bzero(&top, sizeof(t_shape));
	ft_bzero(&bottom, sizeof(t_shape));
	// Define the top and bottom caps as planes
	top.xyz = add(cylinder.xyz, multiply_tuple(cylinder.xyz3d, cylinder.h)); // Top center
	top.xyz3d = cylinder.xyz3d;                                              // Top normal
	bottom.xyz = cylinder.xyz;                                               // Bottom center
	bottom.xyz3d = negate_tuple(cylinder.xyz3d);                             // Bottom normal

	// Find intersection t-values with the planes
	t_top = fplane(ray, ray_origin, top);
	t_bottom = fplane(ray, ray_origin, bottom);

	// Check if the intersection point lies within the circular cap area
	if (t_top > 0)
	{
		hit_point_top = add(ray_origin, multiply_tuple(ray, t_top)); // Intersection point
		if (magnitude(subtract(hit_point_top, top.xyz)) > cylinder.r)
			t_top = 0; // Intersection point is outside the top cap radius
	}
	if (t_bottom > 0)
	{
		hit_point_bottom = add(ray_origin, multiply_tuple(ray, t_bottom)); // Intersection point
		if (magnitude(subtract(hit_point_bottom, bottom.xyz)) > cylinder.r)
			t_bottom = 0; // Intersection point is outside the bottom cap radius
	}

	// Return the smallest positive t (if any)
	if (t_top > 0 && t_bottom > 0)
		return fminf(t_top, t_bottom);
	else if (t_top > 0)
		return t_top;
	else if (t_bottom > 0)
		return t_bottom;

	return 0; // No valid intersection with the caps
}


float fcylinder(t_vec ray, t_vec ray_origin, t_shape cylinder)
{
	t_vec	origin_to_cylinder;
	float coef[3];
	float discriminant;
	float t;
	float tcaps;
	float axis_projection;

	cylinder.xyz3d = normalize(cylinder.xyz3d);
	origin_to_cylinder = subtract(ray_origin, cylinder.xyz);
	coef[a] = dot(ray, ray) - (pow(dot(ray, cylinder.xyz3d), 2));
	coef[b] = 2 * (dot(ray, origin_to_cylinder) - (dot(ray, cylinder.xyz3d) *
		dot(origin_to_cylinder, cylinder.xyz3d)));
	coef[c] = dot(origin_to_cylinder, origin_to_cylinder) - 
		pow(dot(origin_to_cylinder, cylinder.xyz3d), 2) - cylinder.r * cylinder.r;
	discriminant = coef[b] * coef[b] - 4 * coef[a] * coef[c];
	if (discriminant < 0)
		return -1;
	t = (-coef[b] - sqrt(discriminant)) / (2 * coef[a]);
	if (t < EPSILON)
		t = (-coef[b] + sqrt(discriminant)) / (2 * coef[a]);
	tcaps = top_bottom_cyl(ray, ray_origin, cylinder);
	if (t > EPSILON)
	{
		t_vec hit_point1 = add(ray_origin, multiply_tuple(ray, t));
		axis_projection = dot(subtract(hit_point1, cylinder.xyz), cylinder.xyz3d);
		if (axis_projection < 0 || axis_projection > cylinder.h)
			t = -1;
	}
	if (t < EPSILON || tcaps < EPSILON)
		return (fmaxf(t, tcaps));
	return (fminf(t, tcaps));
}

t_vec	calculate_cy_normal(t_scene *scene, t_shape *cy)
{
	return (normalize(subtract(scene->data.hitp, add(cy->xyz, multiply_tuple(cy->xyz3d, cy->h / 2)))));
}

//fix in case of planes so there is no recalculating #efficiency.
//change to void type
int	calculate_diffuse_colour(t_scene *scene, t_shape *shape)
{
	float		diffuse_amount;
	t_colour	diffuse_color;

	diffuse_amount = 0;
	diffuse_color = create_colour(0,0,0);
	if (shape->type == cylinder)
		scene->data.normal = calculate_cy_normal(scene, shape);
	else
		scene->data.normal = normalize(subtract(scene->data.hitp, shape->xyz));
	diffuse_amount = dot(scene->data.normal, scene->data.shadow_ray);
	if (shape->type == plane)
		diffuse_amount = fabs(dot(shape->xyz3d, scene->data.shadow_ray));//how do we color if plane is looking away from light/diffuse_amount < 0?
	// if (diffuse_amount < 0)
	// 	diffuse_amount = 0;
	diffuse_color = multiply_colour_by(shape->rgb, scene->lbr);
	scene->data.diffuse_color = multiply_colour_by(diffuse_color, diffuse_amount);
	return(SUCCESS);
}

t_colour	calculate_colour(t_scene *scene, t_shape *shape)
{
	scene->data.shade_color = hadamard_product(shape->rgb, scene->ambiant);
	if (shadow_check(scene, scene->data.shadow_ray))
		return (scene->data.shade_color);
	calculate_diffuse_colour(scene, shape);
	return (add_colours(scene->data.shade_color, scene->data.diffuse_color));
}

int	shadow_check(t_scene *scene, t_vec shadowray)
{
	float		t;
	float		tmin;
	int			i;
	float		light_distance;

	i = 0;
	light_distance = magnitude(subtract(scene->lightpos, scene->data.hitp));
	tmin = light_distance;
	while (i < scene->shape_count)
	{
		t = shape_intersect(shadowray, scene->data.hitp, scene->shapes[i]);
		if (t > EPSILON && t < tmin)
				tmin = t;
		i++;
	}
	if (tmin < light_distance)
		return (1);
	return (0);
}

float	shape_intersect(t_vec ray, t_vec ray_origin, t_shape shape)
{
	if (shape.type == sphere)
		return (fsphere(ray, ray_origin, shape));
	else if (shape.type == plane)
		return (fplane(ray, ray_origin, shape));
	else if (shape.type == cylinder)
		return (fcylinder(ray, ray_origin, shape));
	return (0);
}

int	find_closest_shape(t_scene *scene, t_vec ray)
{
	float	hit;
	int		i;

	i = 0;
	hit = 0.0;
	scene->data.hitmin = (float)INT32_MAX;
	while (i < scene->shape_count)
	{
		hit = shape_intersect(ray, scene->camera.pos, scene->shapes[i]);
		if (hit > EPSILON && hit < scene->data.hitmin)
		{
			scene->data.hitmin = hit;
			scene->data.shape = &scene->shapes[i];
		}
		i++;
	}
	if (scene->data.hitmin < (float)INT32_MAX)
		return (1);
	return (0);
}

/*
	t represents the distance along the ray from its origin where it intersects the sphere:
	t>0 means there is an intersection, and the ray hits the sphere at t units from the ray origin
*/
int trace(t_scene *scene, t_vec ray)
{
	ft_bzero(&scene->data, sizeof(t_data));
	if (!find_closest_shape(scene, ray))
		return(ft_colour_to_uint32(scene->ambiant));
	scene->data.hitp = add(scene->camera.pos, multiply_tuple(ray, scene->data.hitmin));
	scene->data.shadow_ray = normalize(subtract(scene->lightpos, scene->data.hitp));
	return (ft_colour_to_uint32(calculate_colour(scene, scene->data.shape)));
}

/*
	as the viewing plane is focal_length away from camera's view point,
		we add focal_length to camera's z when making the camera's ray
*/
int	render_pixels(t_scene *scene, mlx_image_t *img)
{
	int		i;
	int		j;
	t_vec	ray;

	i = -1;
	j = -1;
	ray = create_vec(0, 0, 0);
	while (++i < WINSIZE)
	{
		j = -1;
		while (++j < WINSIZE)
		{
			ray = calculate_camera_ray(scene, scene->camera.pos, i, WINSIZE - j);
			if (!diff(ray, create_vec(0, 0, 0)))//do we need to check for this?
				return (ERROR);
			((uint32_t *)img->pixels)[j * WINSIZE + i] = trace(scene, ray);
		}
	}
	return (SUCCESS);
}
