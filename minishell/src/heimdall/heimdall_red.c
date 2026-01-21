#include "minishell.h"

/* =============================== */
/* ======== heimdall_red ========= */
/* =============================== */

int	ft_init_red(t_red *red, t_tree **ygg, int forked)
{
	red->cmd_node = (*ygg)->left;
	red->curr = *ygg;
	red->file_node = NULL;
	red->fd_out = -1;
	red->fd_in = -1;
	if (!forked)
	{
		red->stdin_backup = dup(STDIN_FILENO);
		red->stdout_backup = dup(STDOUT_FILENO);
	}
	red->status = 0;
	red->tmp_fd = -1;
	red->flags = -1;
	return (0);
}

int	ft_case_in(t_red *red, int forked)
{
	red->tmp_fd = open(red->file_node->content[0], O_RDONLY);
	if (red->tmp_fd < 0)
	{
		if (!forked)
		{
			close(red->stdin_backup);
			close(red->stdout_backup);
		}
		return (1);
	}
	if (red->fd_in != -1)
		close(red->fd_in);
	red->fd_in = red->tmp_fd;
	return (0);
}

int	ft_case_out(t_red *red, int forked)
{
	red->flags = O_CREAT | O_WRONLY;
	if (red->curr->type == T_REDIR_OUT)
		red->flags |= O_TRUNC;
	else
		red->flags |= O_APPEND;
	red->tmp_fd = open(red->file_node->content[0], red->flags, 0644);
	if (red->tmp_fd < 0)
	{
		if (!forked)
		{
			close(red->stdin_backup);
			close(red->stdout_backup);
		}
		return (1);
	}
	if (red->fd_out != -1)
		close(red->fd_out);
	red->fd_out = red->tmp_fd;
	return (0);
}

void	ft_redir_aux(t_data **data, char **env, t_red *red, int forked)
{
	if (red->fd_in != -1)
	{
		dup2(red->fd_in, STDIN_FILENO);
		close(red->fd_in);
	}
	if (red->fd_out != -1)
	{
		dup2(red->fd_out, STDOUT_FILENO);
		close(red->fd_out);
	}
	if (red->cmd_node)
		red->status = ft_heimdall(data, &red->cmd_node, env, forked);
	if (!forked)
	{
		if (red->stdin_backup != -1)
		{
			dup2(red->stdin_backup, STDIN_FILENO);
			close(red->stdin_backup);
		}
		if (red->stdout_backup != -1)
		{
			dup2(red->stdout_backup, STDOUT_FILENO);
			close(red->stdout_backup);
		}
	}
}

int	ft_heimdall_redir(t_data **data, t_tree **ygg, char **env, int forked)
{
	t_red	red;

	ft_init_red(&red, ygg, forked);
	while (red.curr && ft_is_red(red.curr->type))
	{
		if (red.curr->right && ft_is_red(red.curr->right->type))
			red.file_node = red.curr->right->left;
		else
			red.file_node = red.curr->right;
		if (red.curr->type == T_REDIR_IN)
		{
			if (ft_case_in(&red, forked))
				return (ft_pd_error(NO_FILE_DIR, red.file_node->content[0], 1));
		}
		else
			if (ft_case_out(&red, forked))
				return (ft_pd_error(NO_FILE_DIR, red.file_node->content[0], 1));
		if (red.curr->right && ft_is_red(red.curr->right->type))
			red.curr = red.curr->right;
		else
			break ;
	}
	ft_redir_aux(data, env, &red, forked);
	return (red.status);
}
