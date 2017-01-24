/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhurt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 13:47:51 by lhurt             #+#    #+#             */
/*   Updated: 2017/01/23 18:10:57 by lhurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

int		julia_depth(t_mlx *new, t_point tmp, int col, int row)
{
	double	new_re;
	double	new_im;
	double	old_re;
	double	old_im;
	int		i;

	new_re = (col - W_WIDTH / 2.0) * 4.0 / W_WIDTH * new->env.scale +
		new->env.offset.x;
	new_im = (row - W_HEIGHT / 2.0) * 4.0 / W_WIDTH * new->env.scale +
		new->env.offset.y;
	i = 0;
	while (i < new->env.depth)
	{
		old_re = new_re;
		old_im = new_im;
		new_re = old_re * old_re - old_im * old_im + tmp.x;
		new_im = 2 * old_re * old_im + tmp.y;
		if ((new_re * new_re + new_im * new_im) > 4)
			break ;
		i++;
	}
	return (i);
}

void	julia_set(t_mlx *new, int x, int y, t_point quad)
{
	t_point		point;
	int			*tmp;
	int			i;
	int			row;
	int			col;

	row = (quad.y == 1) ? 540 : 0;
	tmp = return_map(new->env.color);
	while (row < W_HEIGHT / quad.y)
	{
		col = (quad.x == 1) ? 960 : 0;
		while (col < W_WIDTH / quad.x)
		{
			point.x = NEW_X(x);
			point.y = NEW_Y(y);
			if ((i = julia_depth(new, point, col, row)) < new->env.depth)
				pixel_to_img(new, col, row,
					tmp[get_color_type(new, i % 64,
						RANGE(i, 0, 64, 0, new->env.depth))]);
			else
				pixel_to_img(new, col, row, 0x000000);
			col++;
		}
		row++;
	}
}

void	*thread_jul(void *arg)
{
	static unsigned int	i = 1;
	t_mlx				*new;
	t_point				tmp;

	if (i > THREADS)
		i = 1;
	get_quad(i++, &tmp);
	new = (t_mlx*)arg;
	julia_set(new, new->env.lock.x, new->env.lock.y, tmp);
	return (NULL);
}
