/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex_control.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrosio <jbrosio@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 11:30:14 by jbrosio           #+#    #+#             */
/*   Updated: 2025/11/10 20:49:35 by jbrosio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_puthex_p(unsigned long long num)
{
	char	*digits;
	int		printed;

	printed = 0;
	if (!num)
	{
		printed += ft_putstr_fd("(nil)", 1);
		return (printed);
	}
	printed += ft_putstr_fd("0x", 1);
	digits = "0123456789abcdef";
	if (num < 16)
		printed += ft_putchar_fd(digits[num], 1);
	if (num >= 16)
	{
		printed += ft_puthex_x(num / 16);
		printed += ft_putchar_fd(digits[num % 16], 1);
	}
	return (printed);
}

int	ft_puthex_x(unsigned long long num)
{
	char	*digits;
	int		printed;

	printed = 0;
	digits = "0123456789abcdef";
	if (num < 16)
		printed += ft_putchar_fd(digits[num], 1);
	else if (num >= 16)
	{
		printed += ft_puthex_x(num / 16);
		printed += ft_putchar_fd(digits[num % 16], 1);
	}
	return (printed);
}

int	ft_puthex_mayus(unsigned long long num)
{
	char	*digits;
	int		printed;

	printed = 0;
	digits = "0123456789ABCDEF";
	if (num < 16)
		printed += ft_putchar_fd(digits[num], 1);
	else if (num >= 16)
	{
		printed += ft_puthex_mayus(num / 16);
		printed += ft_putchar_fd(digits[num % 16], 1);
	}
	return (printed);
}
