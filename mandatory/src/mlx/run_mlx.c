/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_mlx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 03:01:55 by aguinea           #+#    #+#             */
/*   Updated: 2025/06/30 14:59:46 by lbellmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minirt.h"
/*
void	ft_rayos(t_mlx *mlx, t_scene *scene)
{
	t_vec	cam_vec;

	cam_vec.x = scene->camera.orientation.x - scene->camera.position.x;
	cam_vec.y = scene->camera.orientation.y - scene->camera.position.y;
	cam_vec.z = scene->camera.orientation.z - scene->camera.position.z;
	//calcular 4 rayos maximos (altura maxima, altura minima, derecha e izquierda)
	//con la posicion de la camra y su vision hay que volver a hacer los ejes EJ:
	//x = x * 0,1 + y * 0,5 + z * 0,4
	//luego para saber si ese pixel hay que pintarlo cada objeto lo pasamos a 2d 
	//cuando todos los objetos estan en 2d tiramos ayo por rayo y miramos que hay que pintar en cada pixel
	//
}*/

void	key_call(mlx_key_data_t keydata, void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		close_window(mlx);
		exit(0);
	}
}

int	run_mlx(void)//t_scene *scene)
{
	t_mlx	mlx;

	if (!init_mlx(&mlx))
		return (1);
	if (!create_new_images(&mlx))
		return (mlx_terminate(mlx.init), 1);
	if (!put_image_to_window(&mlx))
		return (mlx_terminate(mlx.init), 1);
	mlx_key_hook(mlx.init, key_call, &mlx);
//	ft_rayos(&mlx, scene);
	mlx_loop(mlx.init);
	mlx_delete_image(mlx.init, mlx.image);
	mlx_terminate(mlx.init);
	return (0);
}
