/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 01:13:06 by aguinea           #+#    #+#             */
/*   Updated: 2025/06/12 02:38:06 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../..//header/minirt.h"

static int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (0);
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	is_valid_rgb_value(char *str)
{
	int	value;

	if (!str || !is_numeric(str))
		return (0);
	value = atoi(str);
	return (value >= 0 && value <= 255);
}

int	vec_is_normalized(t_vec v)
{
	float	length;

	length = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
	if (fabsf(length - 1.0f) < 0.0001f)
		return (1);
	return (0);
}
