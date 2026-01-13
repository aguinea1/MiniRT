/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_backandmore.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellmas <lbellmas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 15:17:05 by aguinea           #+#    #+#             */
/*   Updated: 2026/01/13 21:23:52 by lbellmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minirt.h"

t_vec	ray_back(t_ray ray)
{
	t_vec	background[2];
	double	t;

	t = 0.5 * (ray.direction.y + 1.0);
	background[0] = vec(1, 1, 1);
	background[1] = vec(0.5, 0.7, 1);
	return (vec_add(vec_scale(background[0], 1.0 - t),
			vec_scale(background[1], t)));
}

t_vec	reflect(t_vec L, t_vec N)
{
	return (vec_sub(L, vec_scale(N, 2 * vec_dot(L, N))));
}

t_vec	calculate_specular(t_hit hit, t_light *light, t_scene *scene)
{
	t_vec	lvr[3];
	double	spec;
	t_vec	light_color;

	lvr[0] = vec_normalize(vec_sub(light->position, hit.point));
	lvr[1] = vec_normalize(vec_sub(scene->camera.position, hit.point));
	lvr[2] = reflect(vec_scale(lvr[0], -1), hit.normal);
	spec = pow(fmax(vec_dot(lvr[2], lvr[1]), 0.0), hit.shininess);
	light_color = vec_scale(light->color, light->brightness);
	return (vec_scale(light_color, spec * hit.ks));
}

t_vec	light_loop(t_scene *scene, t_hit hit, t_vec color)
{
	t_vec	total_light;
	t_list	*curr;
	t_light	*light;
	t_vec	light_contrib;
	t_vec	ambient_plus_current;
	t_vec	specular;

	total_light = vec(0, 0, 0);
	specular = vec(0, 0, 0);
	curr = scene->light;
	while (curr)
	{
		light = (t_light *)curr->content;
		light_contrib = calculate_light(hit, light, scene);
		specular = vec_add(specular, calculate_specular(hit, light, scene));
		ambient_plus_current = vec_add(color, total_light);
		if (light_contrib.x > ambient_plus_current.x)
			total_light.x += light_contrib.x - ambient_plus_current.x;
		if (light_contrib.y > ambient_plus_current.y)
			total_light.y += light_contrib.y - ambient_plus_current.y;
		if (light_contrib.z > ambient_plus_current.z)
			total_light.z += light_contrib.z - ambient_plus_current.z;
		curr = curr->next;
	}
	return (vec_add(vec_add(color, total_light), specular));
}

double	calculate_lightdir(t_hit hit, t_ray *shadow_ray, t_light *light)
{
	t_vec	light_dir;

	light_dir = vec_sub(light->position, hit.point);
	shadow_ray->direction = vec_normalize(light_dir);
	return (vec_length(light_dir));
}
