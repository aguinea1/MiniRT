/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:21:23 by aguinea           #+#    #+#             */
/*   Updated: 2025/07/15 12:07:04 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minirt.h"

static t_scene	scene_init(void)
{
	t_scene	scene;

	scene.spheres = NULL;
	scene.planes = NULL;
	scene.cylinders = NULL;
	return (scene);
}

int	main(int ac, char **av)
{
	t_scene	scene;

	if (ac == 2)
	{
		scene = scene_init();
		if (parser(av, &scene))
			run_mlx(&scene);
		free_all(&scene.cylinders, &scene.planes, &scene.spheres, &scene.light);
	}
	else
		write (1, "invalid args\n", 13);
	return (0);
}
