/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 18:51:35 by aguinea           #+#    #+#             */
/*   Updated: 2025/07/15 16:45:56 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minirt.h"

static int	setup_ambient(t_scene *scene)
{
	if (scene->ambient.ratio < 0.0 || scene->ambient.ratio > 1.0)
		return (printf("Error: Ambient intensity must be between 0 and 1\n"),
			0);
	scene->ambient.color.x = fmin(fmax(scene->ambient.color.x, 0.0), 1.0);
	scene->ambient.color.y = fmin(fmax(scene->ambient.color.y, 0.0), 1.0);
	scene->ambient.color.z = fmin(fmax(scene->ambient.color.z, 0.0), 1.0);
	return (1);
}

static void	setup_lights(t_scene *scene)
{
	t_list	*curr;
	t_light	*light;

	curr = scene->light;
	while (curr)
	{
		light = (t_light *)curr->content;
		if (light->color.x > 1.0f || light->color.y > 1.0f
			|| light->color.z > 1.0f)
		{
			light->color.x /= 255.0f;
			light->color.y /= 255.0f;
			light->color.z /= 255.0f;
		}
		if (light->brightness < 0.0f)
			light->brightness = 0.0f;
		else if (light->brightness > 1.0f)
			light->brightness = 1.0f;
		curr = curr->next;
	}
}

int	setup_scene(t_scene *scene)
{
	if (!setup_ambient(scene))
		return (0);
	setup_lights(scene);
	return (1);
}
