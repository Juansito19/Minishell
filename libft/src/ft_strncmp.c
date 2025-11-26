/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrosio <jbrosio@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 11:56:22 by jbrosio           #+#    #+#             */
/*   Updated: 2025/11/26 16:16:30 by jbrosio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	res;

	i = 0;
	res = 0;
	if (!s1 || !s2)
		return (-1);
	while ((s1[i] || s2[i]) && (i < n) && (res == 0))
	{
		if (s1[i] != s2[i])
			res = (unsigned char)s1[i] - (unsigned char)s2[i];
		i++;
	}
	return ((int)res);
}
