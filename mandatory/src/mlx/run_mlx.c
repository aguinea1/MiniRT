/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_mlx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 03:01:55 by aguinea           #+#    #+#             */
/*   Updated: 2025/06/14 04:05:41 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minirt.h"

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

int	run_mlx(void)
{
	t_mlx	mlx;

	if (!init_mlx(&mlx))
		return (1);
	if (!create_new_images(&mlx))
		return (mlx_terminate(mlx.init), 1);
	if (!put_image_to_window(&mlx))
		return (mlx_terminate(mlx.init), 1);
	mlx_key_hook(mlx.init, key_call, &mlx);
	mlx_loop(mlx.init);
	mlx_terminate(mlx.init);
	return (0);
}
