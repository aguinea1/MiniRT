/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:46:18 by aguinea           #+#    #+#             */
/*   Updated: 2025/06/30 18:30:56 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minirt.h"

static int	tab_for_space(char *line)
{
	int	i;

	i = 0;
	if (line[0] == '#' || line[0] == '\0')
		return (0);
	while (line[i])
	{
		if (line[i] == '\t')
			line[i] = ' ';
		i++;
	}
	return (1);
}

static int	parse_line_bonus(t_scene *scene, int ret, char **tokens)
{
	if (ft_strcmp(tokens[0], "co") == 0)
		ret = parse_cone(tokens, scene);
	else if (ret == -1)
		printf("Error: Unknown identifier '%s'\n", tokens[0]);
	return (ret);
}

static int	parse_line(char *line, t_scene *scene)
{
	char	**tokens;
	int		ret;

	ret = -1;
	if (!tab_for_space(line))
		return (1);
	tokens = ft_split1(line, ' ');
	if (!tokens)
		return (printf("split failed\n"), 0);
	if (ft_strcmp(tokens[0], "A") == 0)
		ret = parse_ambient(tokens, scene);
	else if (ft_strcmp(tokens[0], "C") == 0)
		ret = parse_camera(tokens, scene);
	else if (ft_strcmp(tokens[0], "L") == 0)
		ret = parse_light(tokens, scene);
	else if (ft_strcmp(tokens[0], "sp") == 0)
		ret = parse_sphere(tokens, scene);
	else if (ft_strcmp(tokens[0], "pl") == 0)
		ret = parse_plane(tokens, scene);
	else if (ft_strcmp(tokens[0], "cy") == 0)
		ret = parse_cylinder(tokens, scene);
	ret = parse_line_bonus(scene, ret, tokens);
	return (free_array(tokens), ret);
}

static int	parse_get_line(int fd, t_scene *scene)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		if (!parse_line(line, scene))
			return (free(line), 0);
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
	if (parse_get_line(fd, scene))
		return (1);
	return (0);
}
