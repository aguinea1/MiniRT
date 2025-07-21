/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:21:23 by aguinea           #+#    #+#             */
/*   Updated: 2025/07/21 22:01:54 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minirt.h"

//pa q sepas lo q falta mas o menos
//1.cono
//2.plano
//3. todo el bonus(tres texturas diferentes creo)
//4. yo le meteria zoom
//5. tambien le meteria q al apretar y arrastrar el raton
//pudieramos mover el POV(pero bueno quiza es porro)
//6. normi(probablemente tu parte q eres un puto terrorista)

static t_scene	scene_init(void)
{
	t_scene	scene;

	scene.spheres = NULL;
	scene.planes = NULL;
	scene.cylinders = NULL;
	scene.light = NULL;
	return (scene);
}

int	main(int ac, char **av)
{
	t_scene	scene;
	int		parse;

	if (ac == 2)
	{
		scene = scene_init();
		parse = parser(av, &scene);
		if (parse == 1)
			run_mlx(&scene);
		if (parse != 2)
			free_all(&scene.cylinders, &scene.planes,
				&scene.spheres, &scene.light);
		else
			write (1, "Invalid doc\n", 13);
	}
	else
		write (1, "invalid args\n", 13);
	return (0);
}
