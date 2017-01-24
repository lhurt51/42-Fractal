/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhurt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 13:31:23 by lhurt             #+#    #+#             */
/*   Updated: 2017/01/20 13:31:25 by lhurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

void	move_xoff(t_mlx *new, double x)
{
	new->env.offset.x += x;
	run_img(new);
}

void	move_yoff(t_mlx *new, double x)
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
	else if (keycode == 47)
		change_color(new, 1);
	else if (keycode == 43)
		change_color(new, -1);
	else
		my_extra_key(keycode, new);
	return (0);
}
