/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 16:01:28 by aguinea           #+#    #+#             */
/*   Updated: 2025/07/21 16:11:42 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minirt.h"

static void	out_new_line(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == '\n' || line[i] == '\r')
		{
			line[i] = '\0';
			break ;
		}
	}
}

int	tab_for_space(char *line)
{
	int	i;

	if (!line || line[0] == '#' || line[0] == '\0')
		return (0);
	i = 0;
	while (line[i])
	{
		if (line[i] == '#')
		{
			line[i] = '\0';
			break ;
		}
		else if (line[i] == '\t')
			line[i] = ' ';
		i++;
	}
	out_new_line(line);
	return (1);
}
