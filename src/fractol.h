/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyoo <yoyoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 13:34:04 by yoyoo             #+#    #+#             */
/*   Updated: 2021/09/06 15:19:44 by yoyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include "../minilibX/mlx.h"

# define ERROR  -1
# define SUCCESS 0
# define WIDTH  800
# define ITER_MAX 200
# define HEIGHT 700
# define MANDEL 77
# define JULIA  74
# define BURN   102
# define M_COLOR	11
# define J_COLOR	12
# define B_COLOR 13

typedef struct s_data
{
	void	*img_ptr;
	char	*addr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	int		type;
	int		color;
	double	start_x;
	double	start_y;
	double	zoom;
	double	constant[2];
	int		(*color_func)(int);
}		t_data;

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_data	img;
}				t_mlx;

void	check_set(char *set, t_data *img);
int		ft_strncmp(const char *ptr1, const char *ptr2, size_t num);
size_t	ft_strlen(const char *str);

int		julia(double x, double y, int iter, t_data *image);
int		mandelbrot(double c_re, double c_im, int iter);
int		burningship(double c_re, double c_im, int iter);

int		color_mandel(int iter);
int		color_julia(int iter);
int		color_burn(int iter);
int		color_shift(int keycode, t_mlx *mlx);

void	put_pixel(t_data *img, double c_re, double c_im);
void	my_mlx_pixel_put(t_data	*img, int x, int y, int color);

int		init(t_mlx	*mlx);
void	assign_func(t_data *image);
void	assign_color(t_data *img);

int		key_hook(int keycode, t_mlx *mlx);
int		zoom(int button, int x, int y, t_mlx *mlx);
int		julia_event(int x, int y, t_mlx *mlx);

#endif
