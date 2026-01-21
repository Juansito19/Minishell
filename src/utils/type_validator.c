/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_validator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrosio <jbrosio@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 19:11:22 by jbrosio           #+#    #+#             */
/*   Updated: 2026/01/15 19:11:23 by jbrosio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* =================================== */
/* ========= type_validator ========== */
/* =================================== */

int	ft_is_metachar(char c)
{
	if (c == 60)
		return (T_REDIR_IN);
	if (c == 62)
		return (T_REDIR_OUT);
	if (c == 124)
		return (T_PIPE);
	return (0);
}

t_type	ft_is_quote(char c)
{
	if (c == 34)
		return (T_DQUOTE);
	if (c == 39)
		return (T_SQUOTE);
	return (0);
}

t_type	ft_is_red(t_type type)
{
	if (type == T_REDIR_IN)
		return (T_REDIR_IN);
	else if (type == T_REDIR_OUT)
		return (T_REDIR_OUT);
	else if (type == T_HEREDOC)
		return (T_HEREDOC);
	else if (type == T_APPEND)
		return (T_APPEND);
	return (0);
}

t_type	ft_take_meta(char *content)
{
	if (!ft_strncmp(content, "|", 2))
		return (T_PIPE);
	else if (!ft_strncmp(content, "<", 2))
		return (T_REDIR_IN);
	else if (!ft_strncmp(content, ">", 2))
		return (T_REDIR_OUT);
	else if (!ft_strncmp(content, ">>", 3))
		return (T_APPEND);
	else if (!ft_strncmp(content, "<<", 3))
		return (T_HEREDOC);
	return (0);
}

t_type	ft_is_builtin(t_token **token)
{
	char	*builtins[8];
	int		i;

	if (!token || !(*token) || !(*token)->content)
		return (T_CMD);
	i = -1;
	builtins[0] = "echo";
	builtins[1] = "cd";
	builtins[2] = "pwd";
	builtins[3] = "export";
	builtins[4] = "unset";
	builtins[5] = "exit";
	builtins[6] = "env";
	builtins[7] = NULL;
	while (builtins[++i])
		if (!ft_strcmp(builtins[i], (*token)->content))
			return (T_BUILTIN);
	if ((*token)->type == T_EOF)
		return (T_EOF);
	else if ((*token)->type == T_FD)
		return (T_FD);
	return (T_CMD);
}
