/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_render_scene.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 11:26:56 by aguinea           #+#    #+#             */
/*   Updated: 2025/07/08 13:28:43 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minirt.h"

void	space_viewport(t_scene *scene, double *viewport, t_vec	*ref, t_vec *v)
{
	v[0] = vec_scale(ref[1], 2 * viewport[1]);
	v[1] = vec_scale(ref[2], 2 * viewport[0]);
	v[2] = vec_sub(vec_sub(vec_sub(scene->camera.position,vec_scale
				(v[0], 0.5)), vec_scale(v[1], 0.5)), ref[0]);
}

void	viewport_calc(t_scene *scene, double *viewport)
{
	double	aspect_ratio;
    double	theta;
    double	half_height;
    double	half_width;

	aspect_ratio = (double)WIDTH / (double)HEIGHT;
	theta = scene->camera.fov * M_PI / 180.0;
	half_height = tan(theta / 2);
	half_width = aspect_ratio * half_height;
	viewport[0] = half_height;
	viewport[1] = half_width;
}

void	camera_ref(t_scene	*scene, t_vec *ref)
{
	ref[0] = vec_normalize(vec_scale(scene->camera.orientation, -1));
	ref[1] = vec_normalize(vec_cross(vec(0, 1, 0), ref[0]));
	ref[2] = vec_cross(ref[0], ref[1]);
}


