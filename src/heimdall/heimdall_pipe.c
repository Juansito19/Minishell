#include "minishell.h"

/* ================================ */
/* ======== heimdall_pipe ========= */
/* ================================ */

// int	ft_heimdall_pipe(t_data **data, t_tree **ygg, char **env, int forked)
// {
// 	int	left_pid;
// 	int	right_pid;
// 	int	status;

// 	status = 0;
// 	if (pipe((*ygg)->pipe)) // Hay que ver como le damos valor a exit_status a la hora de terminar
// 		return (ft_pd_error(ERR_PIPE_FAILED, NULL, 32));
// 	left_pid = fork();
// 	if (!left_pid)
// 	{
// 		ft_odinson_signal();
// 		forked = 1;
// 		close((*ygg)->pipe[0]);
// 		dup2((*ygg)->pipe[1], STDOUT_FILENO);
// 		close((*ygg)->pipe[1]);
// 		if ((*ygg)->left)
// 			ft_heimdall(data, &(*ygg)->left, env, forked);
// 		exit(status);
// 	}
// 	right_pid = fork();
// 	if (!right_pid)
// 	{
// 		ft_odinson_signal();
// 		forked = 1;
// 		close((*ygg)->pipe[1]);
// 		dup2((*ygg)->pipe[0], STDIN_FILENO);
// 		close((*ygg)->pipe[0]);
// 		if ((*ygg)->right)
// 			ft_heimdall(data, &(*ygg)->right, env, forked);
// 		exit(status);
// 	}
// 	close((*ygg)->pipe[0]);
// 	close((*ygg)->pipe[1]);
// 	waitpid(left_pid, NULL, 0);
// 	waitpid(right_pid, &status, 0);
// 	if (forked)
// 		exit(WEXITSTATUS(status));
// 	return (WEXITSTATUS(status));
// }

int	ft_heimdall_pipe(t_data **data, t_tree **ygg, char **env, int forked)
{
	int	left_pid;
	int	right_pid;
	int	status;

	status = 0;
	(void)env;
	if (pipe((*ygg)->pipe))
		return (ft_pd_error(ERR_PIPE_FAILED, NULL, 32));
	left_pid = fork();
	if (!left_pid)
	{
		forked = 1;
		ft_odinson_signal();
		close((*ygg)->pipe[0]);
		dup2((*ygg)->pipe[1], STDOUT_FILENO);
		close((*ygg)->pipe[1]);
		if ((*ygg)->left)
			ft_heimdall(data, &(*ygg)->left, env, forked);
		status = (*data)->exit_status;
		ft_clean_data(data);
		exit(status);
	}
	// close((*ygg)->pipe[1]);
	// waitpid(left_pid, NULL, 0);
	right_pid = fork();
	if (!right_pid)
	{
		forked = 1;
		ft_odinson_signal();
		close((*ygg)->pipe[1]);
		dup2((*ygg)->pipe[0], STDIN_FILENO);
		close((*ygg)->pipe[0]);
		if ((*ygg)->right)
			ft_heimdall(data, &(*ygg)->right, env, forked);
		status = (*data)->exit_status;
		ft_clean_data(data);
		exit(status);
	}
	close((*ygg)->pipe[1]);
	close((*ygg)->pipe[0]);
	waitpid(left_pid, NULL, 0);
	waitpid(right_pid, &status, 0);
	if (forked)
	{
		ft_clean_data(data);
		exit(WEXITSTATUS(status));
	}
	return (WEXITSTATUS(status));
}

// esta funcion queda porque en este caso:
// bostero$> ls "" | ls ""
// /usr/bin/ls: cannot access '': No such file or directory
// /usr/bin/ls: cannot access '': No such file or directory
// salen los mensajes solapados

// int	ft_heimdall_pipe(t_data **data, t_tree **ygg, char **env, int forked)
// {
// 	int	left_pid;
// 	int	right_pid;
// 	int	status;

// 	status = 0;
// 	(void)env;
// 	if (pipe((*ygg)->pipe))
// 		return (ft_pd_error(ERR_PIPE_FAILED, NULL, 32));
// 	left_pid = fork();
// 	if (!left_pid)
// 	{
// 		forked = 1;
// 		// status = ft_left_pid(status, ygg, data, &forked);
// 		ft_odinson_signal();
// 		close((*ygg)->pipe[0]);
// 		dup2((*ygg)->pipe[1], STDOUT_FILENO);
// 		close((*ygg)->pipe[1]);
// 		if ((*ygg)->left)
// 			ft_heimdall(data, &(*ygg)->left, env, forked);
// 		status = (*data)->exit_status;
// 		ft_clean_data(data);
// 		exit(status);
// 	}
// 	right_pid = fork();
// 	if (!right_pid)
// 	{
// 		forked = 1;
// 		// status = ft_right_pid(status, ygg, data, &forked);
// 		ft_odinson_signal();
// 		close((*ygg)->pipe[1]);
// 		dup2((*ygg)->pipe[0], STDIN_FILENO);
// 		close((*ygg)->pipe[0]);
// 		if ((*ygg)->right)
// 			ft_heimdall(data, &(*ygg)->right, env, forked);
// 		status = (*data)->exit_status;
// 		ft_clean_data(data);
// 		exit(status);
// 	}
// 	close((*ygg)->pipe[0]);
// 	close((*ygg)->pipe[1]);
// 	waitpid(left_pid, NULL, 0);
// 	waitpid(right_pid, &status, 0);
// 	if (forked)
// 	{
// 		ft_clean_data(data);
// 		exit(WEXITSTATUS(status));
// 	}
// 	return (WEXITSTATUS(status));
// }
