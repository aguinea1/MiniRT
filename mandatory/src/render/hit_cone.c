/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cone.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellmas <lbellmas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:22:22 by lbellmas          #+#    #+#             */
/*   Updated: 2026/01/12 19:48:39 by lbellmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minirt.h"

typedef struct s_cone_data
{
	t_vec	axis;
	t_vec	oc;
	double	k;
	double	a;
	double	b;
	double	c;
	double	disc;
	double	sqrt_disc;	
}	t_cone_data;

static void	check_cone_cap(t_ray ray, t_cone *co,
		t_vec axis, t_hit *hit)
{
	double	t;
	t_vec	center;
	t_vec	p;
	double	r;
	
	center = vec_add(co->position, vec_scale(axis, co->height));
	r = co->height * tan(co->angle * M_PI / 180.0);
	double denom = vec_dot(ray.direction, axis);
	if (fabs(denom) < 1e-6)
		return ;
	t = vec_dot(vec_sub(center, ray.origin), axis) / denom;
	if (t < 0 || t >= hit->t)
		return ;
	p = vec_add(ray.origin, vec_scale(ray.direction, t));
	if (vec_length(vec_sub(p, center)) <= r)
	{
		hit->hit = 1;
		hit->t = t;
		hit->point = p;
		hit->normal = vec_scale(axis, -1);

		if (co->pattern == NONE || co->pattern == BUMP)
			hit->color = co->color;
		else if (co->pattern == CHECKER)
			hit->color = ft_checkerboard(*hit);
	}
}

static void	intersect_cone_body(t_ray ray, t_cone *co,
		t_cone_data *d, t_hit *hit)
{
	int		i;
	double	t;
	double	h;
	t_vec	p;
	t_vec	v;
	t_vec	n;

	i = -1;
	while (++i < 2)
	{
		t = (-d->b + (i ? d->sqrt_disc : -d->sqrt_disc)) / (2 * d->a);
		if (fabs(d->a) < 1e-6)
			return ;
		if (t < 0 || t >= hit->t)
			continue ;
		p = vec_add(ray.origin, vec_scale(ray.direction, t));
		v = vec_sub(p, co->position);
		h = vec_dot(v, d->axis);
		if (h < 0 || h > co->height)
			continue ;

		hit->hit = 1;
		hit->t = t;
		hit->point = p;
		double m = vec_dot(v, d->axis);
		n = vec_sub(v, vec_scale(d->axis, m * (1 + d->k)));
		if (co->pattern == BUMP)
			hit->normal = ft_bump_normal(*hit, 0.3);
		else
			hit->normal = vec_normalize(n);
		if (co->pattern == NONE || co->pattern == BUMP)
			hit->color = co->color;
		else if (co->pattern == CHECKER)
			hit->color = ft_checkerboard(*hit);
	}
}

static int	prepare_cone_data(t_ray ray, t_cone *co, t_cone_data *out)
{
	if (vec_length(co->direction) < 1e-6)
		return (0);

	out->axis = vec_normalize(co->direction);
	out->oc = vec_sub(ray.origin, co->position);
	out->k = tan(co->angle * M_PI / 180.0);
	out->k = out->k * out->k;

	double dv = vec_dot(ray.direction, out->axis);
	double ov = vec_dot(out->oc, out->axis);

	out->a = vec_dot(ray.direction, ray.direction)
		- (1 + out->k) * dv * dv;
	out->b = 2 * (vec_dot(ray.direction, out->oc)
		- (1 + out->k) * dv * ov);
	out->c = vec_dot(out->oc, out->oc)
		- (1 + out->k) * ov * ov;

	out->disc = out->b * out->b - 4 * out->a * out->c;
	if (out->disc < 0)
		return (0);

	out->sqrt_disc = sqrt(out->disc);
	return (1);
}

t_hit	hit_cone(t_ray ray, t_cone *co)
{
	t_hit			hit;
	t_cone_data		data;

	hit.hit = 0;
	hit.t = INFINITY;

	if (!prepare_cone_data(ray, co, &data))
		return (hit);

	intersect_cone_body(ray, co, &data, &hit);
	check_cone_cap(ray, co, data.axis, &hit);

	if (hit.hit)
	{
		if (vec_dot(ray.direction, hit.normal) > 0)
			hit.normal = vec_scale(hit.normal, -1);
	}
	return (hit);
}

t_hit find_closest_cone(t_ray ray, t_list *list)
{
	t_hit closest_hit;
	t_hit current_hit;
	t_cone *cone;
	double min_t;

	closest_hit.hit = 0;
	min_t = INFINITY;

	while (list)
	{
		cone = (t_cone *)list->content;
		current_hit = hit_cone(ray, cone);
		if (current_hit.hit && current_hit.t < min_t)
		{
			min_t = current_hit.t;
			closest_hit = current_hit;
		}
		list = list->next;
	}

	closest_hit.ks = 0.5;
	closest_hit.shininess = 32;
	return closest_hit;
}
