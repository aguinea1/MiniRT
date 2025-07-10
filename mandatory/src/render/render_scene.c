/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 13:00:22 by aguinea           #+#    #+#             */
/*   Updated: 2025/07/10 17:50:11 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minirt.h"

static void	rgb_to_putpixel(t_thread_data *th, double *st, int	*rgb)
{
	t_vec	dir;
	t_vec	color;

	dir = vec_sub(vec_add(vec_add(th->views[2], vec_scale(th->views[0], st[0])),
				vec_scale(th->views[1], st[1])), th->scene->camera.position);
	dir = vec_normalize(dir);
	color = ray_color(dir, th->scene);
	rgb[0] = (int)(fmin(color.x, 1.0) * 255.999);
	rgb[1] = (int)(fmin(color.y, 1.0) * 255.999);
	rgb[2] = (int)(fmin(color.z, 1.0) * 255.999);
}

void	*render_loop(void *data)
{
	int				i;
	int				j;
	double			st[2];
	t_thread_data	*th;
	int				rgb[3];

	th = (t_thread_data *)data;
	j = th->y_start;
	while (j++ < th->y_end)
	{
		i = 0;
		while (i++ < WIDTH)
		{
			st[0] = (double)i / (WIDTH - 1);
			st[1] = (double)(HEIGHT - j - 1) / (HEIGHT - 1);
			rgb_to_putpixel(th, st, rgb);
			put_pixel(th->mlx, i, j, rgb);
		}
	}
	return (NULL);
}

void	calc_rays(t_mlx *mlx, t_scene *scene)
{
	double			viewport[2];
	t_vec			ref[3];
	t_vec			view_space[3];

	camera_ref(scene, ref);
	viewport_calc(scene, viewport);
	space_viewport(scene, viewport, ref, view_space);
	create_threads(scene, view_space, mlx);
	mlx_image_to_window(mlx->init, mlx->image, 0, 0);
}
