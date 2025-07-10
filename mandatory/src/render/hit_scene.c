/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 12:37:13 by aguinea           #+#    #+#             */
/*   Updated: 2025/07/10 17:46:56 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minirt.h"

t_vec	ray_color(t_vec dir, t_scene *scene)
{
	t_ray	ray;
	t_hit	hit;
	double	t;
	t_vec	background[2];

	background[0] = (t_vec){1.0, 1.0, 1.0};
	background[1] = (t_vec){0.5, 0.7, 1.0};
	ray.origin = scene->camera.position;
	ray.direction = vec_normalize(dir);
	hit = find_closest_sphere(ray, scene->spheres);
	if (hit.hit)
		return (hit.color);
	t = 0.5 * (ray.direction.y + 1.0);
	return (vec_add(vec_scale(background[0], 1.0 - t),
			vec_scale(background[1], t)));
}

void	put_pixel(t_mlx *mlx, int x, int y, int *rgb)
{
	unsigned char	*pixel;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	pixel = &mlx->image->pixels[(y * WIDTH + x) * 4];
	pixel[0] = rgb[0];
	pixel[1] = rgb[1];
	pixel[2] = rgb[2];
	pixel[3] = 255;
}
