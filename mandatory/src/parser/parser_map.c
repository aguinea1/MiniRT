/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:46:18 by aguinea           #+#    #+#             */
/*   Updated: 2025/06/11 21:34:28 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minirt.h"

static int	parse_line(char *line, t_scene *scene)
{
	char	**tokens;

	if (line[0] == '#' || line[0] == '\0')
		return (1);
	tokens = ft_split(line, " \t");
	if (!tokens)
		return (printf("split failed\n"), 0);
	if (ft_strcmp(tokens[0], "A") == 0)
		return (parse_ambient(tokens, scene), free_array(tokens), 1);
	else if (ft_strcmp(tokens[0], "C") == 0)
		return (parse_camera(tokens, scene), free_array(tokens), 1);
	else if (ft_strcmp(tokens[0], "L") == 0)
		return (parse_light(tokens, scene), free_array(tokens), 1);
	else if (ft_strcmp(tokens[0], "sp") == 0)
		return (parse_sphere(tokens, scene), free_array(tokens), 1);
	else if (ft_strcmp(tokens[0], "pl") == 0)
		return (parse_plane(tokens, scene), free_array(tokens), 1);
	else if (ft_strcmp(tokens[0], "cy") == 0)
		return (parse_cylinder(tokens, scene), free_array(tokens), 1);
	else
		printf("Error: Unknown identifier '%s'\n", tokens[0]);
	return (free_array(tokens), 0);
}

static int	parse_get_line(int fd, t_scene *scene)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		if (!parse_line(line, scene))
			return (0);
		free(line);
		line = get_next_line(fd);
	}
	return (close(fd), 1);
}

int	parser_map(char *file, t_scene *scene)
{
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (printf("open failed\n"), 0);
	if (parse_line(fd, scene))
		return (1);
	return (0);
}
