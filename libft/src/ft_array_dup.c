/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_dup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrosio <jbrosio@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 23:00:43 by jbrosio           #+#    #+#             */
/*   Updated: 2025/11/30 23:00:56 by jbrosio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	**ft_array_dup(char **s)
{
	char	**res;
	int		size;
	int		i;

	i = 0;
	size = 0;
	while (s[size])
		size++;
	res = ft_calloc(size + 1, sizeof(char *));
	if (!res)
		return (NULL);
	while (s[i] && size > 0)
	{
		res[i] = ft_strdup(s[i]);
		if (!res[i])
			return (ft_free_all_array(res));
		i++;
		size--;
	}
	return (res);
}
