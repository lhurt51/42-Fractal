/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_algo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhurt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 19:21:13 by lhurt             #+#    #+#             */
/*   Updated: 2016/11/21 19:23:15 by lhurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

void	draw_y(t_mlx *lst, t_point *point1, t_point *point2, t_line *new)
{
	int		*tmp;
	int		x;
	int		y;
	int		p;

	x = point1->x;
	y = point1->y;
	p = 2 * new->xans - new->yans;
	tmp = return_map(lst->env.color);
	if (x < (int)point2->x)
		new->inc = 1;
	else
		new->inc = -1;
	while (y++ < (int)point2->y)
	{
		if ((x < W_WIDTH && x > 0) && (y - 1 < W_HEIGHT && y - 1 > 0))
			pixel_to_img(lst, x, y - 1, tmp[y % 64]);
		if (p < 0)
			p += 2 * new->xans;
		else
		{
			x += new->inc;
			p += 2 * (new->xans - new->yans);
		}
	}
}

void	draw_x(t_mlx *lst, t_point *point1, t_point *point2, t_line *new)
{
	int		*tmp;
	int		x;
	int		y;
	int		p;

	x = point1->x;
	y = point1->y;
	p = 2 * new->yans - new->xans;
	tmp = return_map(lst->env.color);
	if (y < (int)point2->y)
		new->inc = 1;
	else
		new->inc = -1;
	while (x++ < (int)point2->x)
	{
		if ((x - 1 < W_WIDTH && x - 1 > 0) && (y < W_HEIGHT && y > 0))
			pixel_to_img(lst, x - 1, y, tmp[y % 64]);
		if (p < 0)
			p += 2 * new->yans;
		else
		{
			y += new->inc;
			p += 2 * (new->yans - new->xans);
		}
	}
}

void	get_da(t_mlx *lst, t_point *point1, t_point *point2)
{
	t_line		*new;

	new = malloc(sizeof(t_line));
	if (!new)
		return ;
	new->xans = fabs(point2->x - point1->x);
	new->yans = fabs(point2->y - point1->y);
	if (new->xans > new->yans)
	{
		if (point1->x > point2->x)
			draw_x(lst, point2, point1, new);
		else
			draw_x(lst, point1, point2, new);
	}
	else
	{
		if (point1->y > point2->y)
			draw_y(lst, point2, point1, new);
		else
			draw_y(lst, point1, point2, new);
	}
}
