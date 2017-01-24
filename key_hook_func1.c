/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook_func1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhurt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 17:10:08 by lhurt             #+#    #+#             */
/*   Updated: 2017/01/23 17:10:11 by lhurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

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

int		my_extra_key(int keycode, t_mlx *new)
{
	if (keycode == 69)
		change_depth(new, 10);
	else if (keycode == 78)
		change_depth(new, -10);
	else if (keycode == 25)
		change_len(new, -0.01);
	else if (keycode == 29)
		change_len(new, 0.01);
	else if (keycode == 33)
		change_ang(new, 0.01);
	else if (keycode == 30)
		change_ang(new, -0.01);
	else
		my_extra_key1(keycode, new);
	return (0);
}
