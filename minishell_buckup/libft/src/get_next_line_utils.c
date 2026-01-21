/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrosio <jbrosio@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 11:35:00 by jbrosio           #+#    #+#             */
/*   Updated: 2025/11/10 20:49:35 by jbrosio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlen_gnl(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

char	*ft_strchr_gnl(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != (char)c)
	{
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)(s + i));
	else
		return (NULL);
}

char	*ft_strdup_gnl(const char *s)
{
	unsigned char	*new_s;
	size_t			i;
	size_t			size;

	i = 0;
	size = ft_strlen((char *)s);
	new_s = (unsigned char *)malloc((size + 1) * sizeof(char));
	if (!new_s)
	{
		return (NULL);
	}
	while (s[i] && i < size)
	{
		new_s[i] = s[i];
		i++;
	}
	new_s[i] = '\0';
	return ((char *)new_s);
}

char	*gnl_substr(char *s, unsigned int start, size_t len, size_t i)
{
	unsigned char	*new_s;
	size_t			size;

	size = ft_strlen((char *)s);
	if (start > size)
	{
		new_s = (unsigned char *)ft_strdup("");
		if (!new_s)
			return (NULL);
		new_s[i] = '\0';
		return ((char *)new_s);
	}
	new_s = (unsigned char *)malloc((len + 1) * sizeof(char));
	if (!new_s)
		return (NULL);
	while (s[start] && i < len)
	{
		new_s[i] = s[start];
		i++;
		start++;
	}
	new_s[i] = '\0';
	return ((char *)new_s);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char			*new_s;
	size_t			i;
	size_t			j;
	size_t			size;

	size = ft_strlen(s1) + ft_strlen(s2);
	new_s = (char *)malloc((size + 1) * sizeof(char));
	if (!new_s)
		return (NULL);
	j = 0;
	i = 0;
	while (s1 && s1[i])
	{
		new_s[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
	{
		new_s[i] = s2[j];
		i++;
		j++;
	}
	new_s[i] = '\0';
	free(s1);
	return (new_s);
}
