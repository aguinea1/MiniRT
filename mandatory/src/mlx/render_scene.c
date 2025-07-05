/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 13:00:22 by aguinea           #+#    #+#             */
/*   Updated: 2025/07/05 14:53:43 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minirt.h"

static t_vec vec(double x, double y, double z);

static t_vec vec_scale(t_vec v, double scalar)
{
    t_vec result;
    result.x = v.x * scalar;
    result.y = v.y * scalar;
    result.z = v.z * scalar;
    return result;
}
static t_vec vec(double x, double y, double z) {
    t_vec result;
    result.x = x;
    result.y = y;
    result.z = z;
    return result;
}
static t_vec vec_normalize(t_vec v) {
    double len = vec_length(v);
    if (len == 0)
        return vec(0, 0, 0);  // evitar división por 0
    return vec(v.x / len, v.y / len, v.z / len);
}

static t_vec ray_color(t_ray r) {
    // Normaliza dirección del rayo
    t_vec unit_direction = vec_normalize(r.direction);

    // Escala y para obtener valor t entre 0.0 (suelo) y 1.0 (cielo)
    double t = 0.5 * (unit_direction.y + 1.0);

    // Interpolación lineal: mezcla entre blanco y azul
    t_vec white = (t_vec){1.0, 1.0, 1.0};   // RGB: blanco
    t_vec blue = (t_vec){0.5, 0.7, 1.0};    // RGB: azul cielo

    t_vec result;
    result.x = (1.0 - t) * white.x + t * blue.x;
    result.y = (1.0 - t) * white.y + t * blue.y;
    result.z = (1.0 - t) * white.z + t * blue.z;

    return result;
}

static void put_pixel(t_mlx *mlx, int x, int y, int r, int g, int b)
{
	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return;
    unsigned char *pixel = &mlx->image->pixels[(y * WIDTH + x) * 4];
    pixel[0] = b;
    pixel[1] = g;
    pixel[2] = r;
    pixel[3] = 255; // alpha
}
void	calc_rays(t_mlx *mlx, t_scene *scene)
{/*
	t_vec	a(x);
	t_vec	b(z);
	t_vec	c(y);
	t_vec	up(0, 1, 0);;

	a(x) = vec_normalize(vec_scale(scene->camera.orientation, -1));
	b(z) = vec_normalize(vec_cross(up, a(x)));
	c(y) = vec_cross(a(x), b(z));*/
	// Paso 1: Calcula el sistema de referencia de la cámara
	scene = NULL;
  // Valores de cámara
    t_vec cam_pos = vec(0, 0, 0);
    t_vec cam_dir = vec(0, 0, -1); // mirando hacia -Z
    t_vec up = vec(0, 1, 0);       // arriba del mundo
    double fov = 90.0;

    // Paso 1: Sistema de referencia de la cámara
    t_vec w = vec_normalize(vec_scale(cam_dir, -1));
    t_vec u = vec_normalize(vec_cross(up, w));
    t_vec v = vec_cross(w, u);

    // Paso 2: Tamaño del viewport
    double aspect_ratio = (double)WIDTH / (double)HEIGHT;
    double theta = fov * M_PI / 180.0;
    double half_height = tan(theta / 2);
    double half_width = aspect_ratio * half_height;

    // Paso 3: viewport en el espacio
    t_vec horizontal = vec_scale(u, 2 * half_width);
    t_vec vertical = vec_scale(v, 2 * half_height);
    t_vec lower_left_corner = vec_sub(
        vec_sub(
            vec_sub(cam_pos, vec_scale(horizontal, 0.5)),
            vec_scale(vertical, 0.5)
        ),
        w
    );

    // Render loop (puedes conectar esto a minilibx si quieres)
    for (int j = 0; j < HEIGHT; ++j) {
        for (int i = 0; i < WIDTH; ++i) {
            double s = (double)i / (WIDTH - 1);
            double t = (double)(HEIGHT - j - 1) / (HEIGHT - 1);
            t_vec dir = vec_sub(
                vec_add(
                    vec_add(lower_left_corner, vec_scale(horizontal, s)),
                    vec_scale(vertical, t)
                ),
                cam_pos
            );
            dir = vec_normalize(dir);
            t_ray r = {cam_pos, dir};
            t_vec color = ray_color(r);

            // Aquí podrías guardar el color en un buffer o usar minilibx
            // Ejemplo: print RGB
            int rr = (int)(255.999 * color.x);
            int gg = (int)(255.999 * color.y);
            int bb = (int)(255.999 * color.z);

            put_pixel(mlx,i, j, rr, gg, bb);
        }
    }
    mlx_image_to_window(mlx->init, mlx->image, 0, 0);
}

