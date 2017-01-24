/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhurt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 13:55:27 by lhurt             #+#    #+#             */
/*   Updated: 2017/01/20 13:55:28 by lhurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

void	fractal_tree(t_mlx *new, t_point *pnt1, double len, double ang)
{
	t_point *pnt2;

	pnt2 = malloc(sizeof(t_point));
	if (len > 2)
	{
		pnt2->x = pnt1->x + len * cos(ang) * 2 * new->env.scale;
		pnt2->y = pnt1->y - len * sin(ang) * 2 * new->env.scale;
		get_da(new, pnt1, pnt2);
		fractal_tree(new, pnt2, len * new->env.lenoff, ang + new->env.angoff);
		fractal_tree(new, pnt2, len * new->env.lenoff, ang - new->env.angoff);
	}
}

void	run_tree(t_mlx *new)
{
	t_point pnt1;

	new->env.color_type = 0;
	pnt1.x = W_XORIGIN + new->env.offset.x;
	pnt1.y = W_HEIGHT + new->env.offset.y;
	fractal_tree(new, &pnt1, new->env.depth, M_PI / 2);
}
