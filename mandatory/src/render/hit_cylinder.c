/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 17:56:00 by aguinea           #+#    #+#             */
/*   Updated: 2025/07/15 16:44:06 by aguinea          ###   ########.fr       */
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

static int	prepare_cylinder_data(t_ray ray, t_cylinder *cy, t_cyl_data *out)
{
	if (vec_length(cy->orientation) < 1e-6)
		return (0);
	out->axis = vec_normalize(cy->orientation);
	out->oc = vec_sub(ray.origin, cy->position);
	out->d_proj = vec_sub(ray.direction,
			vec_scale(out->axis, vec_dot(ray.direction, out->axis)));
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

static void	intersect_cylinder_body(t_ray ray,
			t_cylinder *cy, t_cyl_data *d, t_hit *hit)
{
	int		i;
	double	t;
	double	h;
	t_vec	pv[2];
	t_vec	n;

	i = 0;
	while (i++ < 2)
	{
		t = (-d->b + (i == 0 ? -d->sqrt_disc : d->sqrt_disc)) / (2.0 * d->a);
		if (t < 0 || t >= hit->t)
			continue ;
		pv[0] = vec_add(ray.origin, vec_scale(ray.direction, t));
		pv[1] = vec_sub(pv[0], cy->position);
		h = vec_dot(pv[1], d->axis);
		if (h < 0 || h > cy->height)
			continue ;
		hit->hit = 1;
		hit->t = t;
		hit->point = pv[0];
		n = vec_sub(pv[1], vec_scale(d->axis, h));
		hit->normal = vec_normalize(n);
		hit->color = cy->color;
	}
}

static void	check_cylinder_cap(t_ray ray,
			t_cylinder *cy, t_vec axis, t_hit *hit)
{
	int		i;
	double	t;
	double	denom;
	t_vec	center;
	t_vec	p;

	i = 0;
	while (i < 2)
	{
		if (i == 0)
			center = cy->position;
		else
			center = vec_add(cy->position, vec_scale(axis, cy->height));
		denom = vec_dot(ray.direction, axis);
		if (fabs(denom) > 1e-6)
		{
			t = vec_dot(vec_sub(center, ray.origin), axis) / denom;
			if (t >= 0 && t < hit->t)
			{
				p = vec_add(ray.origin, vec_scale(ray.direction, t));
				if (vec_length(vec_sub(p, center)) <= cy->diameter / 2.0)
				{
					hit->hit = 1;
					hit->t = t;
					hit->point = p;
					hit->normal = (i == 0) ? vec_scale(axis, -1) : axis;
					hit->color = cy->color;
				}
			}
		}
		i++;
	}
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
	return (hit);
}
