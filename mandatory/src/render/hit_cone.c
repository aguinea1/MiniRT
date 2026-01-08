/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cone.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellmas <lbellmas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:22:22 by lbellmas          #+#    #+#             */
/*   Updated: 2026/01/08 17:56:01 by lbellmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minirt.h"

t_hit	cone_body(t_ray ray, t_cone *cone)
{
	t_hit hit;
//	t_ray local_ray;
	t_vec oc;
	double k, a, b, c, discriminant, t;
	t_vec hit_point;
//	double y;

	hit.hit = 0;

	// Dirección del cono normalizada
	t_vec cone_dir = vec_normalize(cone->direction);

	// Ángulo en radianes y su tangente al cuadrado
	double angle_rad = cone->angle * M_PI / 180.0;
	double tan2 = tan(angle_rad);
	tan2 *= tan2;

	// Vector desde el vértice del cono al origen del rayo
	oc = vec_sub(ray.origin, cone->position);

	// Proyecciones para el cuerpo del cono (más matemático)
	k = 1 + tan2;

	double dv = vec_dot(ray.direction, cone_dir);
	double ov = vec_dot(oc, cone_dir);

	a = vec_dot(ray.direction, ray.direction) - k * dv * dv;
	b = 2 * (vec_dot(ray.direction, oc) - k * dv * ov);
	c = vec_dot(oc, oc) - k * ov * ov;

	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (hit);

	// Obtener el menor t positivo
	double sqrt_d = sqrt(discriminant);
	double t1 = (-b - sqrt_d) / (2 * a);
	double t2 = (-b + sqrt_d) / (2 * a);

	t = (t1 > 1e-4) ? t1 : (t2 > 1e-4 ? t2 : -1);
	if (t < 0)
		return (hit);

	hit_point = vec_add(ray.origin, vec_scale(ray.direction, t));

	// Verificar que esté dentro del límite de altura del cono
	t_vec v_to_p = vec_sub(hit_point, cone->position);
	double height = vec_dot(v_to_p, cone_dir);

	if (height < 0 || height > cone->height)
		return (hit);

	// Calcular normal del cono en el punto
	t_vec normal;
	t_vec axis_component = vec_scale(cone_dir, height);
	normal = vec_sub(v_to_p, vec_scale(axis_component, 1 + tan2));
	normal = vec_normalize(normal);

	hit.hit = 1;
	hit.t = t;
	hit.point = hit_point;
	hit.normal = normal;
	hit.color = cone->color;
	return (hit);
}

t_hit	cone_cap(t_ray ray, t_cone *cone)
{
	t_hit hit;
	t_plane cap;
	t_vec cap_center;

	hit.hit = 0;

	// El centro de la base está a lo largo de la dirección del cono, a distancia "height"
	cap.normal = vec_normalize(cone->direction);
	cap_center = vec_add(cone->position, vec_scale(cap.normal, cone->height));
	cap.position = cap_center;
	cap.color = cone->color;

	// Usamos hit_plane para verificar intersección con la tapa
	hit = hit_plane(ray, &cap);
	if (!hit.hit)
		return (hit);

	// Verificamos que esté dentro del radio
	t_vec v = vec_sub(hit.point, cap_center);
	double dist2 = vec_dot(v, v);
	double radius = cone->height * tan(cone->angle * M_PI / 180.0);

	if (dist2 > radius * radius)
		hit.hit = 0;

	return (hit);
}

t_hit	hit_cone(t_ray ray, t_cone *cone)
{
	t_hit	hit;
	t_hit	body_hit;
	t_hit	cap_hit;

	body_hit = cone_body(ray, cone);
	cap_hit = cone_cap(ray, cone);

	if (body_hit.hit && (!cap_hit.hit || body_hit.t < cap_hit.t))
		return (body_hit);
	else if (cap_hit.hit)
		return (cap_hit);

	hit.hit = 0;
	return (hit);
}

t_hit	find_closest_cone(t_ray ray, t_list *list)
{
	t_hit	closest_hit;
	t_hit	current_hit;
	t_cone	*cone;
	double	min_t;

	closest_hit.hit = 0;
	min_t = INFINITY;
	while (list)
	{
		cone = (t_cone *)list->content;
		current_hit = hit_cone(ray, cone);
		if (current_hit.hit && current_hit.t < min_t)
		{
			min_t = current_hit.t;
			closest_hit = current_hit;
		}
		list = list->next;
	}
	closest_hit.ks = 0.5;
	closest_hit.shininess = 32;
	return (closest_hit);
}

/*
t_hit	hit_cone(t_ray ray, t_cone *cone)
{
	t_hit	hit;

	cone_body(ray, cone);
	cone_cap(ray, cone);
	return (hit);
}

t_hit	find_closest_cone(t_ray ray, t_list *list)
{
	t_hit	closest_hit;
	t_hit	current_hit;
	t_cone	*cone;

	closest_hit.hit = 0;
	while (list)
	{
		cone = (t_cone *)list->content;
		current_hit = hit_cone(ray, cone);
		if (current_hit.hit)
		{

		}
		list = list->next;
	}
	return (closest_hit);
}*/
