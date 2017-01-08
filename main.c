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

void			*error(void)
{
	ft_putendl("Error: invalid amount of parameters");
	ft_putendl("Usage: valid parameters man, jul, apo");
	return (NULL);
}

void	pixel_to_img(t_mlx *new, int x, int y, int color)
{
	int		i;

	i = (x * 4) + (y * new->size_line);
	new->data[i++] = color & 0xFF;
	new->data[i++] = (color >> 8) & 0xFF;
	new->data[i] = (color >> 16) & 0xFF;
}

void	man_depth(int *i, double c_re, double c_im, int max)
{
	double	x;
	double	y;
	double	x_new;

	x = 0;
	y = 0;
	*i = 0;
	while (x * x + y * y <= 4 && *i < max) {
		x_new = x * x - y * y + c_re;
		y = 2 * x * y + c_im;
		x = x_new;
		(*i)++;
	}
}

void	mandelbrot(t_mlx *new, int max)
{
	int		row;
	int		col;
	int		i;

	row = 0;
	while (row < W_HEIGHT) {
		col = 0;
    	while (col < W_WIDTH) {
			man_depth(&i, (col - W_WIDTH / 2.0) * 4.0 / W_WIDTH,
				(row - W_HEIGHT / 2.0) * 4.0 / W_WIDTH, max);
	        if (i < max)
				pixel_to_img(new, col, row, red_to_blue[i]);
	        else
				pixel_to_img(new, col, row, 0x000000);
			col++;
	    }
		row++;
	}
}

int		my_key_press(int keycode, t_mlx *new)
{
	if (keycode == 53)
		exit(0);
	else if (new)
		ft_putnbr(keycode);
	return (0);
}

void	run_win(t_mlx *new)
{
	new->mlx = mlx_init();
	new->win = mlx_new_window(new->mlx, W_WIDTH, W_HEIGHT, "42");
	new->img = mlx_new_image(new->mlx, W_WIDTH, W_HEIGHT);
	new->data = mlx_get_data_addr(new->img, &new->bits, &new->size_line, &new->endian);
	mandelbrot(new, 100);
	mlx_put_image_to_window(new->mlx, new->win, new->img, 0, 0);
	mlx_hook(new->win, 2, 0, my_key_press, new);
	mlx_loop(new->mlx);
}

void	check_param(t_mlx *new, char *str)
{
	if (!strncmp(str, "man", 3))
		run_win(new);
	// else if (!strncmp(str, "jul", 3))
	//
	// else if (!strncmp(str, "apo", 3))
	//
	else
		error();
}

int		main(int argc, char **argv)
{
	t_mlx	*new;
	int		i;

	i = 0;
	new = malloc(sizeof(t_mlx));
	if (!new)
		return ((int)error());
	if (argc < 2 || argc > 5)
		return ((int)error());
	while (i++ <= argc)
		check_param(new, argv[i]);
	return (1);
}
