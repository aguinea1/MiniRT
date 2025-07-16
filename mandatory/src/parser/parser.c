/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:32:35 by aguinea           #+#    #+#             */
/*   Updated: 2025/07/16 13:19:39 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minirt.h"
//el peor parseo de la historia, ns si me dara tiempo a hacerlo bien pero bueno pa q lo sepas si quieres probar en un .rt prueba como en el q te he dejado de ejmplo(ejemplo.rt)
static int	file_name(char **av)
{
	int	i;

	i = 0;
	while (av[1][i])
		i++;
	if (i >= 3)
	{
		if (av[1][i - 3] == '.' &&
			av[1][i - 2] == 'r' &&
			av[1][i - 1] == 't')
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
