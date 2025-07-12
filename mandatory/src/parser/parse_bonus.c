/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:59:45 by aguinea           #+#    #+#             */
/*   Updated: 2025/07/11 18:42:56 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minirt.h"

static int	which_is(char *figure)
{
	if (ft_strcmp(figure, "cyl") == 0)
		return (6);
	else if (ft_strcmp(figure, "plane") == 0)
		return (4);
	else if (ft_strcmp(figure, "cone") == 0)
		return (6);
	return (4);
}

int	parse_bonus(char **tokens, char *figure)
{
	int	pattern;
	int	i;
	int	max;

	pattern = 0;
	i = which_is(figure);
	max = i + 3;
	while (tokens[i])
	{
		if (ft_strcmp(tokens[i], CHECKER_P) == 0)
			pattern |= 1 << 0;
		else if (ft_strcmp(tokens[i], STRIPE_P) == 0)
			pattern |= 1 << 1;
		else if (ft_strcmp(tokens[i], NOISE_P) == 0)
			pattern |= 1 << 2;
		else if (tokens[i][0] != ' ' && tokens[i][0] != '\t')
			return (printf("Warning: Unknown pattern '%s'\n", tokens[i]), -1);
		if (i == max)
			return (printf("Warning: More than three patterns\n"), -1);
		i++;
	}
	return (pattern);
}
