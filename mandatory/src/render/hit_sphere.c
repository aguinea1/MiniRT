/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 16:59:42 by aguinea           #+#    #+#             */
/*   Updated: 2025/07/10 17:44:52 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minirt.h"

static void	complete_abc(t_ray ray, t_sphere *sphere, double *abc, t_vec oc)
{
	abc[0] = vec_dot(ray.direction, ray.direction);
	abc[1] = 2.0 * vec_dot(oc, ray.direction);
	abc[2] = vec_dot(oc, oc) - powf(sphere->diameter / 2, 2);
}

t_hit	hit_sphere(t_ray ray, t_sphere *sphere)
{
	t_hit		hit;
	t_vec		oc;
	double		abc[3];
	double		discriminant;
	double		t;

	oc = vec_sub(ray.origin, sphere->center);
	complete_abc(ray, sphere, abc, oc);
	discriminant = abc[1] * abc[1] - 4 * abc[0] * abc[2];
	hit.hit = 0;
	if (discriminant < 0)
		return (hit);
	t = (-abc[1] - sqrt(discriminant)) / (2.0 * abc[0]);
	if (t < 0)
		t = (-abc[1] + sqrt(discriminant)) / (2.0 * abc[0]);
	if (t < 0)
		return (hit);
	hit.hit = 1;
	hit.t = t;
	hit.point = vec_add(ray.origin, vec_scale(ray.direction, t));
	hit.normal = vec_normalize(vec_sub(hit.point, sphere->center));
	hit.color = sphere->color;
	return (hit);
}

t_hit	find_closest_sphere(t_ray ray, t_list *spheres)
{
	t_hit		closest_hit;
	t_hit		current_hit;
	double		min_t;
	t_sphere	*sphere;

	closest_hit.hit = 0;
	min_t = INFINITY;
	while (spheres)
	{
		sphere = (t_sphere *)spheres->content;
		current_hit = hit_sphere(ray, sphere);
		if (current_hit.hit && current_hit.t < min_t)
		{
			min_t = current_hit.t;
			closest_hit = current_hit;
		}
		spheres = spheres->next;
	}
	return (closest_hit);
}
