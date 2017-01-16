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

void	mandelbrot(t_mlx *new, int max, t_point quad)
{
	int		*tmp;
	int		row;
	int		col;
	int		i;
	int		tmpc;

	ft_putendl("RUNNING...");
	row = (quad.y == 1) ? 540 : 0;
	tmpc = (quad.x == 1) ? 960 : 0;
	tmp = return_map(new->env.color);
	while (row < W_HEIGHT / quad.y)
	{
		col = tmpc;
		while (col < W_WIDTH / quad.x)
		{
			man_depth(&i, (col - W_WIDTH / 2.0) * 4.0 / W_WIDTH * new->env.scale + new->env.offset.x,
				(row - W_HEIGHT / 2.0) * 4.0 / W_WIDTH * new->env.scale + new->env.offset.y, max);
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
	newRe = (col - W_WIDTH / 2.0) * 4.0 / W_WIDTH * new->env.scale + new->env.offset.x;
	newIm = (row - W_HEIGHT / 2.0) * 4.0 / W_WIDTH * new->env.scale + new->env.offset.y;
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

void	julia_set(t_mlx *new, int x, int y, t_point quad)
{
	int		*tmp;
	int		i;
	int		row;
	int		col;
	int		tmpc;

	row = (quad.y == 1) ? 540 : 0;
	tmpc = (quad.x == 1) ? 960 : 0;
	tmp = return_map(new->env.color);
	while (row < W_HEIGHT / quad.y)
	{
		col = tmpc;
		while (col < W_WIDTH / quad.x)
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

void	get_quad(int i, t_point *tmp)
{
	if (i == 1)
	{
		tmp->x = 2;
		tmp->y = 2;
	}
	else if(i == 2)
	{
		tmp->x = 1;
		tmp->y = 2;
	}
	else if(i == 3)
	{
		tmp->x = 2;
		tmp->y = 1;
	}
	else if (i == 4)
	{
		tmp->x = 1;
		tmp->y = 1;
	}
}

void	*thread_man(void *arg)
{
	static int i = 0;
	t_mlx *new;
	t_point tmp;

	if (i >= 4)
		i = 0;
	get_quad(++i, &tmp);
	new = (t_mlx*)arg;
	mandelbrot(new, new->env.depth, tmp);
	return (NULL);
}

void	*thread_jul(void *arg)
{
	static unsigned int i = 0;
	t_mlx *new;
	t_point tmp;

	if (i >= 4)
		i = 0;
	get_quad(++i, &tmp);
	new = (t_mlx*)arg;
	julia_set(new, new->env.lock.x, new->env.lock.y, tmp);
	return (NULL);
}

void	*check_param(t_mlx *new)
{
	if (!strncmp(new->env.check, "man", 3))
		return (&thread_man);
	else if (!strncmp(new->env.check, "jul", 3))
		return (&thread_jul);
	// else if (!strncmp(str, "apo", 3))
	//
	else
		return(error());
}

void 	make_threads(t_mlx *new)
{
	pthread_t	pth[4];
	int			i;

	i = 0;
	while (i++ < 4)
	{
		pthread_create(&pth[i - 1], NULL, check_param(new), new);
		usleep(1);
	}
	i = 0;
	while (i++ < 4)
		pthread_join(pth[i - 1], NULL);
}

void	run_img(t_mlx *new)
{
	mlx_destroy_image(new->mlx, new->img);
	new->img = mlx_new_image(new->mlx, W_WIDTH, W_HEIGHT);
	new->data = mlx_get_data_addr(new->img, &new->bits, &new->size_line, &new->endian);
	make_threads(new);
	mlx_put_image_to_window(new->mlx, new->win, new->img, 0, 0);
}

void	zoom(t_mlx *new, int x, int y, int check)
{
	if (check > 0)
	{
		new->env.scale *= .92;
		new->env.offset.x += (x - W_XORIGIN) / (W_XORIGIN / new->env.scale) / 2.5;
		new->env.offset.y += (y - W_YORIGIN) / (W_YORIGIN / new->env.scale) / 2.5;
	}
	else
	{
		new->env.scale /= .92;
		new->env.offset.x -= (x - W_XORIGIN) / (W_XORIGIN / new->env.scale) / 2.5;
		new->env.offset.y -= (y - W_YORIGIN) / (W_YORIGIN / new->env.scale) / 2.5;
	}
	run_img(new);
}

int		my_mouse_func(int keycode, int x, int y, t_mlx *new)
{
	if (keycode == 1)
	{
		new->env.lock.x = x;
		new->env.lock.y = y;
		run_img(new);
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
	new->env.offset.x += x;
	run_img(new);
}

void 	move_yoff(t_mlx *new, double x)
{
	new->env.offset.y += x;
	run_img(new);
}

void	change_color(t_mlx *new, int i)
{
	new->env.color += i;
	if (new->env.color > 11)
		new->env.color = 0;
	else if (new->env.color < 0)
		new->env.color = 11;
	run_img(new);
}

void	change_depth(t_mlx *new, int x)
{
	if (new->env.depth + x > 0 && new->env.depth + x < 500)
		new->env.depth += x;
	run_img(new);
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
	new->env.lock.x = 425;
	new->env.lock.y = 600;
	new->env.depth = 300;
	new->env.check = check;
	run_img(new);
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
