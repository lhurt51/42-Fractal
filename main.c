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
			man_depth(&i, (col - W_WIDTH / 2.0) * 4.0 / W_WIDTH * new->scale + new->x_offset,
				(row - W_HEIGHT / 2.0) * 4.0 / W_WIDTH * new->scale + new->y_offset, max);
	        if (i < max)
				pixel_to_img(new, col, row, red_to_blue[i % 64]);
	        else
				pixel_to_img(new, col, row, 0x000000);
			col++;
	    }
		row++;
	}
}

int		julia_depth(t_mlx *new, int x, int y, int col, int row)
{
	double	newRe, newIm, oldRe, oldIm;
	double	cRe, cIm;
	int		i;

	x += y;
	cRe = -0.7;
	cIm = 0.27015;
	newRe = (col - W_WIDTH / 2.0) * 4.0 / W_WIDTH * new->scale + new->x_offset;
	newIm = (row - W_HEIGHT / 2.0) * 4.0 / W_WIDTH * new->scale + new->y_offset;
	i = 0;
	while(i < new->depth)
	{
		oldRe = newRe;
		oldIm = newIm;
		newRe = oldRe * oldRe - oldIm * oldIm + cRe;
		newIm = 2 * oldRe * oldIm + cIm;
		if((newRe * newRe + newIm * newIm) > 4)
			break;
		i++;
	}
	return (i);
}

void	julia_set(t_mlx *new, int x, int y)
{
	int	i;
	int	row;
	int	col;

	row = 0;
	while (row < W_HEIGHT)
	{
		col = 0;
		while (col < W_WIDTH)
		{
			i = julia_depth(new, x, y, col, row);
			if (i < new->depth)
				  pixel_to_img(new, col, row, red_to_blue[i % 64]);
			else
				  pixel_to_img(new, col, row, 0x000000);
			col++;
		}
		row++;
	}
}

void	run_man(t_mlx *new)
{
	new->img = mlx_new_image(new->mlx, W_WIDTH, W_HEIGHT);
	new->data = mlx_get_data_addr(new->img, &new->bits, &new->size_line, &new->endian);
	mandelbrot(new, new->depth);
	mlx_put_image_to_window(new->mlx, new->win, new->img, 0, 0);
}

void	run_jul(t_mlx *new, int x, int y)
{
	new->img = mlx_new_image(new->mlx, W_WIDTH, W_HEIGHT);
	new->data = mlx_get_data_addr(new->img, &new->bits, &new->size_line, &new->endian);
	julia_set(new, x, y);
	mlx_put_image_to_window(new->mlx, new->win, new->img, 0, 0);
}

void	zoom(t_mlx *new, int x, int y, int check)
{
	if (check > 0)
	{
		new->scale *= .92;
		new->x_offset += (x - W_XORIGIN) / (W_XORIGIN / new->scale) / 2.5;
		new->y_offset += (y - W_YORIGIN) / (W_YORIGIN / new->scale) / 2.5;
	}
	else
	{
		new->scale /= .92;
		new->x_offset -= (x - W_XORIGIN) / (W_XORIGIN / new->scale) / 2.5;
		new->y_offset -= (y - W_YORIGIN) / (W_YORIGIN / new->scale) / 2.5;
	}
	mlx_destroy_image(new->mlx, new->img);
	run_jul(new, 1, 0);
}

int		my_mouse_func(int keycode, int x, int y, t_mlx *new)
{
	static int	check = 0;

	check++;
	if (keycode == 5 && check == ZOOM_SPEED)
	{
		zoom(new, x, y, 1);
		check = 0;
	}
	else if (keycode == 4 && check == ZOOM_SPEED)
	{
		zoom(new, x, y, -1);
		check = 0;
	}
	else
	{
		ft_putnbr(keycode);
		ft_putchar('\n');
	}
	return (0);
}

void 	move_xoff(t_mlx *new, double x)
{
	new->x_offset += x;
	mlx_destroy_image(new->mlx, new->img);
	run_jul(new, 1, 0);
}

void 	move_yoff(t_mlx *new, double x)
{
	new->y_offset += x;
	mlx_destroy_image(new->mlx, new->img);
	run_jul(new, 1, 0);
}

void	change_depth(t_mlx *new, int x)
{
	if (new->depth + x > 0)
		new->depth += x;
	mlx_destroy_image(new->mlx, new->img);
	run_jul(new, 1, 0);
}

int		my_key_press(int keycode, t_mlx *new)
{
	if (keycode == 53)
		exit(0);
	else if (keycode == 123)
		move_xoff(new, -0.1);
	else if (keycode == 124)
		move_xoff(new, 0.1);
	else if (keycode == 126)
		move_yoff(new, -0.1);
	else if (keycode == 125)
		move_yoff(new, 0.1);
	else if (keycode == 69)
		change_depth(new, 2);
	else if (keycode == 78)
		change_depth(new, -2);
	else if (new)
	{
		ft_putnbr(keycode);
		ft_putchar('\n');
	}
	return (0);
}

void	run_win(t_mlx *new, int check)
{
	new->mlx = mlx_init();
	new->win = mlx_new_window(new->mlx, W_WIDTH, W_HEIGHT, "42");
	new->img = mlx_new_image(new->mlx, W_WIDTH, W_HEIGHT);
	new->scale = 1;
	new->depth = 300;
	if (check == 1)
		run_man(new);
	else if (check == 2)
		run_jul(new, 1, 0);
	mlx_mouse_hook(new->win, my_mouse_func, new);
	mlx_hook(new->win, 2, 0, my_key_press, new);
	mlx_loop(new->mlx);
}

void	check_param(t_mlx *new, char *str)
{
	if (!strncmp(str, "man", 3))
		run_win(new, 1);
	else if (!strncmp(str, "jul", 3))
		run_win(new, 2);
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
	while (i++ < argc)
		check_param(new, argv[i]);
	return (1);
}
