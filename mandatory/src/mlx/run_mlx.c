/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_mlx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 03:01:55 by aguinea           #+#    #+#             */
/*   Updated: 2025/07/12 18:51:26 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minirt.h"

static void	clear_image_black(mlx_image_t *img, int width, int height)
{
	int	y;
	int	x;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			mlx_put_pixel(img, x, y, 0x000000FF);
			x++;
		}
		y++;
	}
}

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

int	run_mlx(t_scene *scene)
{
	t_mlx	mlx;

	if (!init_mlx(&mlx))
		return (1);
	if (!create_new_images(&mlx))
		return (mlx_terminate(mlx.init), 1);
	if (!put_image_to_window(&mlx))
		return (mlx_terminate(mlx.init), 1);
	clear_image_black(mlx.image, mlx.window_width, mlx.window_height);
	if (!setup_scene(scene))
		return (mlx_terminate(mlx.init), 1);
	calc_rays(&mlx, scene);
	mlx_key_hook(mlx.init, key_call, &mlx);
	mlx_loop(mlx.init);
	mlx_delete_image(mlx.init, mlx.image);
	mlx_terminate(mlx.init);
	return (0);
}
