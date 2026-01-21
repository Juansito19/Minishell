/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrosio <jbrosio@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 11:06:33 by jbrosio           #+#    #+#             */
/*   Updated: 2025/12/10 21:59:38 by jbrosio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned char	*s3;
	size_t			i;
	size_t			j;
	size_t			size;

	i = -1;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2);
	s3 = (unsigned char *)malloc((size + 1) * sizeof(char));
	if (!s3)
		return (NULL);
	while (s1[++i] != '\0')
		s3[i] = s1[i];
	while (s2[j] != '\0')
	{
		s3[i] = s2[j];
		j++;
		i++;
	}
	s3[i] = '\0';
	return ((char *)s3);
}
