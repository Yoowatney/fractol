/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyoo <yoyoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 13:41:29 by yoyoo             #+#    #+#             */
/*   Updated: 2021/09/06 15:23:20 by yoyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	my_mlx_pixel_put(t_data	*img, int x, int y, int color)
{
	unsigned char	*dest;

	dest = (unsigned char *)img->addr + x * (img->bits_per_pixel / 8)
		+ y * (img->size_line);
	*(unsigned int *)dest = color;
}

int	iteration(t_data *img, double c_re, double c_im)
{
	int	iter;

	if (img->type == MANDEL)
		iter = mandelbrot(c_re, c_im, 0);
	else if (img->type == JULIA)
		iter = julia(c_re, c_im, 0, img);
	else
		iter = burningship(c_re, c_im, 0);
	return (iter);
}

void	put_pixel(t_data *img, double c_re, double c_im)
{
	int		x;
	int		y;
	int		iter;
	double	dx;
	double	dy;

	dx = img->zoom / WIDTH;
	dy = img->zoom / HEIGHT;
	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		c_re = img->start_x;
		while (++x < WIDTH)
		{
			iter = iteration(img, c_re, c_im);
			if (iter < ITER_MAX)
				my_mlx_pixel_put(img, x, y, img->color_func(iter));
			else
				my_mlx_pixel_put(img, x, y, 0x00000000);
			c_re += dx;
		}
		c_im += dy;
	}
}
