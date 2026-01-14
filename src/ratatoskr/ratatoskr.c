#include "minishell.h"

/* ========================== */
/* ======= ratatoskr ======== */
/* ========================== */

void	ft_search_eof(t_token **token)
{
	t_token	*aux;
	int		eof;

	eof = 0;
	aux = (*token);
	while (aux)
	{
		if (aux->type == T_HEREDOC)
			eof = 1;
		else if (aux && eof)
		{
			eof = 0;
			aux->type = T_EOF;
		}
		aux = aux->next;
	}
}

void	ft_find_branch_eof(t_token **token, t_token **eof)
{
	if (!token || !(*token))
		return ;
	if ((*token)->type == T_EOF)
	{
		*eof = *token;
		return ;
	}
	ft_find_branch_eof(&(*token)->next, eof);
}

int	ft_new_content(char **tmp_name, t_token **eof, t_token **token)
{
	free((*eof)->content);
	free((*token)->content);
	(*eof)->content = *tmp_name;
	(*eof)->type = T_FD;
	(*token)->type = T_REDIR_IN;
	(*token)->content = ft_strdup("<");
	return (0);
}

int	ft_chg_b(t_token **token, char **tmp_name, int fd, t_token **eof)
{
	char	*line;
	int		stdin_backup;

	stdin_backup = dup(STDIN_FILENO);
	line = NULL;
	while (1)
	{
		if (g_status != 130)
			line = readline("> ");
		if (!line || g_status == 130)
		{
			line = ft_strdup((*eof)->content);
			ft_new_content(tmp_name, eof, token);
			return (ft_signal_break(&line, fd, stdin_backup, eof));
		}
		if (!ft_strcmp(line, (*eof)->content))
			break ;
		ft_fprintf(fd, "%s\n", line);
		free(line);
	}
	free(line);
	close(fd);
	close(stdin_backup);
	ft_new_content(tmp_name, eof, token);
	return (0);
}

int	ft_ratatoskr(t_token **token)
{
	char	*tmp_name;
	int		fd;
	t_token	*eof_token;

	if (!token || !(*token))
		return (0);
	if ((*token)->type == T_HEREDOC)
	{
		tmp_name = ft_make_unic_name();
		if (!tmp_name)
			return (1);
		fd = open(tmp_name, O_CREAT | O_WRONLY, 0644);
		if (fd < 0)
		{
			free(tmp_name);
			return (ft_pd_error(ERR_RATA, NULL, 1));
		}
		ft_munin_signal();
		ft_find_branch_eof(&(*token)->next, &eof_token);
		ft_chg_b(token, &tmp_name, fd, &eof_token);
		ft_hugin_signal();
	}
	ft_ratatoskr(&(*token)->next);
	ft_reset_heredoc_times();
	return (0);
}
