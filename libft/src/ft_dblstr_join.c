/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dblstr_join.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrosio <jbrosio@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 20:14:56 by jbrosio           #+#    #+#             */
/*   Updated: 2025/11/18 12:36:28 by jbrosio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_dblstr_join(char **str)
{
	char	*res;
	char	*tmp;
	int		i;

	i = -1;
	res = ft_strdup("");
	if (!res)
		return (NULL);
	while (str[++i])
	{
		if (i > 0)
		{
			tmp = ft_strjoin(res, " ");
			free(res);
			res = tmp;
			if (!res)
				return (NULL);
		}
		tmp = ft_strjoin(res, str[i]);
		free(res);
		res = tmp;
		if (!res)
			return (NULL);
	}
	return (res);
}
