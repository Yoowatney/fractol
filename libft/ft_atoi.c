/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyoo <yoyoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 21:19:39 by yoyoo             #+#    #+#             */
/*   Updated: 2021/08/24 23:36:52 by yoyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int			sign;
	long long	i;

	sign = 1;
	i = 0;
	while (*str == ' ' || *str == '\n' || *str == '\f'
		|| *str == '\t' || *str == '\r' || *str == '\v')
		str++;
	if (*str == '-')
	{
		str++;
		sign *= -1;
	}
	else if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		i *= 10;
		i += (sign) * ((*(str++) - '0'));
		if (i > 2147483647)
			return (-1);
		else if (i < -2147483648)
			return (0);
	}
	return ((int)i);
}
