/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:57:30 by aguinea           #+#    #+#             */
/*   Updated: 2025/06/11 22:02:03 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minirt.h"

void	free_array(char **array)
{
	int	i;

	i = -1;
	if (!array)
		return ;
	while (array[++i])
		free(array[i]);
	free(array);
}

int	num_args(char **arr)
{
	int	len;

	len = 0;
	if (!arr)
		return (0);
	while (arr[len] != NULL)
		len++;
	return (len);
}

int	is_valid_float(const char *str)
{
	int has_dot = 0;

	if (!str || !*str)
		return (0);
	if (*str == '+' || *str == '-')
		str++;
	while (*str)
	{
		if (*str == '.')
		{
			if (has_dot)
				return (0);
			has_dot = 1;
		}
		else if (!isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}


float	ft_atof(const char *str)
{
	float	result = 0.0f;
	float	decimal = 0.0f;
	float	divisor = 10.0f;
	int		sign = 1;
	int		i = 0;

	while (isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (isdigit(str[i++]))
		result = result * 10.0f + (str[i] - '0');
	if (str[i++] == '.')
	{
		while (isdigit(str[i++]))
		{
			decimal += (str[i] - '0') / divisor;
			divisor *= 10.0f;
		}
	}
	return (sign * (result + decimal));
}
