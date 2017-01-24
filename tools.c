/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhurt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 13:52:20 by lhurt             #+#    #+#             */
/*   Updated: 2017/01/20 13:52:21 by lhurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

void	*error(void)
{
	ft_putendl("Error: invalid amount of parameters");
	ft_putendl("Usage: valid parameters man, jul, tree");
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

void	reset_struct(t_mlx *new)
{
	new->env.scale = 1;
	new->env.color = 6;
	new->env.color_type = 1;
	new->env.offset.x = 0;
	new->env.offset.y = 0;
	new->env.lock.x = 425;
	new->env.lock.y = 600;
	new->env.depth = 200;
	new->env.lenoff = 0.65;
	new->env.angoff = 45;
}

void	get_quad(int i, t_point *tmp)
{
	if (i == 1)
	{
		tmp->x = 2;
		tmp->y = 2;
	}
	else if (i == 2)
	{
		tmp->x = 1;
		tmp->y = 2;
	}
	else if (i == 3)
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

int		get_color_type(t_mlx *new, int ans1, int ans2)
{
	if (new->env.color_type == 0)
		return (ans1);
	else
		return (ans2);
}
