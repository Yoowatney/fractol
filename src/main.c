/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyoo <yoyoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 13:36:38 by yoyoo             #+#    #+#             */
/*   Updated: 2021/09/06 15:20:58 by yoyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	main(int argc, char *argv[])
{
	t_mlx	mlx;

	if (argc != 2)
	{
		printf("\nUsage : %s 'Mandelbrot' or 'Julia' or 'Burning Ship'\n",
			argv[0]);
		return (0);
	}
	check_set(argv[1], &mlx.img);
	init(&mlx);
	assign_func(&mlx.img);
	put_pixel(&mlx.img, -2.0, -2.0);
	mlx_put_image_to_window(mlx.mlx_ptr, mlx.win_ptr, mlx.img.img_ptr, 0, 0);
	mlx_key_hook(mlx.win_ptr, &key_hook, &mlx);
	mlx_hook(mlx.win_ptr, 6, 0, &julia_event, &mlx);
	mlx_hook(mlx.win_ptr, 2, 0, &color_shift, &mlx);
	mlx_mouse_hook(mlx.win_ptr, &zoom, &mlx);
	mlx_loop(mlx.mlx_ptr);
	return (0);
}
