/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_nodes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrosio <jbrosio@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 20:17:50 by jbrosio           #+#    #+#             */
/*   Updated: 2025/11/10 20:49:35 by jbrosio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_free_nodes(void **head)
{
	t_list	*current;
	t_list	*next;

	current = (t_list *)(*head);
	if (!(*head))
		return ;
	while (1)
	{
		next = current->next;
		free(current);
		current = next;
		if (current == (*head))
			break ;
	}
}
