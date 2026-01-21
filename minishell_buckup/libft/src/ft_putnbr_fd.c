/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrosio <jbrosio@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:58:14 by jbrosio           #+#    #+#             */
/*   Updated: 2025/11/10 20:49:35 by jbrosio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_putnbr_fd(int n, int fd)
{
	long int	num;
	int			printed;

	printed = 0;
	num = n;
	if (num < 0)
	{
		printed += ft_putchar_fd('-', 1);
		num = -num;
	}
	if (num >= 10)
	{
		printed += ft_putnbr_fd(num / 10, fd);
		num %= 10;
	}
	if (num < 10)
	{
		num += '0';
		printed += write(fd, &num, 1);
	}
	return (printed);
}
