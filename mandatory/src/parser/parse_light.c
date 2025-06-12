/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 00:33:03 by aguinea           #+#    #+#             */
/*   Updated: 2025/06/12 02:40:26 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minirt.h"

static int	parse_bright(char *str, t_scene *scene)
{
	float	brightness;

	if (!is_valid_float(str))
		return (printf("Invalid float (light[brightness])\n"), 0);
	brightness = ft_atof(str);
	if (brightness < 0.0 || brightness > 1.0)
		return (printf("Brightness must be in range [0,1]\n"), 0);
	scene->light.brightness = brightness;
	return (1);
}

static int	parse_color(char *str, t_scene *scene)
{
	char	**rgb;

	rgb = ft_split(str, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
		return (free_array(rgb),
			printf("Invalid RGB format (light[color])\n"), 0);
	if (!is_valid_rgb_value(rgb[0])
		|| !is_valid_rgb_value(rgb[1])
		|| !is_valid_rgb_value(rgb[2]))
		return (free_array(rgb), printf("RGB values must be 0–255\n"), 0);
	scene->light.color.x = (float)atoi(rgb[0]);
	scene->light.color.y = (float)atoi(rgb[1]);
	scene->light.color.z = (float)atoi(rgb[2]);
	return (free_array(rgb), 1);
}

int	parse_light(char **tokens, t_scene *scene)
{
	t_vec	pos;

	if (num_args(tokens) != 4)
		return (printf("Invalid number of Light arguments\n"), 0);
	if (!parse_vec(tokens[1], &pos))
		return (printf("Invalid light position vector\n"), 0);
	scene->light.position = pos;
	if (!parse_bright(tokens[2], scene) || !parse_color(tokens[3], scene))
		return (0);
	return (1);
}
