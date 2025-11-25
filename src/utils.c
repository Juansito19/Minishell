#include "../minishell.h"

/* ========================== */
/* ==========utils=========== */
/* ========================== */

int	ft_is_metachar(char c)
{
	if (c == 34)
		return (T_DQUOTE);
	if (c == 39)
		return (T_SQUOTE);
	if (c == 60)
		return (T_REDIR_IN);
	if (c == 62)
		return (T_REDIR_OUT);
	if (c == 124)
		return (T_PIPE);
	return (0);
}

t_token_type	ft_is_red(char *content)
{
	if (!ft_strncmp(content, "<", 2))
		return (T_REDIR_IN);
	else if (!ft_strncmp(content, ">", 2))
		return (T_REDIR_OUT);
	else if (!ft_strncmp(content, "<<", 3))
		return (T_HEREDOC);
	else if (!ft_strncmp(content, ">>", 3))
		return (T_APPEND);
	return (0);
}

t_token_type	ft_take_meta(char *content)
{
	if (!ft_strncmp(content, "|", 2))
		return (T_PIPE);
	else if (!ft_strncmp(content, "<<", 3))
		return (T_HEREDOC);
	else if (!ft_strncmp(content, ">>", 3))
		return (T_APPEND);
	else if (!ft_strncmp(content, "<", 2))
		return (T_REDIR_IN);
	else if (!ft_strncmp(content, ">", 2))
		return (T_REDIR_OUT);
	return (0);
}

t_token_type	ft_is_builtin(t_token *token)
{
	if (!ft_strncmp(token->content, "echo", 5))
		return (T_BUILTIN);
	else if (!ft_strncmp(token->content, "cd", 3))
		return (T_BUILTIN);
	else if (!ft_strncmp(token->content, "pwd", 4))
		return (T_BUILTIN);
	else if (!ft_strncmp(token->content, "export", 7))
		return (T_BUILTIN);
	else if (!ft_strncmp(token->content, "unset", 6))
		return (T_BUILTIN);
	else if (!ft_strncmp(token->content, "exit", 5))
		return (T_BUILTIN);
	else if (!ft_strncmp(token->content, "env", 4))
		return (T_BUILTIN);
	return (T_CMD);
}
