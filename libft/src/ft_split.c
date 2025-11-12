/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrosio <jbrosio@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:45:54 by jbrosio           #+#    #+#             */
/*   Updated: 2025/11/10 20:49:35 by jbrosio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	**free_all_array(char **big)
{
	int	i;

	i = 0;
	while (big[i])
	{
		free(big[i]);
		i++;
	}
	free(big);
	return (NULL);
}

static int	counter(const char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

static char	**array_const(char const *s1, char **big, char c, int count)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i] && j < count)
	{
		if (s1[i] != c)
		{
			big[j] = ft_substr(s1, i, counter(&s1[i], c));
			if (!big[j])
				return (free_all_array(big));
			j++;
			i = i + (counter(&s1[i], c));
		}
		i++;
	}
	return (big);
}

static int	count_words(char const *str, char c)
{
	int	i;
	int	sep_flag;
	int	count;

	i = -1;
	sep_flag = 1;
	count = 0;
	if (*str == '\0')
		return (0);
	while (str[++i])
	{
		if (str[i] == c)
			sep_flag = 1;
		if (str[i] != c && sep_flag != 0)
		{
			sep_flag = 0;
			count++;
		}
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	char	**big;
	int		count;

	if (!s)
		return (NULL);
	count = count_words(s, c);
	big = ft_calloc((count + 1), sizeof(char *));
	if (!big)
		return (NULL);
	big[count] = NULL;
	return (array_const(s, big, c, count));
}
