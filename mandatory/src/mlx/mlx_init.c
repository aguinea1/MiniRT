/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 02:52:14 by aguinea           #+#    #+#             */
/*   Updated: 2025/06/18 14:26:52 by lbellmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minirt.h"

void	close_window(t_mlx *mlx)
{
	if (mlx->init)
	{
		mlx_terminate(mlx->init);
		mlx->init = NULL;
	}
}

int	init_mlx(t_mlx *mlx)
{
	mlx->window_width = WIDTH;
	mlx->window_height = HEIGHT;
	mlx->init = mlx_init(mlx->window_width, mlx->window_height, "MiniRT", true);
	if (!mlx->init)
		return (printf("It's not possible to initialize the mlx\n"), 0);
	return (1);
}

int	create_new_images(t_mlx *mlx)
{
	int	mini_width;
	int	mini_height;

	mini_width = 4480;
	mini_height = 2520;
	mlx->image = mlx_new_image(mlx->init,
			mlx->window_width, mlx->window_height);
	printf ("window: %d, %d\n", mlx->window_width, mlx->window_height);
	if (!mlx->image)
		return (printf("It's not possible to generate new image\n"),
			close_window(mlx), 0);
	mlx->mini_image = mlx_new_image(mlx->init, mini_width, mini_height);
	if (!mlx->mini_image)
		return (printf("It's not possible to generate new mini_image\n"),
			close_window(mlx), 0);
	return (1);
}

int	put_image_to_window(t_mlx *mlx)
{
	if (mlx_image_to_window(mlx->init, mlx->image, 0, 0) == -1)
		return (printf("It's not possible to put new image to window\n"),
			close_window(mlx), 0);
	if (mlx_image_to_window(mlx->init, mlx->mini_image, 15, 15) == -1)
		return (printf("It's not possible to put new image to window\n"),
			close_window(mlx), 0);
	return (1);
}
