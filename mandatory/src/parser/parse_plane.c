/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 01:27:23 by aguinea           #+#    #+#             */
/*   Updated: 2025/06/12 02:13:12 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minirt.h"

static void	add_plane(t_plane *plane, t_vec position, t_vec normal, char **rgb)
{
	plane->position = position;
	plane->normal = normal;
	plane->color.x = (float)atoi(rgb[0]);
	plane->color.y = (float)atoi(rgb[1]);
	plane->color.z = (float)atoi(rgb[2]);
}

int	parse_plane(char **tokens, t_scene *scene)
{
	t_plane	*plane;
	t_vec	position;
	t_vec	normal;
	char	**rgb;

	if (num_args(tokens) != 4)
		return (printf("Plane must have 3 arguments\n"), 0);
	if (!parse_vec(tokens[1], &position))
		return (printf("Invalid plane position vector\n"), 0);
	if (!parse_vec(tokens[2], &normal))
		return (printf("Invalid plane normal vector\n"), 0);
	if (!vec_is_normalized(normal))
		return (printf("Plane normal vector must be in range [-1, 1]\n"), 0);
	rgb = parse_rgb(tokens[3]);
	if (!rgb)
		return (0);
	plane = malloc(sizeof(t_plane));
	if (!plane)
		return (free_array(rgb), 0);
	add_plane(plane, position, normal, rgb);
	return (free_array(rgb),
		ft_lstadd_back(&scene->planes, ft_lstnew(plane)), 1);
}
