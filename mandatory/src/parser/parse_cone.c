/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellmas <lbellmas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:21:06 by aguinea           #+#    #+#             */
/*   Updated: 2026/01/16 17:24:19 by lbellmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minirt.h"

static int	print_errors(char **tokens, t_vec *position, t_vec *direction)
{
	if (num_args(tokens) < 6)
		return (printf("Cone needs 6 arguments\n"), 0);
	if (!is_valid_float(tokens[3]) || !is_valid_float(tokens[4]))
		return (printf("Invalid cone angle or height\n"), 0);
	if (!parse_vec(tokens[1], position) || !parse_vec(tokens[2], direction))
		return (printf("Invalid cone vectors\n"), 0);
	return (1);
}

static	void	ft_set_color(t_cone *cone, char **rgb)
{
	cone->color.x = (float)atoi(rgb[0]);
	cone->color.y = (float)atoi(rgb[1]);
	cone->color.z = (float)atoi(rgb[2]);
}

int	parse_cone(char **tokens, t_scene *scene)
{
	t_cone	*cone;
	char	**rgb;
	t_vec	position;
	t_vec	direction;
	int		pattern;

	if (!print_errors(tokens, &position, &direction))
		return (0);
	rgb = parse_rgb(tokens[5]);
	if (!rgb)
		return (0);
	cone = malloc(sizeof(t_cone));
	if (!cone)
		return (free_array(rgb), 0);
	cone->position = position;
	cone->direction = direction;
	cone->angle = ft_atof(tokens[3]);
	cone->height = ft_atof(tokens[4]);
	ft_set_color(cone, rgb);
	pattern = parse_bonus(tokens, "cones");
	if (pattern == -1)
		return (free_array(rgb), ft_lstadd_back(&scene->cones,
				ft_lstnew(cone)), 0);
	cone->pattern = pattern;
	return (free_array(rgb), ft_lstadd_back(&scene->cones, ft_lstnew(cone)), 1);
}
