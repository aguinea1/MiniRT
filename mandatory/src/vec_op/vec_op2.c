/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_op2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 15:53:20 by aguinea           #+#    #+#             */
/*   Updated: 2025/07/04 15:54:09 by aguinea          ###   ########.fr       */
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
	return sqrt(vec_dot(v, v));
}
