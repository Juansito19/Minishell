/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrosio <jbrosio@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 16:34:25 by jbrosio           #+#    #+#             */
/*   Updated: 2025/11/10 20:49:35 by jbrosio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strdup(const char *s)
{
	unsigned char	*cpy;
	size_t			i;
	size_t			size;

	i = 0;
	size = ft_strlen(s);
	cpy = (unsigned char *)malloc((size + 1) * sizeof(char));
	if (!cpy)
		return (NULL);
	while (i < size)
	{
		cpy[i] = (unsigned char)s[i];
		i++;
	}
	cpy[i] = '\0';
	return ((char *)cpy);
}
