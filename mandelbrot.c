/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhurt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 13:47:37 by lhurt             #+#    #+#             */
/*   Updated: 2017/01/20 13:47:39 by lhurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

void	man_depth(int *i, double c_re, double c_im, int max)
{
	double	x;
	double	y;
	double	x_new;

	x = 0;
	y = 0;
	*i = 0;
	while (x * x + y * y <= 4 && *i < max)
	{
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

	row = (quad.y == 1) ? W_YORIGIN : 0;
	tmp = return_map(new->env.color);
	while (row < W_HEIGHT / quad.y)
	{
		col = (quad.x == 1) ? W_XORIGIN : 0;
		while (col < W_WIDTH / quad.x)
		{
			man_depth(&i, RE(col, new->env.scale, new->env.offset.x),
				IM(row, new->env.scale, new->env.offset.y), max);
			if (i < max)
				pixel_to_img(new, col, row, tmp[get_color_type(new, i % 64,
					RANGE(i, 0, 64, 0, new->env.depth))]);
			else
				pixel_to_img(new, col, row, 0x000000);
			col++;
		}
		row++;
	}
}

void	*thread_man(void *arg)
{
	static int	i = 1;
	t_mlx		*new;
	t_point		tmp;

	if (i > THREADS)
		i = 1;
	get_quad(i++, &tmp);
	new = (t_mlx*)arg;
	mandelbrot(new, new->env.depth, tmp);
	return (NULL);
}
