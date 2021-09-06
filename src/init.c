/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyoo <yoyoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 13:45:01 by yoyoo             #+#    #+#             */
/*   Updated: 2021/09/06 14:52:22 by yoyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	assign_func(t_data *image)
{
	if (image->color == M_COLOR)
		image->color_func = &color_mandel;
	else if (image->color == J_COLOR)
		image->color_func = &color_julia;
	else if (image->color == B_COLOR)
		image->color_func = &color_burn;
}

void	assign_color(t_data *img)
{
	if (img->color == M_COLOR)
		img->color = J_COLOR;
	else if (img->color == J_COLOR)
		img->color = B_COLOR;
	else if (img->color == B_COLOR)
		img->color = M_COLOR;
	assign_func(img);
}

int	init(t_mlx	*mlx)
{
	mlx->mlx_ptr = mlx_init();
	if (mlx->mlx_ptr == NULL)
		return (ERROR);
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, WIDTH, HEIGHT, "fractol");
	if (mlx->win_ptr == NULL)
		return (ERROR);
	mlx->img.img_ptr = mlx_new_image(mlx->mlx_ptr, WIDTH, HEIGHT);
	if (mlx->img.img_ptr == NULL)
		return (ERROR);
	mlx->img.addr = mlx_get_data_addr(mlx->img.img_ptr,
			&mlx->img.bits_per_pixel, &mlx->img.size_line, &mlx->img.endian);
	if (mlx->img.addr == NULL)
		return (ERROR);
	mlx->img.zoom = 4.0;
	mlx->img.start_x = -2.0;
	mlx->img.start_y = -2.0;
	return (SUCCESS);
}
