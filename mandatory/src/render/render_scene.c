/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 13:00:22 by aguinea           #+#    #+#             */
/*   Updated: 2025/07/08 13:37:23 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minirt.h"

t_vec ray_color(t_vec dir, t_scene *scene) 
{
    t_vec unit_direction;
	t_ray	ray;

	ray.origin = scene->camera.position;
	ray.direction = dir;
	unit_direction = vec_normalize(ray.direction);
    // Escala y para obtener valor t entre 0.0 (suelo) y 1.0 (cielo)
    double t = 0.5 * (unit_direction.y + 1.0);

    // Interpolación lineal: mezcla entre blanco y azul
    t_vec white = (t_vec){1.0, 1.0, 1.0};   // RGB: blanco
	t_vec blue = (t_vec){1.0, 0.5, 0.0};
    t_vec result;
    result.x = (1.0 - t) * white.x + t * blue.x;
    result.y = (1.0 - t) * white.y + t * blue.y;
    result.z = (1.0 - t) * white.z + t * blue.z;

    return result;
}

void put_pixel(t_mlx *mlx, int x, int y, int r, int g, int b)
{
	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return;
    unsigned char *pixel = &mlx->image->pixels[(y * WIDTH + x) * 4];
    pixel[0] = b;
    pixel[1] = g;
    pixel[2] = r;
    pixel[3] = 255; // alpha
}

void	render_loop(t_scene *scene, t_vec *views, t_mlx *mlx)
{
	int		i;
	int		j;
	double	st[2];
	t_vec	dir;
	t_vec	color;

	j = 0;
	while (++j < HEIGHT) 
	{
		i = 0;
		while (++i < WIDTH) 
		{
			st[0] = (double)i / (WIDTH - 1);
			st[1] = (double)(HEIGHT - j - 1) / (HEIGHT - 1);
			dir = vec_sub(vec_add(vec_add(views[2], vec_scale(views[0], st[0])),
					vec_scale(views[1], st[1])),scene->camera.position);
			dir = vec_normalize(dir);
			color = ray_color(dir, scene);
			// Aqui va el calculo de las figuras
			put_pixel(mlx,i, j, rr, gg, bb);
		}
	}
}

void	calc_rays(t_mlx *mlx, t_scene *scene)
{
	double	viewport[2];
	t_vec	ref[3];
	t_vec	view_space[3];

	camera_ref(scene, ref);
	viewport_calc(scene, viewport);
	space_viewport(scene, viewport, ref, view_space);
	render_loop(scene, view_space, mlx);
    mlx_image_to_window(mlx->init, mlx->image, 0, 0);
}

