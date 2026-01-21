/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex_control_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrosio <jbrosio@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 11:30:14 by jbrosio           #+#    #+#             */
/*   Updated: 2026/01/19 13:00:25 by jbrosio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	puthex_p_fd(unsigned long long num, int fd)
{
	char	*digits;
	int		printed;

	printed = 0;
	if (!num)
	{
		printed += ft_putstr_fd("(nil)", fd);
		return (printed);
	}
	printed += ft_putstr_fd("0x", fd);
	digits = "0123456789abcdef";
	if (num < 16)
		printed += ft_putchar_fd(digits[num], fd);
	if (num >= 16)
	{
		printed += puthex_lower_fd(num / 16, fd);
		printed += ft_putchar_fd(digits[num % 16], fd);
	}
	return (printed);
}

int	puthex_lower_fd(unsigned long long num, int fd)
{
	char	*digits;
	int		printed;

	printed = 0;
	digits = "0123456789abcdef";
	if (num < 16)
		printed += ft_putchar_fd(digits[num], fd);
	else if (num >= 16)
	{
		printed += puthex_lower_fd(num / 16, fd);
		printed += ft_putchar_fd(digits[num % 16], fd);
	}
	return (printed);
}

int	puthex_upper_fd(unsigned long long num, int fd)
{
	char	*digits;
	int		printed;

	printed = 0;
	digits = "0123456789ABCDEF";
	if (num < 16)
		printed += ft_putchar_fd(digits[num], fd);
	else if (num >= 16)
	{
		printed += puthex_upper_fd(num / 16, fd);
		printed += ft_putchar_fd(digits[num % 16], fd);
	}
	return (printed);
}
