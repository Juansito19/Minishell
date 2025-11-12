/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_int_tab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrosio <jbrosio@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:24:02 by ancanale          #+#    #+#             */
/*   Updated: 2025/11/10 20:39:34 by jbrosio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_sort_int_tab(int *tab, int size)
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
			if ((tab[i] > tab[i + 1]))
			{
				temp = tab[i + 1];
				tab[i + 1] = tab[i];
				tab[i] = temp;
			}
			i++;
		}
		j++;
		i = 0;
	}
}
