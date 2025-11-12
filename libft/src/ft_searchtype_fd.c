/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_searchtype_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrosio <jbrosio@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 09:19:33 by jbrosio           #+#    #+#             */
/*   Updated: 2025/11/10 21:42:28 by jbrosio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_searchtype_fd(va_list vargs, char c, int fd)
{
	unsigned int	printed;

	printed = 0;
	if (c == 'c')
		printed += ft_putchar_fd(va_arg(vargs, int), fd);
	else if (c == 's')
		printed += ft_putstr_fd(va_arg(vargs, char *), fd);
	else if (c == 'd' || c == 'i')
		printed += ft_putnbr_fd(va_arg(vargs, int), fd);
	else if (c == 'u')
		printed += ft_putnbr_u_fd(va_arg(vargs, unsigned int), fd);
	else if (c == '%')
		printed += ft_putchar_fd('%', fd);
	else if (c == 'p')
		printed += puthex_p_fd((unsigned long long)va_arg(vargs,
					unsigned long long), fd);
	else if (c == 'x')
		printed += puthex_x_fd((unsigned int)va_arg(vargs, unsigned int), fd);
	else if (c == 'X')
		printed += puthex_X_fd((unsigned int)va_arg(vargs, unsigned int), fd);
	return (printed);
}
