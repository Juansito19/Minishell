/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrosio <jbrosio@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:59:48 by jbrosio           #+#    #+#             */
/*   Updated: 2025/11/10 20:49:35 by jbrosio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	r;
	size_t	j;

	i = 0;
	r = ft_strlen(dst) + ft_strlen(src);
	j = ft_strlen(dst);
	if (size <= ft_strlen(dst))
		return (size + ft_strlen(src));
	while ((src[i] != '\0') && (j < size - 1))
	{
		dst[j] = src[i];
		j++;
		i++;
	}
	dst[j] = '\0';
	return (r);
}
