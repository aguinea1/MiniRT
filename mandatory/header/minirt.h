/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellmas <lbellmas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:23:32 by aguinea           #+#    #+#             */
/*   Updated: 2026/01/09 18:01:11 by lbellmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <ctype.h> 
# include <stdio.h>
# include <math.h>
# include <pthread.h>
# include "../../libs/libft/libft.h"
# include "../../libs/MLX42/include/MLX42/MLX42.h"
# define WIDTH 4480
# define HEIGHT 2520
# define CHECKER_P "checker"
# define STRIPE_P "stripe"
# define NOISE_P "noise"
# define BUMP_P "bump"
# define THREADS 12
# define RGB_LIGHT "Error\nRGB values must be 0–255\n"
# define M_PI 3.14159265358979323846

//STRUCTS
//lo q hay q hacer esta en el main
typedef enum e_pattern
{
	NONE,
	CHECKER,
	STRIPE,
	NOISE,
	BUMP
}	t_pattern;

typedef struct s_vec
{
	float	x;
	float	y;
	float	z;
}	t_vec;

typedef struct s_ray
{
	t_vec	origin;
	t_vec	direction;
}	t_ray;

typedef struct s_ambient
{
	float	ratio;
	t_vec	color;
}	t_ambient;

typedef struct s_camera
{
	t_vec	position;
	t_vec	orientation;
	float	fov;
}	t_camera;

typedef struct s_light
{
	t_vec	position;
	float	brightness;
	t_vec	color;
}	t_light;

typedef struct s_sphere
{
	t_vec		center;
	float		diameter;
	t_vec		color;
	t_pattern	pattern;
}	t_sphere;

typedef struct s_plane
{
	t_vec		position;
	t_vec		normal;
	t_vec		color;
	t_pattern	pattern;
}	t_plane;

typedef struct s_cyl_data
{
	t_vec	axis;
	t_vec	oc;
	t_vec	d_proj;
	t_vec	oc_proj;
	double	a;
	double	b;
	double	c;
	double	disc;
	double	sqrt_disc;
}	t_cyl_data;

typedef struct s_cylinder
{
	t_vec		position;
	t_vec		orientation;
	float		diameter;
	float		height;
	t_vec		color;
	t_pattern	pattern;
	t_cyl_data	*data;
}	t_cylinder;

typedef struct s_cone
{
	t_vec		position;
	t_vec		direction;
	float		height;
	float		angle;
	t_vec		color;
	t_pattern	pattern;
}	t_cone;

typedef struct s_scene
{
	t_ambient	ambient;
	t_camera	camera;
	t_list		*light;
	t_list		*spheres;
	t_list		*planes;
	t_list		*cylinders;
	t_list		*cones;
}	t_scene;

typedef struct s_mlx
{
	mlx_t		*init;
	int			window_height;
	int			window_width;
	mlx_image_t	*image;
	mlx_image_t	*mini_image;

}				t_mlx;

typedef struct s_hook_data
{
	t_mlx	*mlx;
	t_scene	*scene;
}	t_hook_data;

typedef struct s_thread_data
{
	t_scene	*scene;
	t_vec	*views;
	t_mlx	*mlx;
	int		y_start;
	int		y_end;
}	t_thread_data;

typedef struct s_hit
{
	double	t;
	t_vec	point;
	t_vec	normal;
	t_vec	color;
	int		hit;
	int		i;
	double	ks;
	double	shininess;
}	t_hit;

//PARSER
int		parser(char **av, t_scene *scene);
int		parser_map(char *file, t_scene *scene);
int		parse_rgb_int(char **rgb, t_scene *scene);
int		parse_camera(char **tokens, t_scene *scene);
int		parse_vec(char *str, t_vec *vec);
int		parse_light(char **tokens, t_scene *scene);
int		parse_sphere(char **tokens, t_scene *scene);
int		parse_ambient(char **tokens, t_scene *scene);
char	**parse_rgb(char *rgb1);
int		parse_plane(char **tokens, t_scene *scene);
int		parse_cylinder(char **tokens, t_scene *scene);
int		parse_bonus(char **tokens, char *figure);
int		parse_cone(char **tokens, t_scene *scene);

//UTILS
void	free_array(char **array);
int		is_valid_float(const char *str);
float	ft_atof(const char *str);
int		is_valid_rgb_value(char *str);
int		num_args(char **arr);
char	**ft_split1(char const *s, char c);
void	evaluate_token(char **tokens);
void	remove_comment(char *line);
int		tab_for_space(char *line);
void	hit_cylinder_cap(t_vec p, t_hit *hit, double t, t_vec axis);
void	center_cyl(int i, t_cylinder *cy, t_vec	axis, t_vec *center);
void	whats_t(double *t, t_cyl_data *d, int i);

//RENDER
t_vec	vec_scale(t_vec v, double scalar);
void	*render_loop(void *data);
void	calc_rays(t_mlx *mlx, t_scene *scene);
t_vec	ray_color(t_vec dir, t_scene *scene);
t_vec	vec_normalize(t_vec v);
t_vec	vec(double x, double y, double z);
t_vec	vec_scale(t_vec v, double scalar);
void	camera_ref(t_scene	*scene, t_vec *ref);
void	viewport_calc(t_scene *scene, double *viewport);
void	space_viewport(t_scene *scene, double *viewport, t_vec	*ref, t_vec *v);
void	put_pixel(t_mlx *mlx, int x, int y, int *rgb);
t_vec	ray_color(t_vec dir, t_scene *scene);
t_hit	find_closest_sphere(t_ray ray, t_list *spheres);
t_hit	hit_sphere(t_ray ray, t_sphere *sphere);
t_hit	hit_cylinder(t_ray ray, t_cylinder *cy);
t_hit	find_closest_cylinder(t_ray ray, t_list *cyls);
int		setup_scene(t_scene *scene);
t_vec	ray_back(t_ray ray);
t_vec	light_loop(t_scene *scene, t_hit hit, t_vec color);
t_vec	calculate_light(t_hit hit, t_light *light, t_scene *scene);
double	calculate_lightdir(t_hit hit, t_ray *shadow_ray, t_light *light);
t_hit	find_closest_plane(t_ray ray, t_list *list);
t_hit	find_closest_cone(t_ray ray, t_list *list);
t_hit	hit_plane(t_ray ray, t_plane *plane);
t_vec	ft_checkerboard(t_hit hit);
t_vec	ft_bump_normal(t_hit hit, double strength);

//THREADS
void	create_threads(t_scene *scene, t_vec *views, t_mlx *mlx);

//VEC OPERATIONS
t_vec	vec_cross(t_vec a, t_vec b);
t_vec	vec_add(t_vec a, t_vec b);
t_vec	vec_sub(t_vec a, t_vec b);
t_vec	vec_mult(t_vec a, double t);
double	vec_dot(t_vec a, t_vec b);
double	vec_length(t_vec v);
int		vec_is_normalized(t_vec v);
t_vec	vec_mul(t_vec a, t_vec b);

//MLX
int		run_mlx(t_scene *scene);
int		init_mlx(t_mlx *mlx);
int		create_new_images(t_mlx *mlx);
int		put_image_to_window(t_mlx *mlx);
void	close_window(t_mlx *mlx);
void	key_call(mlx_key_data_t keydata, void *param);

//FINISH
void	free_all(t_list **cyl, t_list **plane, t_list **sphere, t_list **light);
#endif
