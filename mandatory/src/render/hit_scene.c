/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellmas <lbellmas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 12:37:13 by aguinea           #+#    #+#             */
/*   Updated: 2026/01/08 18:52:24 by lbellmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minirt.h"
//en esta funcion es dnd tienes que meter las otras figuras en pln
//(find_closest_cone) y entonces ahi ya hace todos los calculos
//como en hit_cylinder o como quieras
//(y el bonus ni puta idea dnd meterlo en verdad)
static t_hit	find_closest_hit(t_ray ray, t_scene *scene)
{
	t_hit	sphere;
	t_hit	cyl;
	t_hit	nothing;
	t_hit	plane;
	t_hit	cone;

	cone = find_closest_cone(ray, scene->cones);
	plane = find_closest_plane(ray, scene->planes);
	sphere = find_closest_sphere(ray, scene->spheres);
	cyl = find_closest_cylinder(ray, scene->cylinders);
	if (sphere.hit && (!cyl.hit || sphere.t < cyl.t))
	{
		sphere.normal = vec_normalize(sphere.normal);
		if (vec_dot(ray.direction, sphere.normal) > 0)
			sphere.normal = vec_scale(sphere.normal, -1);
		return (sphere);
	}
	if (cyl.hit)
	{
		cyl.normal = vec_normalize(cyl.normal);
		if (vec_dot(ray.direction, cyl.normal) > 0)
			cyl.normal = vec_scale(cyl.normal, -1);
		return (cyl);
	}
	if (cone.hit)
		return (cone);
	if (plane.hit)
		return (plane);
	nothing.hit = 0;
	return (nothing);
}

t_vec	calculate_light(t_hit hit, t_light *light, t_scene *scene)
{
	t_vec	diffuse;
	t_vec	light_color;
	t_ray	shadow_ray;
	t_hit	shadow_hit;
	double	intensity_dist[2];

	intensity_dist[1] = calculate_lightdir(hit, &shadow_ray, light);
	shadow_ray.origin = vec_add(hit.point, vec_scale(hit.normal, 0.001));
	shadow_hit = find_closest_hit(shadow_ray, scene);
	if (shadow_hit.hit && shadow_hit.t < intensity_dist[1])
		return (vec(0, 0, 0));
	intensity_dist[0] = fmax(0.0, vec_dot(hit.normal, shadow_ray.direction));
	light_color = vec_scale(light->color, light->brightness);
	diffuse = vec_scale(vec_mul(vec_scale(hit.color, 1.0 / 255.0), light_color),
			intensity_dist[0]);
	return (diffuse);
}

t_vec	ray_color(t_vec dir, t_scene *scene)
{
	t_ray	ray;
	t_hit	hit;
	t_vec	ambient;
	t_vec	color;
	t_vec	obj_color;

	ray.origin = scene->camera.position;
	ray.direction = vec_normalize(dir);
	hit = find_closest_hit(ray, scene);
	if (vec_dot(ray.direction, hit.normal) > 0)
		hit.normal = vec_scale(hit.normal, -1);
	if (!hit.hit)
		return (ray_back(ray));
	ambient = vec_scale(scene->ambient.color, scene->ambient.ratio);
	obj_color = vec_scale(hit.color, 1.0 / 255.0);
	color = vec_mul(obj_color, ambient);
	return (light_loop(scene, hit, color));
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
