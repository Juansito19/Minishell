/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrosio <jbrosio@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 15:44:19 by jbrosio           #+#    #+#             */
/*   Updated: 2025/11/10 20:49:35 by jbrosio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	size_t	d;

	i = 0;
	d = 0;
	if ((char)c == '\0')
		return ((char *)s + ft_strlen(s));
	while (i < ft_strlen(s))
	{
		if (s[i] == (char)c)
			d = i;
		i++;
	}
	if (s[d] == (char)c)
		return ((char *)(s + d));
	else
		return (NULL);
}
