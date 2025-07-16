/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_op1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 15:47:57 by aguinea           #+#    #+#             */
/*   Updated: 2025/07/16 13:18:13 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minirt.h"
//esto son todas las operaciones que encontre con vectores, ns ni si las uso todas pero bueno aqui estan
t_vec	vec_add(t_vec a, t_vec b)
{
	return (vec(a.x + b.x, a.y + b.y, a.z + b.z));
}

t_vec	vec_sub(t_vec a, t_vec b)
{
	return (vec(a.x - b.x, a.y - b.y, a.z - b.z));
}

t_vec	vec_mult(t_vec a, double t)
{
	return (vec(a.x * t, a.y * t, a.z * t));
}

double	vec_dot(t_vec a, t_vec b)
{
	return ((a.x * b.x + a.y * b.y + a.z * b.z));
}

t_vec	vec_cross(t_vec a, t_vec b)
{
	return (vec(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z,
			a.x * b.y - a.y * b.x));
}
