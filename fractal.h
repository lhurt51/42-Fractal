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

# include <pthread.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include "libft/libft.h"

# define THREADS 4
# define ZOOM_SPEED 2
# define W_WIDTH 1280
# define W_HEIGHT 720
# define W_XORIGIN W_WIDTH / 2
# define W_YORIGIN W_HEIGHT / 2
# define NEW_X(i) ((i) * 4.0 / W_WIDTH - 2)
# define NEW_Y(j) ((j) * 4.0 / W_HEIGHT - 2)
# define RANGE(x, a, b, mn, mx) (((b)-(a)) * ((x)-(mn)) / ((mx)-(mn))) + (a)
# define X_OFF(x, scale) ((x-W_XORIGIN)/(W_XORIGIN/scale)*2)
# define Y_OFF(y, scale) ((y-W_YORIGIN)/(W_YORIGIN/scale)*(2*W_HEIGHT/W_WIDTH))
# define RE(col, scale, offset) ((col-W_WIDTH/2.0)*4.0/W_WIDTH*scale+offset)
# define IM(row, scale, offset) (row-W_HEIGHT/2.0)*4.0/W_WIDTH*scale+offset

typedef struct		s_point
{
	double			x;
	double			y;
}					t_point;

typedef struct		s_line
{
	int				inc;
	float			yans;
	float			xans;
}					t_line;

typedef struct		s_env
{
	char			*check;
	double			scale;
	double			angoff;
	double			lenoff;
	t_point			offset;
	t_point			lock;
	int				depth;
	int				color;
	int				color_type;
	int				lockup;
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

void				*error(void);
int					*extra_maps(int i);
int					*extra_maps1(int i);
int					*return_map(int i);
int					get_color_type(t_mlx *new, int ans1, int answ2);
void				reset_struct(t_mlx *new);
void				pixel_to_img(t_mlx *new, int x, int y, int color);
void				get_da(t_mlx *lst, t_point *point1, t_point *point2);
void				get_quad(int i, t_point *tmp);
void				*thread_man(void *arg);
void				*thread_jul(void *arg);
void				run_tree(t_mlx *new);
void				run_img(t_mlx *new);
int					my_extra_key(int keycode, t_mlx *new);
int					my_extra_key1(int keycode, t_mlx *new);
int					my_key_press(int keycode, t_mlx *new);
int					my_mouse_movement(int x, int y, t_mlx *new);
int					my_mouse_func(int keycode, int x, int y, t_mlx *new);

#endif
