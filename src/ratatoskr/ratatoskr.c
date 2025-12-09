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
		else if (aux->type == T_WORD && eof)
		{
			eof = 0;
			aux->type = T_EOF;
		}
		aux = aux->next;
	}
}

void	ft_find_branch_eof(t_tree **yggdrasil, t_tree **eof)
{
	if (!yggdrasil || !(*yggdrasil))
		return ;
	if ((*yggdrasil)->type == T_EOF)
	{
		*eof = *yggdrasil;
		return ;
	}
	ft_find_branch_eof(&(*yggdrasil)->left, eof);
	ft_find_branch_eof(&(*yggdrasil)->right, eof);
}

int	ft_new_content(char **tmp_name, t_tree **eof_branch, t_tree **yggdrasil)
{
	char	**tmp;

	tmp = malloc(2 * sizeof(char *));
	if (!tmp)
	{
		free(*tmp_name);
		return (ft_pd_error(ERR_MALLOC, NULL, 12));
	}
	tmp[0] = *tmp_name;
	tmp[1] = NULL;
	(*eof_branch)->content = tmp;
	(*eof_branch)->type = T_FD;
	(*yggdrasil)->type = T_REDIR_IN;
	return (0);
}

int	ft_chg_b(t_tree **yggdrasil, char **tmp_name, int fd, t_tree **eof_branch)
{
	char	*line;

	while (1)
	{
		line = readline("> "); // SEÑALES DE CTRL_C || CTRL_D
		if (!line)
		{
			free(*tmp_name);
			close(fd);
			return (1);
		}
		if (!ft_strcmp(line, (*eof_branch)->content[0]))
			break ;
		ft_fprintf(fd, "%s\n", line);
		free(line);
		line = NULL;
	}
	close(fd);
	ft_free_all(NULL, NULL, &line, &(*eof_branch)->content);
	ft_new_content(tmp_name, eof_branch, yggdrasil);
	return (0);
}

int	ft_ratatoskr(t_tree **yggdrasil)
{
	char	*tmp_name;
	int		fd;
	t_tree	*eof_branch;

	if (!yggdrasil || !(*yggdrasil))
		return (0);
	if ((*yggdrasil)->type == T_HEREDOC)
	{
		tmp_name = ft_make_unic_name();
		if (!tmp_name)
			return (1);
		fd = open(tmp_name, O_CREAT | O_WRONLY, 0644);
		ft_find_branch_eof(&(*yggdrasil)->right, &eof_branch);
		ft_chg_b(yggdrasil, &tmp_name, fd, &eof_branch);
	}
	ft_ratatoskr(&(*yggdrasil)->left);
	ft_ratatoskr(&(*yggdrasil)->right);
	return (0);
}
