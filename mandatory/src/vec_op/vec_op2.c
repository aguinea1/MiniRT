/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_op2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 15:53:20 by aguinea           #+#    #+#             */
/*   Updated: 2025/07/09 15:27:12 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minirt.h"
#include <math.h>

int	vec_is_normalized(t_vec v)
{
	float	length;

	length = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
	if (fabsf(length - 1.0f) < 0.0001f)
		return (1);
	return (0);
}

double	vec_length(t_vec v)
{
	return (sqrt(vec_dot(v, v)));
}

t_vec	vec_normalize(t_vec v)
{
	double	len;

	len = vec_length(v);
	if (len == 0)
		return (vec(0, 0, 0));
	return (vec(v.x / len, v.y / len, v.z / len));
}

t_vec	vec_scale(t_vec v, double scalar)
{
	t_vec	result;

	result.x = v.x * scalar;
	result.y = v.y * scalar;
	result.z = v.z * scalar;
	return (result);
}

t_vec	vec(double x, double y, double z)
{
	t_vec	result;

	result.x = x;
	result.y = y;
	result.z = z;
	return (result);
}
