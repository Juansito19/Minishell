/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrosio <jbrosio@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 00:37:48 by jbrosio           #+#    #+#             */
/*   Updated: 2025/05/07 00:37:48 by jbrosio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*n_list;
	t_list	*temp;

	n_list = NULL;
	if (!lst || !f || !del)
		return (NULL);
	while (lst)
	{
		temp = ft_lstnew(NULL);
		if (!temp)
		{
			ft_lstclear(&n_list, del);
			return (NULL);
		}
		temp->content = f(lst->content);
		ft_lstadd_back(&n_list, temp);
		lst = lst->next;
	}
	return (n_list);
}
