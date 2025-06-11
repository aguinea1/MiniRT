/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:32:35 by aguinea           #+#    #+#             */
/*   Updated: 2025/06/11 21:33:34 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minirt.h"

static int	file_name(char **av)
{
	int	i;

	i = 0;
	while (av[1][i])
		i++;
	if (i > 3)
	{
		i -= 3;
		if ((av[1][i] == ".") && (av[1][i + 1] == "r") && (av[1][i + 2] == "t"))
			return (1);
	}
	return (0);
}

int	parser(char **av, t_scene *scene)
{
	if (file_name(av) && parser_map(av[1], scene))
		return (1);
	return (0);
}
