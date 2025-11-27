#include "../minishell.h"

/* ========================== */
/* ==========utils=========== */
/* ========================== */

void	ft_random_banner(void)
{
	pid_t	pid;
	int		banner_choice;

	pid = getpid();
	banner_choice = (pid % 4) + 1;

	if (banner_choice == 1)
		ft_banner_1();
	else if (banner_choice == 2)
		ft_banner_2();
	else if (banner_choice == 3)
		ft_banner_3();
	else
		ft_banner_4a();
}

int	ft_find_path(t_data **data, char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			(*data)->path = ft_strdup(envp[i]);
			if (!(*data)->path)
				return (ft_print_error(12, NULL));
			break ;
		}
		i++;
	}
	if (!(*data)->path)
	{
		// ft_print_error(0, "Error: PATH variable not found in environment\n");
		return (1);
	}
	return (0);
}

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
