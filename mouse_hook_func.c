/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook_func.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhurt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 13:34:25 by lhurt             #+#    #+#             */
/*   Updated: 2017/01/20 13:34:26 by lhurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

int		my_mouse_movement(int x, int y, t_mlx *new)
{
	if (new->env.lockup == 1)
	{
		new->env.lock.x = x;
		new->env.lock.y = y;
		run_img(new);
	}
	return (0);
}

void	zoom(t_mlx *new, int x, int y, int check)
{
	if (check > 0)
	{
		new->env.scale *= .92;
		new->env.offset.x += (x - W_XORIGIN) / (W_XORIGIN /
			new->env.scale) / 2.5;
		new->env.offset.y += (y - W_YORIGIN) / (W_YORIGIN /
			new->env.scale) / 2.5;
	}
	else
	{
		new->env.scale /= .92;
		new->env.offset.x -= (x - W_XORIGIN) / (W_XORIGIN /
			new->env.scale) / 2.5;
		new->env.offset.y -= (y - W_YORIGIN) / (W_YORIGIN /
			new->env.scale) / 2.5;
	}
	run_img(new);
}

int		my_mouse_func(int keycode, int x, int y, t_mlx *new)
{
	if (keycode == 1)
	{
		if (new->env.lockup == 1)
			new->env.lockup = 0;
		else
			new->env.lockup = 1;
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
