/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyoo <yoyoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 13:36:00 by yoyoo             #+#    #+#             */
/*   Updated: 2021/09/06 14:43:56 by yoyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	check_set(char *set, t_data *img)
{
	if (ft_strncmp(set, "Mandelbrot", ft_strlen("Mandelbrot")) == 0)
	{
		img->type = MANDEL;
		img->color = M_COLOR;
		return ;
	}
	else if (ft_strncmp(set, "Julia", ft_strlen("Julia")) == 0)
	{
		img->type = JULIA;
		img->color = J_COLOR;
		return ;
	}
	else if (ft_strncmp(set, "Burning Ship", ft_strlen("Burning Ship")) == 0)
	{
		img->type = BURN;
		img->color = B_COLOR;
		return ;
	}
	printf("\nUsage : %s 'Mandelbrot' or 'Julia' or	'Burning ship'\n",
		   	"./fractol");
	exit(0);
}
