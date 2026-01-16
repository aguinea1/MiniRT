/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_normie.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellmas <lbellmas@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:17:12 by lbellmas          #+#    #+#             */
/*   Updated: 2026/01/16 17:17:15 by lbellmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minirt.h"

t_vec	ft_checkerboard(t_hit hit)
{
	int		check;
	double	scale;

	scale = 1.0;
	check = (int)(floor(hit.point.x * scale)
			+ floor(hit.point.y * scale)
			+ floor(hit.point.z * scale)) % 2;
	if (check == 0)
		return (vec(255, 255, 255));
	else
		return (vec(0, 0, 0));
}

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
	closest_hit.ks = 0.5;
	closest_hit.shininess = 32;
	return (closest_hit);
}
