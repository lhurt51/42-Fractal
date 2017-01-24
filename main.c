/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhurt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 19:06:59 by lhurt             #+#    #+#             */
/*   Updated: 2016/12/14 19:07:13 by lhurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

void	*check_param(t_mlx *new)
{
	if (!strncmp(new->env.check, "man", 3))
		return (&thread_man);
	else if (!strncmp(new->env.check, "jul", 3))
		return (&thread_jul);
	else
		return (error());
}

void	make_threads(t_mlx *new)
{
	pthread_t	pth[THREADS];
	int			i;

	i = 0;
	while (i++ < THREADS)
	{
		pthread_create(&pth[i - 1], NULL, check_param(new), new);
		usleep(5);
	}
	i = 0;
	while (i++ < THREADS)
		pthread_join(pth[i - 1], NULL);
}

void	run_img(t_mlx *new)
{
	mlx_destroy_image(new->mlx, new->img);
	new->img = mlx_new_image(new->mlx, W_WIDTH, W_HEIGHT);
	new->data = mlx_get_data_addr(new->img, &new->bits, &new->size_line,
		&new->endian);
	if (!strncmp(new->env.check, "tree", 4))
		run_tree(new);
	else if (check_param(new) != NULL)
		make_threads(new);
	else
		exit(0);
	mlx_put_image_to_window(new->mlx, new->win, new->img, 0, 0);
}

void	run_win(t_mlx *new, char *check)
{
	new->mlx = mlx_init();
	new->win = mlx_new_window(new->mlx, W_WIDTH, W_HEIGHT, "42");
	new->img = mlx_new_image(new->mlx, W_WIDTH, W_HEIGHT);
	new->env.check = check;
	reset_struct(new);
	run_img(new);
	mlx_mouse_hook(new->win, my_mouse_func, new);
	mlx_hook(new->win, 6, 0, my_mouse_movement, new);
	mlx_hook(new->win, 2, 0, my_key_press, new);
	mlx_loop(new->mlx);
}

int		main(int argc, char **argv)
{
	t_mlx	*new;

	new = malloc(sizeof(t_mlx));
	if (!new)
		return ((int)error());
	if (argc != 2)
		return ((int)error());
	run_win(new, argv[1]);
	return (1);
}
