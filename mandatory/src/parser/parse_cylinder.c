/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 01:46:17 by aguinea           #+#    #+#             */
/*   Updated: 2025/06/13 11:51:28 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minirt.h"

static void	add_cyl(t_cylinder *cyl, t_vec pos, t_vec or, char **rgb)
{
	cyl->position = pos;
	cyl->orientation = or;
	cyl->color.x = (float)atoi(rgb[0]);
	cyl->color.y = (float)atoi(rgb[1]);
	cyl->color.z = (float)atoi(rgb[2]);
}

static int	check_args_pos_or(char **tokens, t_vec *pos, t_vec *or)
{
	if (num_args(tokens) != 6)
		return (printf("Cylinder must have 6 arguments\n"), 0);
	if (!parse_vec(tokens[1], pos))
		return (printf("Invalid cylinder position vector\n"), 0);
	if (!parse_vec(tokens[2], or))
		return (printf("Invalid cylinder orientation vector\n"), 0);
	if (!vec_is_normalized(*or))
		return (printf("Cylinder orientation must be in range [-1, 1]\n"), 0);
	if (!is_valid_float(tokens[3]) || !is_valid_float(tokens[4]))
		return (printf("Invalid cylinder diameter or height\n"), 0);
	return (1);
}

int	parse_cylinder(char **tokens, t_scene *scene)
{
	t_cylinder	*cyl;
	t_vec		position;
	t_vec		orientation;
	char		**rgb;

	if (!check_args_pos_or(tokens, &position, &orientation))
		return (0);
	if (ft_atof(tokens[3]) <= 0)
		return (printf("Cylinder diameter must be positive\n"), 0);
	if (ft_atof(tokens[4]) <= 0)
		return (printf("Cylinder height must be positive\n"), 0);
	rgb = parse_rgb(tokens[5]);
	if (!rgb)
		return (0);
	cyl = malloc(sizeof(t_cylinder));
	cyl->height = ft_atof(tokens[4]);
	cyl->diameter = ft_atof(tokens[3]);
	add_cyl(cyl, position, orientation, rgb);
	return (free_array(rgb),
		ft_lstadd_back(&scene->cylinders, ft_lstnew(cyl)), 1);
}
