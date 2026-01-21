/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mimir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrosio <jbrosio@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 19:09:31 by jbrosio           #+#    #+#             */
/*   Updated: 2026/01/15 19:09:32 by jbrosio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ============================ */
/* ======== mimir utils ======= */
/* ============================ */

void	ft_aux_need_to_expand(t_token **tkn, int state)
{
	int		i;

	i = 0;
	while ((*tkn)->content[i] && (*tkn)->expand == 0)
	{
		if (ft_is_quote((*tkn)->content[i]) == T_DQUOTE && !state)
			state = 2;
		else if (ft_is_quote((*tkn)->content[i]) == T_DQUOTE && state == 2)
			state = 0;
		else if (ft_is_quote((*tkn)->content[i]) == T_SQUOTE && !state)
			state = 1;
		else if (ft_is_quote((*tkn)->content[i]) == T_SQUOTE && state == 1)
			state = 0;
		if ((*tkn)->content[i] == '$' && state != 1 && (*tkn)->content[i + 1])
			(*tkn)->expand = 1;
		i++;
	}
}

void	ft_need_to_expand(t_token **token)
{
	t_token	*aux;

	aux = (*token);
	while (aux)
	{
		ft_aux_need_to_expand(&aux, 0);
		aux = aux->next;
	}
}

void	ft_add_char(char **s, char c)
{
	char	*tmp;
	char	str[2];

	str[0] = c;
	str[1] = '\0';
	if (!*s)
		*s = ft_strdup("");
	tmp = ft_strjoin(*s, str);
	free(*s);
	*s = tmp;
}

void	ft_add_str(char **s, char *add)
{
	char	*tmp;

	if (!add)
		return ;
	if (!*s)
		*s = ft_strdup("");
	tmp = ft_strjoin(*s, add);
	free(*s);
	free(add);
	*s = tmp;
}
