/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrosio <jbrosio@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 15:00:01 by jbrosio           #+#    #+#             */
/*   Updated: 2025/11/10 21:43:57 by jbrosio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_fprintf(int fd, char const *s, ...)
{
	va_list			vargs;
	unsigned int	i;
	unsigned int	printed;

	printed = 0;
	va_start(vargs, s);
	i = 0;
	while (s[i])
	{
		if (s[i] == '%')
		{
			printed += ft_searchtype_fd(vargs, s[i + 1], fd);
			i += 2;
		}
		else
		{
			printed += ft_putchar_fd(s[i], fd);
			i++;
		}
	}
	va_end(vargs);
	return (printed);
}
