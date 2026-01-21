/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yggdrasil_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrosio <jbrosio@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 19:11:34 by jbrosio           #+#    #+#             */
/*   Updated: 2026/01/15 19:11:35 by jbrosio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ================================= */
/* ======= yggdrasil utils ========= */
/* ================================= */

t_tree	*ft_tree_init(char **content, t_type type, char **env)
{
	t_tree	*new_tree;

	new_tree = (t_tree *)malloc(1 * sizeof(t_tree));
	if (!new_tree)
		return (NULL);
	new_tree->right = NULL;
	new_tree->left = NULL;
	new_tree->infile = -1;
	new_tree->outfile = -1;
	new_tree->pid = 0;
	new_tree->pipe[0] = -1;
	new_tree->pipe[1] = -1;
	new_tree->path = NULL;
	ft_find_path(&new_tree, env);
	new_tree->type = type;
	new_tree->content = content;
	return (new_tree);
}

t_token	*ft_search_pipe(t_token **tokens)
{
	t_token	*tmp;

	tmp = (*tokens);
	if (!tokens || !(*tokens))
		return (NULL);
	while (tmp)
	{
		if (tmp->type == T_PIPE)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

t_token	*ft_search_red(t_token **tokens)
{
	t_token	*tmp;

	tmp = (*tokens);
	if (!tokens || !(*tokens))
		return (NULL);
	while (tmp)
	{
		if (ft_is_red(tmp->type))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}
