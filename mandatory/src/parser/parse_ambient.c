/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 17:41:04 by aguinea           #+#    #+#             */
/*   Updated: 2025/06/12 02:37:27 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minirt.h"

static int	parse_ratio(char *ratio_str, t_scene *scene)
{
	float	ratio;

	if (!is_valid_float(ratio_str))
		return (printf("Invalid float (ambient[ratio])\n"), 0);
	ratio = ft_atof(ratio_str);
	if (ratio < 0.0 || ratio > 1.0)
		return (printf("Invalid float range (ambient[ratio])\n"), 0);
	scene->ambient.ratio = ratio;
	return (1);
}

int	parse_rgb_int(char **rgb, t_scene *scene)
{
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
		return (printf("RGB must have exactly 3 components\n"), 0);
	if (!is_valid_rgb_value(rgb[0])
		|| !is_valid_rgb_value(rgb[1]) || !is_valid_rgb_value(rgb[2]))
		return (printf("RGB values must be between 0 and 255\n"), 0);
	scene->ambient.color.x = (float)atoi(rgb[0]);
	scene->ambient.color.y = (float)atoi(rgb[1]);
	scene->ambient.color.z = (float)atoi(rgb[2]);
	return (1);
}

int	parse_ambient(char **tokens, t_scene *scene)
{
	char	**rgb;

	rgb = ft_split(tokens[2], ',');
	if (parse_ratio(tokens[1], scene) && parse_rgb_int(rgb, scene))
		return (free_array(rgb), 1);
	return (free_array(rgb), 0);
}
