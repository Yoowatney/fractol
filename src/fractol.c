/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyoo <yoyoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 13:38:39 by yoyoo             #+#    #+#             */
/*   Updated: 2021/09/06 14:51:32 by yoyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	julia(double x, double y, int iter, t_data *image)
{
	double	x_new;
	double	c_re;
	double	c_im;

	c_re = image->constant[0];
	c_im = image->constant[1];
	while (pow(x, 2.0) + pow(x, 2.0) < 4.0 && iter < ITER_MAX)
	{
		x_new = pow(x, 2.0) - pow(y, 2.0) + c_re;
		y = 2 * x * y + c_im;
		x = x_new;
		iter++;
	}
	return (iter);
}

int	mandelbrot(double c_re, double c_im, int iter)
{
	double	x;
	double	y;
	double	x_new;

	x = 0;
	y = 0;
	while (pow(x, 2.0) + pow(x, 2.0) < 4.0 && iter < ITER_MAX)
	{
		x_new = pow(x, 2.0) - pow(y, 2.0) + c_re;
		y = 2 * x * y + c_im;
		x = x_new;
		iter++;
	}
	return (iter);
}

int	burningship(double c_re, double c_im, int iter)
{
	double	x;
	double	y;
	double	x_new;

	x = 0;
	y = 0;
	while (pow(x, 2.0) + pow(x, 2.0) < 4.0 && iter < ITER_MAX)
	{
		x_new = pow(x, 2.0) - pow(y, 2.0) + c_re;
		y = 2 * x * y + c_im;
		if (y < 0)
			y *= -1;
		x = x_new;
		iter++;
	}
	return (iter);
}
