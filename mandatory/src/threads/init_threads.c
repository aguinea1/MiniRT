/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:51:46 by aguinea           #+#    #+#             */
/*   Updated: 2025/07/08 16:59:02 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minirt.h"

void	init_th_struct(t_scene *scene, t_vec *views, t_mlx *mlx, int *coor, t_thread_data *th)
{
	th->scene = scene;
	th->views = views;
	th->mlx = mlx;
	th->y_start = coor[0];
	th->y_end = coor[1];
}

