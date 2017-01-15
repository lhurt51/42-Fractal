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
	int		*tmp;
	int		row;
	int		col;
	int		i;

	row = 0;
	tmp = return_map(new->env.color);
	while (row < W_HEIGHT) {
		col = 0;
    	while (col < W_WIDTH) {
			man_depth(&i, (col - W_WIDTH / 2.0) * 4.0 / W_WIDTH * new->env.scale + new->env.x_offset,
				(row - W_HEIGHT / 2.0) * 4.0 / W_WIDTH * new->env.scale + new->env.y_offset, max);
	        if (i < max)
				pixel_to_img(new, col, row, tmp[i % 64]);
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

	cRe = new_x(x);
	cIm = new_y(y);
	newRe = (col - W_WIDTH / 2.0) * 4.0 / W_WIDTH * new->env.scale + new->env.x_offset;
	newIm = (row - W_HEIGHT / 2.0) * 4.0 / W_WIDTH * new->env.scale + new->env.y_offset;
	i = 0;
	while(i < new->env.depth)
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
	int	*tmp;
	int	i;
	int	row;
	int	col;

	row = 0;
	tmp = return_map(new->env.color);
	while (row < W_HEIGHT)
	{
		col = 0;
		while (col < W_WIDTH)
		{
			i = julia_depth(new, x, y, col, row);
			if (i < new->env.depth)
				  pixel_to_img(new, col, row, tmp[i % 64]);
			else
				  pixel_to_img(new, col, row, 0x000000);
			col++;
		}
		row++;
	}
}

void	run_man(t_mlx *new)
{
	mlx_destroy_image(new->mlx, new->img);
	new->img = mlx_new_image(new->mlx, W_WIDTH, W_HEIGHT);
	new->data = mlx_get_data_addr(new->img, &new->bits, &new->size_line, &new->endian);
	mandelbrot(new, new->env.depth);
	mlx_put_image_to_window(new->mlx, new->win, new->img, 0, 0);
}

void	run_jul(t_mlx *new, int x, int y)
{
	mlx_destroy_image(new->mlx, new->img);
	new->img = mlx_new_image(new->mlx, W_WIDTH, W_HEIGHT);
	new->data = mlx_get_data_addr(new->img, &new->bits, &new->size_line, &new->endian);
	julia_set(new, x, y);
	mlx_put_image_to_window(new->mlx, new->win, new->img, 0, 0);
}

void	check_param(t_mlx *new)
{
	if (!strncmp(new->env.check, "man", 3))
		run_man(new);
	else if (!strncmp(new->env.check, "jul", 3))
		run_jul(new, new->env.x_lock, new->env.y_lock);
	// else if (!strncmp(str, "apo", 3))
	//
	else
		error();
}

void	zoom(t_mlx *new, int x, int y, int check)
{
	if (check > 0)
	{
		new->env.scale *= .92;
		new->env.x_offset += (x - W_XORIGIN) / (W_XORIGIN / new->env.scale) / 2.5;
		new->env.y_offset += (y - W_YORIGIN) / (W_YORIGIN / new->env.scale) / 2.5;
	}
	else
	{
		new->env.scale /= .92;
		new->env.x_offset -= (x - W_XORIGIN) / (W_XORIGIN / new->env.scale) / 2.5;
		new->env.y_offset -= (y - W_YORIGIN) / (W_YORIGIN / new->env.scale) / 2.5;
	}
	check_param(new);
}

int		my_mouse_func(int keycode, int x, int y, t_mlx *new)
{
	if (keycode == 1)
	{
		new->env.x_lock = x;
		new->env.y_lock = y;
		check_param(new);
	}
	else if (keycode == 5)
		zoom(new, x, y, 1);
	else if (keycode == 4)
		zoom(new, x, y, -1);
	else
	{
		ft_putnbr(keycode);
		ft_putchar('\n');
	}
	return (0);
}

void 	move_xoff(t_mlx *new, double x)
{
	new->env.x_offset += x;
	check_param(new);
}

void 	move_yoff(t_mlx *new, double x)
{
	new->env.y_offset += x;
	check_param(new);
}

void	change_color(t_mlx *new, int i)
{
	new->env.color += i;
	if (new->env.color > 11)
		new->env.color = 0;
	else if (new->env.color < 0)
		new->env.color = 11;
	check_param(new);
}

void	change_depth(t_mlx *new, int x)
{
	if (new->env.depth + x > 0)
		new->env.depth += x;
	check_param(new);
}

int		my_key_press(int keycode, t_mlx *new)
{
	if (keycode == 53)
		exit(0);
	else if (keycode == 123)
		move_xoff(new, -0.025);
	else if (keycode == 124)
		move_xoff(new, 0.025);
	else if (keycode == 126)
		move_yoff(new, -0.025);
	else if (keycode == 125)
		move_yoff(new, 0.025);
	else if (keycode == 69)
		change_depth(new, 10);
	else if (keycode == 78)
		change_depth(new, -10);
	else if (keycode == 47)
		change_color(new, 1);
	else if (keycode == 43)
		change_color(new, -1);
	else if (new)
	{
		ft_putnbr(keycode);
		ft_putchar('\n');
	}
	return (0);
}

void	run_win(t_mlx *new, char *check)
{
	new->mlx = mlx_init();
	new->win = mlx_new_window(new->mlx, W_WIDTH, W_HEIGHT, "42");
	new->img = mlx_new_image(new->mlx, W_WIDTH, W_HEIGHT);
	new->env.scale = 1;
	new->env.x_lock = 425;
	new->env.y_lock = 600;
	new->env.depth = 300;
	new->env.check = check;
	check_param(new);
	mlx_mouse_hook(new->win, my_mouse_func, new);
	mlx_hook(new->win, 2, 0, my_key_press, new);
	mlx_loop(new->mlx);
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
		run_win(new, argv[i]);
	return (1);
}
