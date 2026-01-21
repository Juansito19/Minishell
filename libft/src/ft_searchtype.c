/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_searchtype.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrosio <jbrosio@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 09:19:33 by jbrosio           #+#    #+#             */
/*   Updated: 2025/11/10 21:49:10 by jbrosio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_searchtype(va_list vargs, char c)
{
	unsigned int	printed;

	printed = 0;
	if (c == 'c')
		printed += ft_putchar_fd(va_arg(vargs, int), 1);
	else if (c == 's')
		printed += ft_putstr_fd(va_arg(vargs, char *), 1);
	else if (c == 'd' || c == 'i')
		printed += ft_putnbr_fd(va_arg(vargs, int), 1);
	else if (c == 'u')
		printed += ft_putnbr_u(va_arg(vargs, unsigned int));
	else if (c == '%')
		printed += ft_putchar_fd('%', 1);
	else if (c == 'p')
		printed += ft_puthex_p((unsigned long long)va_arg(vargs,
					unsigned long long));
	else if (c == 'x')
		printed += ft_puthex_x((unsigned int)va_arg(vargs, unsigned int));
	else if (c == 'X')
		printed += ft_puthex_mayus((unsigned int)va_arg(vargs, unsigned int));
	return (printed);
}
