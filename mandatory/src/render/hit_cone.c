/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cone.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellmas <lbellmas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:22:22 by lbellmas          #+#    #+#             */
/*   Updated: 2026/01/16 17:13:05 by lbellmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minirt.h"

static	t_vec	ft_check_pattern(t_cone *co, t_hit *hit)
{
	if (co->pattern == NONE || co->pattern == BUMP)
		return (co->color);
	else if (co->pattern == CHECKER)
		return (ft_checkerboard(*hit));
	return (co->color);
}

void	check_cone_cap(t_ray ray, t_cone *co,
		t_vec axis, t_hit *hit)
{
	double	t;
	t_vec	center;
	t_vec	p;
	double	r;
	double	denom;

	center = vec_add(co->position, vec_scale(axis, co->height));
	r = co->height * tan(co->angle * M_PI / 180.0);
	denom = vec_dot(ray.direction, axis);
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
		hit->color = ft_check_pattern(co, hit);
	}
}

t_vec	ft_ccheck_pattern(t_cone *co, t_hit *hit, t_vec n)
{
	if (co->pattern == BUMP)
		hit->normal = ft_bump_normal(*hit, 0.3);
	else
		hit->normal = vec_normalize(n);
	if (co->pattern == NONE || co->pattern == BUMP)
		return (co->color);
	else if (co->pattern == CHECKER)
		return (ft_checkerboard(*hit));
	return (co->color);
}

double	ft_set_t(t_cone_data *d, int i)
{
	if (i == 0)
		return ((-d->b - d->sqrt_disc) / (2 * d->a));
	else
		return ((-d->b + d->sqrt_disc) / (2 * d->a));
}

void	ft_set_hit(t_hit *hit, double t, t_vec p)
{
	hit->hit = 1;
	hit->t = t;
	hit->point = p;
}
