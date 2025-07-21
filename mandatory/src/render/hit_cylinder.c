/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 17:56:00 by aguinea           #+#    #+#             */
/*   Updated: 2025/07/21 20:37:26 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minirt.h"

t_hit	find_closest_cylinder(t_ray ray, t_list *cyls)
{
	t_hit		closest_hit;
	t_hit		current_hit;
	double		min_t;
	t_cylinder	*cyl;

	closest_hit.hit = 0;
	min_t = INFINITY;
	while (cyls)
	{
		cyl = (t_cylinder *)cyls->content;
		current_hit = hit_cylinder(ray, cyl);
		if (current_hit.hit && current_hit.t < min_t)
		{
			min_t = current_hit.t;
			closest_hit = current_hit;
		}
		cyls = cyls->next;
	}
	return (closest_hit);
}

static void	check_cylinder_cap(t_ray ray, t_cylinder *cy,
		t_vec axis, t_hit *hit)
{
	int		i;
	double	t_de[2];
	t_vec	c_p[2];

	i = -1;
	while (++i < 2)
	{
		center_cyl(i, cy, axis, &c_p[0]);
		t_de[1] = vec_dot(ray.direction, axis);
		if (fabs(t_de[1]) > 1e-6)
		{
			t_de[0] = vec_dot(vec_sub(c_p[0], ray.origin), axis) / t_de[1];
			if (t_de[0] >= 0 && t_de[0] < hit->t)
			{
				c_p[1] = vec_add(ray.origin, vec_scale(ray.direction, t_de[0]));
				if (vec_length(vec_sub(c_p[1], c_p[0])) <= cy->diameter / 2.0)
				{
					hit->i = i;
					hit_cylinder_cap(c_p[1], hit, t_de[0], axis);
					hit->color = cy->color;
				}
			}
		}
	}
}

static void	intersect_cylinder_body(t_ray ray, t_cylinder *cy,
		t_cyl_data *d, t_hit *hit)
{
	int		i;
	double	t;
	double	h;
	t_vec	p[2];
	t_vec	n;

	i = -1;
	while (++i < 2)
	{
		whats_t(&t, d, i);
		if (t < 0 || t >= hit->t)
			continue ;
		p[0] = vec_add(ray.origin, vec_scale(ray.direction, t));
		p[1] = vec_sub(p[0], cy->position);
		h = vec_dot(p[1], d->axis);
		if (h < 0 || h > cy->height)
			continue ;
		hit->hit = 1;
		hit->t = t;
		hit->point = p[0];
		n = vec_sub(p[1], vec_scale(d->axis, h));
		hit->normal = vec_normalize(n);
		hit->color = cy->color;
	}
}

static int	prepare_cylinder_data(t_ray ray, t_cylinder *cy, t_cyl_data *out)
{
	if (vec_length(cy->orientation) < 1e-6)
		return (0);
	out->axis = vec_normalize(cy->orientation);
	out->oc = vec_sub(ray.origin, cy->position);
	out->d_proj = vec_sub(ray.direction, vec_scale(out->axis,
				vec_dot(ray.direction, out->axis)));
	out->oc_proj = vec_sub(out->oc, vec_scale(out->axis,
				vec_dot(out->oc, out->axis)));
	out->a = vec_dot(out->d_proj, out->d_proj);
	out->b = 2.0 * vec_dot(out->d_proj, out->oc_proj);
	out->c = vec_dot(out->oc_proj, out->oc_proj) - pow(cy->diameter / 2.0, 2);
	out->disc = out->b * out->b - 4 * out->a * out->c;
	if (out->disc < 0)
		return (0);
	out->sqrt_disc = sqrt(out->disc);
	return (1);
}

t_hit	hit_cylinder(t_ray ray, t_cylinder *cy)
{
	t_hit		hit;
	t_cyl_data	data;

	hit.hit = 0;
	hit.t = INFINITY;
	if (!prepare_cylinder_data(ray, cy, &data))
		return (hit);
	intersect_cylinder_body(ray, cy, &data, &hit);
	check_cylinder_cap(ray, cy, data.axis, &hit);
	if (hit.hit)
	{
		if (vec_dot(ray.direction, hit.normal) > 0)
			hit.normal = vec_scale(hit.normal, -1);
	}
	return (hit);
}
