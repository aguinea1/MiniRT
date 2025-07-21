/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 16:48:27 by aguinea           #+#    #+#             */
/*   Updated: 2025/07/21 20:42:23 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minirt.h"

void	hit_cylinder_cap(t_vec p, t_hit *hit, double t, t_vec axis)
{
	int	i;

	i = hit->i;
	hit->hit = 1;
	hit->t = t;
	hit->point = p;
	if (i == 0)
		hit->normal = vec_scale(axis, -1);
	else
		hit->normal = axis;
}

void	center_cyl(int i, t_cylinder *cy, t_vec	axis, t_vec *center)
{
	if (i == 0)
		*center = cy->position;
	else
		*center = vec_add(cy->position, vec_scale(axis, cy->height));
}

void	whats_t(double *t, t_cyl_data *d, int i)
{
	if (i == 0)
		*t = (-d->b - d->sqrt_disc) / (2.0 * d->a);
	else
		*t = (-d->b + d->sqrt_disc) / (2.0 * d->a);
}
