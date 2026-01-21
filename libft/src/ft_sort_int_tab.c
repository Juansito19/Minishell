/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_int_tab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrosio <jbrosio@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:24:02 by ancanale          #+#    #+#             */
/*   Updated: 2025/11/18 08:05:11 by jbrosio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_sort_int_tab(int *list, int size)
{
	int	temp;
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < size)
	{
		while (i < size - 1)
		{
			if ((list[i] > list[i + 1]))
			{
				temp = list[i + 1];
				list[i + 1] = list[i];
				list[i] = temp;
			}
			i++;
		}
		j++;
		i = 0;
	}
}
