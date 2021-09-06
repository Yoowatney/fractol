/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyoo <yoyoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 13:40:23 by yoyoo             #+#    #+#             */
/*   Updated: 2021/09/06 15:20:00 by yoyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	color_shift(int keycode, t_mlx *mlx)
{
	if (keycode == 258)
	{
		if (mlx->img.color == M_COLOR)
			mlx->img.color = J_COLOR;
		else if (mlx->img.color == J_COLOR)
			mlx->img.color = B_COLOR;
		else if (mlx->img.color == B_COLOR)
			mlx->img.color = M_COLOR;
		assign_color(&mlx->img);
		put_pixel(&mlx->img, mlx->img.start_x, mlx->img.start_y);
		mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img.img_ptr,
			   	0, 0);
	}
	return (SUCCESS);
}

int	color_mandel(int iter)
{
	double	r;
	double	g;
	double	b;
	int		color;

	r = log((double)iter * 0.5) + 32;
	g = log((double)iter * 0.7);
	b = log((double)iter * 0.9);
	color = ((int)(255.999 * r) << 16) + ((int)(255.999 * g) << 8)
		+ ((int)(255.999 * b));
	return (color);
}

int	color_julia(int iter)
{
	double	r;
	double	g;
	double	b;
	int		color;

	r = log((double)iter * 0.7) + 32;
	g = log((double)iter * 0.85);
	b = log((double)iter * 0.5);
	color = ((int)(255.999 * r) << 16) + ((int)(255.999 * g) << 8)
		+ ((int)(255.999 * b));
	return (color);
}

int	color_burn(int iter)
{
	double	r;
	double	g;
	double	b;
	int		color;

	r = log((double)iter * 0.9) + 32;
	g = log((double)iter * 0.5);
	b = log((double)iter * 0.7);
	color = ((int)(255.999 * r) << 16) + ((int)(255.999 * g) << 8)
		+ ((int)(255.999 * b));
	return (color);
}
