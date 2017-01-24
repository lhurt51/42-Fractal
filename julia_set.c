/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhurt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 13:47:51 by lhurt             #+#    #+#             */
/*   Updated: 2017/01/20 13:47:53 by lhurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

int		julia_depth(t_mlx *new, int x, int y, int col, int row)
{
	double	newRe, newIm, oldRe, oldIm;
	double	cRe, cIm;
	int		i;

	cRe = NEW_X(x);
	cIm = NEW_Y(y);
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
				  pixel_to_img(new, col, row, tmp[RANGE(i, 0, 64, 0, new->env.depth)]);
			else
				  pixel_to_img(new, col, row, 0x000000);
			col++;
		}
		row++;
	}
}

void	*thread_jul(void *arg)
{
	static unsigned int i = 1;
	t_mlx *new;
	t_point tmp;

	if (i > THREADS)
		i = 1;
	get_quad(i++, &tmp);
	new = (t_mlx*)arg;
	julia_set(new, new->env.lock.x, new->env.lock.y, tmp);
	return (NULL);
}
