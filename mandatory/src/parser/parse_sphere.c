/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 00:47:32 by aguinea           #+#    #+#             */
/*   Updated: 2025/06/14 04:13:12 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minirt.h"

char	**parse_rgb(char *rgb1)
{
	char	**rgb;

	rgb = ft_split(rgb1, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
		return (free_array(rgb), printf("Error\nInvalid sphere color format\n"),
			NULL);
	if (!is_valid_rgb_value(rgb[0])
		|| !is_valid_rgb_value(rgb[1])
		|| !is_valid_rgb_value(rgb[2]))
		return (free_array(rgb),
			printf("Error\nSphere RGB values must be 0–255\n"), NULL);
	return (rgb);
}

static void	add_sphere(t_sphere *sphere, char **rgb,
			t_vec center, float diameter)
{
	sphere->center = center;
	sphere->diameter = diameter;
	sphere->color.x = (float)atoi(rgb[0]);
	sphere->color.y = (float)atoi(rgb[1]);
	sphere->color.z = (float)atoi(rgb[2]);
}

int	parse_sphere(char **tokens, t_scene *scene)
{
	char		**rgb;
	float		diameter;
	t_sphere	*sphere;
	t_vec		center;

	if (num_args(tokens) != 4)
		return (printf("Error\nInvalid number of Sphere arguments\n"), 0);
	if (!parse_vec(tokens[1], &center))
		return (printf("Error\nInvalid sphere center vector\n"), 0);
	if (!is_valid_float(tokens[2]))
		return (printf("Error\nInvalid sphere diameter\n"), 0);
	diameter = ft_atof(tokens[2]);
	if (diameter <= 0)
		return (printf("Error\nSphere diameter must be positive\n"), 0);
	rgb = parse_rgb(tokens[3]);
	if (rgb == NULL)
		return (0);
	sphere = malloc(sizeof(t_sphere));
	add_sphere(sphere, rgb, center, diameter);
	free_array(rgb);
	return (ft_lstadd_back(&scene->spheres, ft_lstnew(sphere)), 1);
}
