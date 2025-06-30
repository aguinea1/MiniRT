/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:23:32 by aguinea           #+#    #+#             */
/*   Updated: 2025/06/18 14:19:56 by lbellmas         ###   ########.fr       */
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
# include "../../libs/libft/libft.h"
# include "../../libs/MLX42/include/MLX42/MLX42.h"
# define WIDTH 4480
# define HEIGHT 2520

//STRUCTS
typedef struct s_vec
{
	float	x;
	float	y;
	float	z;
}	t_vec;

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
	t_vec	center;
	float	diameter;
	t_vec	color;
}	t_sphere;

typedef struct s_plane
{
	t_vec	position;
	t_vec	normal;
	t_vec	color;
}	t_plane;

typedef struct s_cylinder
{
	t_vec	position;
	t_vec	orientation;
	float	diameter;
	float	height;
	t_vec	color;
}	t_cylinder;

typedef struct s_scene
{
	t_ambient	ambient;
	t_camera	camera;
	t_light		light;
	t_list		*spheres;
	t_list		*planes;
	t_list		*cylinders;
}	t_scene;

typedef struct s_mlx
{
	mlx_t		*init;
	int			window_height;
	int			window_width;
	mlx_image_t	*image;
	mlx_image_t	*mini_image;

}				t_mlx;

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

//UTILS
void	free_array(char **array);
int		is_valid_float(const char *str);
float	ft_atof(const char *str);
int		is_valid_rgb_value(char *str);
int		vec_is_normalized(t_vec v);
int		num_args(char **arr);
char	**ft_split1(char const *s, char c);

//MLX
int		run_mlx(void);
int		init_mlx(t_mlx *mlx);
int		create_new_images(t_mlx *mlx);
int		put_image_to_window(t_mlx *mlx);
void	close_window(t_mlx *mlx);
void	key_call(mlx_key_data_t keydata, void *param);

//FINISH
void	free_all(t_list **cyl, t_list **plane, t_list **sphere);
#endif
