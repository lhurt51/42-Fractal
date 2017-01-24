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

void	change_len(t_mlx *new, double x)
{
	if (new->env.lenoff + x > 0.15 && new->env.lenoff + x < 0.75)
		new->env.lenoff += x;
	run_img(new);
}

void	change_ang(t_mlx *new, double x)
{
	if (new->env.angoff + x > 30 && new->env.angoff + x < 60)
		new->env.angoff += x;
	run_img(new);
}

void	reset_screen(t_mlx *new)
{
	reset_struct(new);
	run_img(new);
}

int		my_key_press(int keycode, t_mlx *new)
{
	if (keycode == 53)
	{
		if (new)
			free(new);
		exit(0);
	}
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
	else if (keycode == 25)
		change_len(new, -0.01);
	else if (keycode == 29)
		change_len(new, 0.01);
	else if (keycode == 33)
		change_ang(new, 0.01);
	else if (keycode == 30)
		change_ang(new, -0.01);
	else if (keycode == 15)
		reset_screen(new);
	else
	{
		ft_putnbr(keycode);
		ft_putchar('\n');
	}
	return (0);
}
