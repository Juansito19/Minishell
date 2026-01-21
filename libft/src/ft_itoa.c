/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrosio <jbrosio@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:45:54 by jbrosio           #+#    #+#             */
/*   Updated: 2025/11/10 20:49:35 by jbrosio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	numsize(int n)
{
	long int	num;
	int			count;

	count = 1;
	num = n;
	if (n < 0)
	{
		count++;
		num = -num;
	}
	while (num / 10 >= 1)
	{
		num = num / 10;
		count++;
	}
	return (count);
}

static int	divnum(int n)
{
	long int	num;
	int			div;

	num = n;
	div = 1;
	if (num < 0)
		num = -num;
	while (num / 10 >= 1)
	{
		div = div * 10;
		num = num / 10;
	}
	return (div);
}

static char	*reservmemory(int n)
{
	long int	num;
	char		*s;

	num = n;
	s = (char *)ft_calloc((numsize(num) + 1), sizeof(char));
	return (s);
}

char	*ft_itoa(int n)
{
	long int	number;
	char		*num;
	int			i;
	int			size_num ;
	int			div;

	i = 0;
	number = n;
	if (number < 0)
		number = -number;
	size_num = numsize(n);
	div = divnum(n);
	num = reservmemory(n);
	if (!num)
		return (NULL);
	while (i < size_num)
	{
		if (n < 0 && i == 0)
			num[i++] = '-';
		num[i] = (number / div) + '0';
		number = number % div;
		div = div / 10;
		i++;
	}
	return (num);
}
