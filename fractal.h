/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhurt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 16:08:13 by lhurt             #+#    #+#             */
/*   Updated: 2016/12/14 16:08:22 by lhurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTAL_H
# define FRACTAL_H

# include <stdio.h>
# include <pthread.h>

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include "libft/libft.h"

# define W_WIDTH 1920
# define W_HEIGHT 1080
# define W_XORIGIN W_WIDTH / 2
# define W_YORIGIN W_HEIGHT / 2
# define new_x(i) ((i)*4.0/W_WIDTH - 2)
# define new_y(j) ((j)*4.0/W_HEIGHT - 2)

typedef struct		s_point
{
	double			x;
	double			y;
}					t_point;

typedef struct		s_env
{
	char			*check;
	double			scale;
	t_point			offset;
	t_point			lock;
	int				depth;
	int				color;
}					t_env;

typedef struct		s_mlx
{
	t_env			env;
	void			*mlx;
	void			*win;
	void			*img;
	char			*data;
	int				bits;
	int				size_line;
	int				endian;
}					t_mlx;

int					*return_map(int i);

#endif
