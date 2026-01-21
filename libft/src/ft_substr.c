/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrosio <jbrosio@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 16:47:15 by jbrosio           #+#    #+#             */
/*   Updated: 2025/11/10 20:49:35 by jbrosio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned char	*cpy;
	size_t			i;

	i = 0;
	if (start > ft_strlen(s))
	{
		cpy = (unsigned char *)malloc(1 * sizeof(char));
		if (!cpy)
			return (NULL);
		cpy[i] = '\0';
		return ((char *)cpy);
	}
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	cpy = (unsigned char *)malloc((len + 1) * sizeof(char));
	if (!cpy)
		return (NULL);
	ft_memcpy(cpy, s + start, len);
	cpy[len] = '\0';
	return ((char *)cpy);
}
