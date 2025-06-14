/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 00:05:41 by aguinea           #+#    #+#             */
/*   Updated: 2025/06/14 04:12:47 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minirt.h"

int	parse_vec(char *str, t_vec *vec)
{
	char	**split;

	split = ft_split(str, ',');
	if (!split || !split[0] || !split[1] || !split[2] || split[3])
		return (free_array(split),
			printf("Error\nInvalid vector format\n"), 0);
	vec->x = ft_atof(split[0]);
	vec->y = ft_atof(split[1]);
	vec->z = ft_atof(split[2]);
	return (free_array(split), 1);
}

static int	parse_fov(char *fov_str, t_scene *scene)
{
	float	fov;

	if (!is_valid_float(fov_str))
		return (printf("Error\nInvalid float (camera[fov])\n"), 0);
	fov = ft_atof(fov_str);
	if (fov < 0.0 || fov > 180.0)
		return (printf("Error\nFOV must be in range [0,180]\n"), 0);
	scene->camera.fov = fov;
	return (1);
}

static int	parse_orientation(t_vec vec)
{
	if (vec.x < -1.0 || vec.x > 1.0
		|| vec.y < -1.0 || vec.y > 1.0
		|| vec.z < -1.0 || vec.z > 1.0)
		return (printf("Error\nCamera orientation must be in range [-1,1]\n"),
			0);
	return (1);
}

static int	parse_camera_orientation(char **tokens, t_scene *scene)
{
	t_vec	pos;
	t_vec	orient;

	if (!parse_vec(tokens[1], &pos))
		return (printf("Error\nInvalid camera position vector\n"), 0);
	if (!parse_vec(tokens[2], &orient))
		return (printf("Error\nInvalid camera orientation vector\n"), 0);
	if (!parse_orientation(orient))
		return (0);
	scene->camera.position = pos;
	scene->camera.orientation = orient;
	return (1);
}

int	parse_camera(char **tokens, t_scene *scene)
{
	if (!tokens[1] || !tokens[2] || !tokens[3])
		return (printf("Error\nCamera requires 3 parameters\n"), 0);
	if (parse_camera_orientation(tokens, scene)
		&& parse_fov(tokens[3], scene))
		return (1);
	return (0);
}
