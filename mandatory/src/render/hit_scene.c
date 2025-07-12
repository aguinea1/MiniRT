/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 12:37:13 by aguinea           #+#    #+#             */
/*   Updated: 2025/07/12 19:56:26 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minirt.h"

static t_hit	find_closest_hit(t_ray ray, t_scene *scene)
{
	t_hit	sphere;
	t_hit	cyl;

	sphere = find_closest_sphere(ray, scene->spheres);
	cyl = find_closest_cylinder(ray, scene->cylinders);
	if (!sphere.hit && cyl.hit)
		return (cyl);
	if (sphere.hit && (!cyl.hit || sphere.t < cyl.t))
		return (sphere);
	return (cyl);
}
static t_vec	calculate_light(t_hit hit, t_light *light, t_scene *scene)
{
	t_vec	light_dir;
	t_vec	diffuse;
	t_vec	light_color;
	t_ray	shadow_ray;
	t_hit	shadow_hit;
	float	diff_intensity;
	float	light_distance;

	light_dir = vec_sub(light->position, hit.point);
	light_distance = vec_length(light_dir);
	light_dir = vec_normalize(light_dir);

	shadow_ray.origin = vec_add(hit.point, vec_scale(hit.normal, 0.001));
	shadow_ray.direction = light_dir;
	shadow_hit = find_closest_hit(shadow_ray, scene);

	if (shadow_hit.hit && shadow_hit.t < light_distance)
		return ((t_vec){0, 0, 0});

	diff_intensity = fmax(vec_dot(hit.normal, light_dir), 0.0);
	light_color = vec_scale(light->color, light->brightness);
	diffuse = vec_mul(vec_scale(hit.color, diff_intensity), light_color);

	return (diffuse);
}

t_vec ray_color(t_vec dir, t_scene *scene)
{
    t_ray ray;
    t_hit hit;
    t_vec color = vec(0,0,0);
    t_vec ambient;
    //int i;

    ray.origin = scene->camera.position;
    ray.direction = vec_normalize(dir);

    hit = find_closest_hit(ray, scene);
    if (!hit.hit)
    {
        double t = 0.5 * (ray.direction.y + 1.0);
        t_vec background[2] = {(t_vec){1.0,1.0,1.0}, (t_vec){0.5,0.7,1.0}};
        return vec_add(vec_scale(background[0], 1.0 - t), vec_scale(background[1], t));
    }
    ambient = vec_scale(scene->ambient.color, scene->ambient.ratio);
    color = vec_mul(hit.color, ambient);
    //t_light *curr_light = &scene->light;
   // while (curr_light)
   // {
	//	t_light *light = curr_light;
		t_vec light_contrib = calculate_light(hit, &scene->light, scene);
		color = vec_add(color, light_contrib);
	//	curr_light = curr_light->next;
//    }
    return (color);
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
