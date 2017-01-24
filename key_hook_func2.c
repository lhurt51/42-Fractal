/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook_func2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhurt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 17:14:28 by lhurt             #+#    #+#             */
/*   Updated: 2017/01/23 17:14:30 by lhurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

void	change_color_type(t_mlx *new)
{
	if (new->env.color_type == 1)
		new->env.color_type = 0;
	else
		new->env.color_type = 1;
	run_img(new);
}

void	reset_screen(t_mlx *new)
{
	reset_struct(new);
	run_img(new);
}

int		my_extra_key1(int keycode, t_mlx *new)
{
	if (keycode == 44)
		change_color_type(new);
	else if (keycode == 15)
		reset_screen(new);
	return (0);
}
