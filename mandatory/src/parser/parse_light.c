/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 00:33:03 by aguinea           #+#    #+#             */
/*   Updated: 2025/07/17 12:50:41 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minirt.h"
/*
static int	parse_bright(char *str, t_scene *scene)
{
	float	brightness;

	if (!is_valid_float(str))
		return (printf("Error\nInvalid float (light[brightness])\n"), 0);
	brightness = ft_atof(str);
	if (brightness < 0.0 || brightness > 1.0)
		return (printf("Error\nBrightness must be in range [0,1]\n"), 0);
	scene->light.brightness = brightness;
	return (1);
}

static int	parse_color(char *str, t_scene *scene)
{
	char	**rgb;

	rgb = ft_split(str, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
		return (free_array(rgb),
			printf("Error\nInvalid RGB format (light[color])\n"), 0);
	if (!is_valid_rgb_value(rgb[0])
		|| !is_valid_rgb_value(rgb[1])
		|| !is_valid_rgb_value(rgb[2]))
		return (free_array(rgb),
			printf("Error\nRGB values must be 0–255\n"), 0);
	scene->light.color.x = (float)atoi(rgb[0]);
	scene->light.color.y = (float)atoi(rgb[1]);
	scene->light.color.z = (float)atoi(rgb[2]);
	return (free_array(rgb), 1);
}
*/
int	parse_light(char **tokens, t_scene *scene)
{
	t_light	*light;
	t_vec	pos;
	char	**rgb;

//	scene->light = NULL;
	if (num_args(tokens) != 4)
		return (printf("Error\nInvalid number of Light arguments\n"), 0);
	if (!parse_vec(tokens[1], &pos))
		return (printf("Error\nInvalid light position vector\n"), 0);

	if (!is_valid_float(tokens[2]))
		return (printf("Error\nInvalid float (light[brightness])\n"), 0);

	rgb = ft_split(tokens[3], ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
		return (free_array(rgb),
			printf("Error\nInvalid RGB format (light[color])\n"), 0);
	if (!is_valid_rgb_value(rgb[0]) || !is_valid_rgb_value(rgb[1]) || !is_valid_rgb_value(rgb[2]))
		return (free_array(rgb),
			printf("Error\nRGB values must be 0–255\n"), 0);

	light = malloc(sizeof(t_light));
	if (!light)
		return (free_array(rgb), printf("Error\nMalloc failed for light\n"), 0);

	light->position = pos;
	light->brightness = ft_atof(tokens[2]);
	if (light->brightness < 0.0f || light->brightness > 1.0f)
		return (free(light), free_array(rgb),
			printf("Error\nBrightness must be in range [0,1]\n"), 0);

	light->color.x = (float)atoi(rgb[0]);
	light->color.y = (float)atoi(rgb[1]);
	light->color.z = (float)atoi(rgb[2]);

	free_array(rgb);
	ft_lstadd_back(&scene->light, ft_lstnew(light));
	return (1);
}

