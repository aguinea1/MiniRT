/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:21:23 by aguinea           #+#    #+#             */
/*   Updated: 2025/07/16 13:25:19 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minirt.h"
//pa q sepas lo q falta mas o menos
//1.parseo mal(intentare arreglarlo)
//2.cono
//3.plano
//4.comprobar si funcionan bien mas de una luz
//5. todo el bonus(tres texturas diferentes creo)
//6. yo le meteria zoom
//7. tambien le meteria q al apretar y arrastrar el raton pudieramos mover el POV(pero bueno quiza es porro)
//8. arreglar makefile, hace relink y el del libft tambn(intentare arreglarlo)
//9. normi(probablemente tu parte q eres un puto terrorista)
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
