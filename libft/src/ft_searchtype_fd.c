/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_searchtype_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrosio <jbrosio@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 09:19:33 by jbrosio           #+#    #+#             */
/*   Updated: 2026/01/19 13:00:25 by jbrosio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_searchtype_fd(va_list vargs, char c, int fd)
{
	unsigned int	print;

	print = 0;
	if (c == 'c')
		print += ft_putchar_fd(va_arg(vargs, int), fd);
	else if (c == 's')
		print += ft_putstr_fd(va_arg(vargs, char *), fd);
	else if (c == 'd' || c == 'i')
		print += ft_putnbr_fd(va_arg(vargs, int), fd);
	else if (c == 'u')
		print += ft_putnbr_u_fd(va_arg(vargs, unsigned int), fd);
	else if (c == '%')
		print += ft_putchar_fd('%', fd);
	else if (c == 'p')
		print += puthex_p_fd((unsigned long long)va_arg(vargs,
					unsigned long long), fd);
	else if (c == 'x')
		print += puthex_lower_fd((unsigned int)va_arg(vargs, unsigned int), fd);
	else if (c == 'X')
		print += puthex_upper_fd((unsigned int)va_arg(vargs, unsigned int), fd);
	return (print);
}
