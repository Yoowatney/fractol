/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyoo <yoyoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 13:46:28 by yoyoo             #+#    #+#             */
/*   Updated: 2021/09/06 15:20:23 by yoyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	key_hook(int keycode, t_mlx *mlx)
{
	if (keycode == 53)
	{
		mlx_destroy_image(mlx->mlx_ptr, mlx->img.img_ptr);
		mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
		exit(0);
	}
	if (keycode == 123)
		mlx->img.start_x -= (0.25) * mlx->img.zoom;
	else if (keycode == 124)
		mlx->img.start_x += (0.25) * mlx->img.zoom;
	else if (keycode == 125)
		mlx->img.start_y += (0.25) * mlx->img.zoom;
	else if (keycode == 126)
		mlx->img.start_y -= (0.25) * mlx->img.zoom;
	put_pixel(&mlx->img, mlx->img.start_x, mlx->img.start_y);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img.img_ptr, 0, 0);
	return (0);
}

int	zoom(int button, int x, int y, t_mlx *mlx)
{
	double	new_x;
	double	new_y;
	t_data	*image;

	image = &mlx->img;
	if (button == 5)
	{
		new_x = (image->zoom) * (double)x / WIDTH + image->start_x;
		new_y = (image->zoom) * (double)y / HEIGHT + image->start_y;
		image->start_x = new_x - (image->zoom) * 0.5;
		image->start_y = new_y - (image->zoom) * 0.5;
		image->zoom *= 0.65;
	}
	else if (button == 4)
	{
		new_x = (image->zoom) * (double)x / WIDTH + image->start_x;
		new_y = (image->zoom) * (double)y / WIDTH + image->start_y;
		image->start_x = new_x - (image->zoom / 2);
		image->start_y = new_y - (image->zoom / 2);
		image->zoom /= 0.65;
	}
	put_pixel(image, image->start_x, image->start_y);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, image->img_ptr, 0, 0);
	return (0);
}

int	julia_event(int x, int y, t_mlx *mlx)
{
	t_data	*image;

	image = &mlx->img;
	(image->constant)[0] = (image->zoom) * (double)x / WIDTH + image->start_x;
	(image->constant)[1] = (image->zoom) * (double)y / HEIGHT + image->start_y;
	put_pixel(image, image->start_x, image->start_y);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, image->img_ptr, 0, 0);
	return (0);
}
