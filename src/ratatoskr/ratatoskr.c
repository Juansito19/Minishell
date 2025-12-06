#include "minishell.h"

/* ========================== */
/* ======= ratatoskr ======== */
/* ========================== */

static void	*ft_free_pointers(char *number, char *tmp)
{
	if (tmp)
		free(tmp);
	if (number)
		free(number);
	return (NULL);
}

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

char	*ft_make_unic_name(void)
{
	static int	n;
	char		*name;
	char		*number;
	char		*tmp;

	name = NULL;
	tmp = ft_strdup(".heredoc_");
	number = ft_itoa(n);
	n++;
	if (!tmp || !number)
	{
		ft_pd_error(ERR_MALLOC, NULL, 12);
		return (ft_free_pointers(number, tmp));
	}
	name = ft_strjoin(tmp, number);
	if (!name)
	{
		ft_pd_error(ERR_MALLOC, NULL, 12);
		return (ft_free_pointers(number, tmp));
	}
	ft_free_pointers(number, tmp);
	return (name);
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

int	ft_ratatoskr(t_tree **yggdrasil)
{
	t_tree	*eof_branch;
	char	*tmp_name;
	char	*line;
	char	**tmp;
	int		fd;

	tmp_name = NULL;
	line = NULL;
	if (!yggdrasil || !(*yggdrasil))
		return (0);
	if ((*yggdrasil)->type == T_HEREDOC)
	{
		tmp_name = ft_make_unic_name();
		if (!tmp_name)
			return (1);
		fd = open(tmp_name, O_CREAT | O_WRONLY, 0644);
		ft_find_branch_eof(&(*yggdrasil)->right, &eof_branch);
		while (1)
		{
			line = readline("> "); // SEÑALES DE CTRL_C || CTRL_D
			if (!ft_strncmp(line, eof_branch->content[0], ft_strlen(line)))
				break ;
			ft_fprintf(fd, "%s", line);
			free(line);
			line = NULL;
		}
		close(fd);
		if (line)
			free(line);
		ft_free_all_array(eof_branch->content);
		tmp = ft_split(tmp_name, ' ');
		if (!tmp)
		{
			free(tmp_name);
			return (ft_pd_error(ERR_MALLOC, NULL, 12));
		}
		eof_branch->content = tmp;
		eof_branch->type = T_FD;
		(*yggdrasil)->type = T_REDIR_IN;
	}
	ft_ratatoskr(&(*yggdrasil)->left);
	ft_ratatoskr(&(*yggdrasil)->right);
	return (0);
}
