/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_u.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrosio <jbrosio@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:30:49 by jbrosio           #+#    #+#             */
/*   Updated: 2025/11/10 21:49:02 by jbrosio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_putnbr_u(long int n)
{
	char	buffer[10];
	int		printed;
	int		i;

	printed = 0;
	i = 0;
	if (n == 0)
		return (ft_putchar_fd('0', 1));
	while (n > 0)
	{
		buffer[i++] = (n % 10) + '0';
		n /= 10;
	}
	while (i > 0)
		printed += ft_putchar_fd(buffer[--i], 1);
	return (printed);
}
