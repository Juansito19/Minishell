/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrosio <jbrosio@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 18:46:08 by jbrosio           #+#    #+#             */
/*   Updated: 2025/11/10 20:49:35 by jbrosio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static float	ft_double_add(char *number, int num)
{
	int		i;
	int		count;
	float	res;

	count = 1;
	i = 0;
	res = 0;
	while (number[i])
	{
		if (number[i] == 46)
			i++;
		else
		{
			res = (res * 10) + (number[i] - '0');
			count *= 10;
			i++;
		}
	}
	res = res / count;
	res = num + res;
	return (res);
}

float	ft_atod(char *nptr)
{
	float		num;
	int			i;
	int			sign;

	i = 0;
	num = 0;
	sign = 1;
	while (nptr[i] == 32 || (nptr[i] > 8 && nptr[i] < 14))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] != '\0' && nptr[i] != 46)
	{
		if (nptr[i] < 48 || nptr[i] > 57)
			return (num * sign);
		num = (num * 10) + (nptr[i] - '0');
		i++;
	}
	if (nptr[i] == 46)
		num = ft_double_add(&nptr[i], (int)num);
	return (num * sign);
}
