/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:23:32 by aguinea           #+#    #+#             */
/*   Updated: 2025/06/11 21:44:45 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include "libft.h"

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

typedef struct s_scene
{
	t_ambient	ambient;
	t_camera	camera;
	t_light		light;
	t_list		*spheres;
	t_list		*planes;
	t_list		*cylinders;
}	t_scene;

//PARSER
int		parser(char **av);
int		parser_map(char *file);

//UTILS
void	free_array(char **array);
int		is_valid_float(const char *str);
#endif
