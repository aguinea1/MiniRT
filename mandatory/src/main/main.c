/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:21:23 by aguinea           #+#    #+#             */
/*   Updated: 2025/06/11 21:33:14 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minirt.h"

int	main(int ac, char **av)
{
	t_scene	scene;

	scene = NULL;
	if (ac == 2)
	{
		if (parsing(av, &scene))
			init_rt(av, &scene);
	}
	return (0);
}
