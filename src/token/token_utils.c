/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrosio <jbrosio@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 19:10:09 by jbrosio           #+#    #+#             */
/*   Updated: 2026/01/15 19:10:10 by jbrosio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ================================= */
/* ========= tokens utils ========== */
/* ================================= */

t_token	*ft_token_init(void *content, t_type type)
{
	t_token	*new_token;

	if (!content)
	{
		ft_pd_error(ERR_MALLOC, NULL, 12);
		return (NULL);
	}
	new_token = (t_token *)malloc(1 * sizeof(t_token));
	if (!new_token)
	{
		ft_pd_error(ERR_MALLOC, NULL, 12);
		return (NULL);
	}
	new_token->next = NULL;
	new_token->expand = 0;
	new_token->content = content;
	new_token->type = type;
	return (new_token);
}

void	ft_tokenadd_back(t_token **tokens, t_token *new)
{
	if (!*tokens)
		(*tokens) = new;
	else
	{
		while ((*tokens)->next)
			tokens = &(*tokens)->next;
		(*tokens)->next = new;
	}
}

int	ft_tk_size(t_token *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
