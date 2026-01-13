/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellmas <lbellmas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 15:35:51 by lbellmas          #+#    #+#             */
/*   Updated: 2026/01/13 21:11:49 by lbellmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minirt.h"

static	t_vec	ft_icheck_pattern(t_plane *plane, t_hit *hit)
{
	if (plane->pattern == BUMP)
		hit->normal = ft_bump_normal(*hit, 0.3);
	else
		hit->normal = plane->normal;
	if (plane->pattern == NONE || plane->pattern == BUMP)
		return (plane->color);
	else if (plane->pattern == CHECKER)
		return (ft_checkerboard(*hit));
	return (plane->color);
}

t_hit	hit_plane(t_ray ray, t_plane *plane)
{
	t_hit	hit;
	double	denom;
	double	t;
	t_vec	p0_to_origin;

	hit.hit = 0;
	plane->normal = vec_normalize(plane->normal);
	denom = vec_dot(ray.direction, plane->normal);
	if (fabs(denom) < 1e-6)
		return (hit);
	p0_to_origin = vec_sub(plane->position, ray.origin);
	t = vec_dot(p0_to_origin, plane->normal) / denom;
	if (t < 0)
		return (hit);
	hit.hit = 1;
	hit.t = t;
	hit.point = vec_add(ray.origin, vec_scale(ray.direction, t));
	hit.color = ft_icheck_pattern(plane, &hit);
	return (hit);
}

t_hit	find_closest_plane(t_ray ray, t_list *list)
{
	t_hit		closest_hit;
	t_hit		current_hit;
	t_plane		*plane;
	double		min_t;

	closest_hit.hit = 0;
	min_t = INFINITY;
	while (list)
	{
		plane = (t_plane *)list->content;
		current_hit = hit_plane(ray, plane);
		if (current_hit.hit && current_hit.t < min_t)
		{
			min_t = current_hit.t;
			closest_hit = current_hit;
		}
		list = list->next;
	}
	closest_hit.ks = 0.5;
	closest_hit.shininess = 32;
	return (closest_hit);
}
