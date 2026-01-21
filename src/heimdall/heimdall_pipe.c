/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heimdall_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrosio <jbrosio@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 19:09:18 by jbrosio           #+#    #+#             */
/*   Updated: 2026/01/20 17:56:53 by jbrosio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ================================ */
/* ======== heimdall_pipe ========= */
/* ================================ */

void	ft_left_child(t_data **data, t_tree **ygg, char **env, int forked)
{
	int	status;

	forked = 1;
	ft_child_signal();
	close((*ygg)->pipe[0]);
	dup2((*ygg)->pipe[1], STDOUT_FILENO);
	close((*ygg)->pipe[1]);
	if ((*ygg)->left)
		ft_heimdall(data, &(*ygg)->left, env, forked);
	if (g_status == 130 || g_status == 131)
		status = g_status;
	else
		status = (*data)->exit_status;
	ft_clean_data(data);
	exit(status);
}

void	ft_right_child(t_data **data, t_tree **ygg, char **env, int forked)
{
	int	status;

	forked = 1;
	ft_child_signal();
	close((*ygg)->pipe[1]);
	dup2((*ygg)->pipe[0], STDIN_FILENO);
	close((*ygg)->pipe[0]);
	if ((*ygg)->right)
		ft_heimdall(data, &(*ygg)->right, env, forked);
	if (g_status == 130 || g_status == 131)
		status = g_status;
	else
		status = (*data)->exit_status;
	ft_clean_data(data);
	exit(status);
}

int	ft_left_process(t_data **data, t_tree **ygg, char **env, int forked)
{
	int	left_pid;

	left_pid = fork();
	if (!left_pid)
		ft_left_child(data, ygg, env, forked);
	return (left_pid);
}

int	ft_right_process(t_data **data, t_tree **ygg, char **env, int forked)
{
	int	right_pid;

	right_pid = fork();
	if (!right_pid)
		ft_right_child(data, ygg, env, forked);
	return (right_pid);
}

int	ft_heimdall_pipe(t_data **data, t_tree **ygg, char **env, int forked)
{
	int	left_pid;
	int	right_pid;
	int	status;

	(void)env;
	if (pipe((*ygg)->pipe))
		return (ft_pd_error(ERR_PIPE_FAILED, NULL, 32));
	left_pid = ft_left_process(data, ygg, env, forked);
	right_pid = ft_right_process(data, ygg, env, forked);
	close((*ygg)->pipe[0]);
	close((*ygg)->pipe[1]);
	waitpid(left_pid, NULL, 0);
	waitpid(right_pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		if (forked)
			ft_exit_clean_child(data, status);
		return (128 + WTERMSIG(status));
	}
	if (forked)
	{
		ft_clean_data(data);
		exit(WEXITSTATUS(status));
	}
	return (WEXITSTATUS(status));
}
