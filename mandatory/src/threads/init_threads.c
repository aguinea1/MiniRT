/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:51:46 by aguinea           #+#    #+#             */
/*   Updated: 2025/07/10 17:50:38 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minirt.h"

static void	init_th_struct(t_scene *scene, t_vec *views, t_mlx *mlx,
		t_thread_data *th)
{
	th->scene = scene;
	th->views = views;
	th->mlx = mlx;
}

static void	init_th_part2(t_thread_data *th, int *coor)
{
	th->y_start = coor[0];
	th->y_end = coor[1];
}

void	create_threads(t_scene *scene, t_vec *views, t_mlx *mlx)
{
	pthread_t		threads[THREADS];
	t_thread_data	th[THREADS];
	int				thread_lines;
	int				i;
	int				coor[2];

	i = -1;
	thread_lines = HEIGHT / THREADS;
	while (++i < THREADS)
	{
		coor[0] = i * thread_lines;
		if (i + 1 == THREADS)
			coor[1] = HEIGHT;
		else
			coor[1] = coor[0] + thread_lines;
		init_th_struct(scene, views, mlx, &th[i]);
		init_th_part2(&th[i], coor);
		pthread_create(&threads[i], NULL, render_loop, (void *)&th[i]);
	}
	i = 0;
	while (i < THREADS)
		pthread_join(threads[i++], NULL);
}
