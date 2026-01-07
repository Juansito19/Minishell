#include "minishell.h"

/* =============================== */
/* ======== heimdall_cmd ========= */
/* =============================== */

int	ft_handle_builtin(t_data **data, char **av, int forked)
{
	int	status;

	status = ft_builtins(data, av, (*data)->env);
	if (forked)
	{
		ft_clean_data(data);
		exit(status);
	}
	return (status);
}

int	ft_handle_bifrost_error(t_data **data, int forked)
{
	if (forked)
	{
		ft_clean_data(data);
		exit(127);
	}
	return (127);
}

void	ft_exec_child(t_data **data, char **av, char **env)
{
	ft_odinson_signal();
	if (execve(av[0], av, env) < 0)
	{
		ft_clean_data(data);
		exit(ft_pd_error(ERR_EXECVE, NULL, 126));
	}
}

int	ft_exec_parent(t_data **data, t_tree **ygg, char **av, char **env)
{
	int	status;

	status = 0;
	(*ygg)->pid = fork();
	if ((*ygg)->pid == -1)
		return (1);
	if ((*ygg)->pid == 0)
		ft_exec_child(data, av, env);
	waitpid((*ygg)->pid, &status, 0);
	return (WEXITSTATUS(status));
}

int	ft_heimdall_cmd(t_data **data, t_tree **ygg, char **env, int forked)
{
	char	**av;

	av = (*ygg)->content;
	if ((*ygg)->type == T_BUILTIN)
		return (ft_handle_builtin(data, av, forked));
	if (ft_bifrost(ygg))
		return (ft_handle_bifrost_error(data, forked));
	if (forked)
	{
		if (execve(av[0], av, env) < 0)
			exit(ft_pd_error(ERR_EXECVE, NULL, 126));
	}
	return (ft_exec_parent(data, ygg, av, env));
}

// int	ft_heimdall_cmd(t_data **data, t_tree **ygg, char **env, int forked)
// {
// 	char	**av;
// 	int	status;

// 	status = 0;
// 	av = (*ygg)->content;
// 	if ((*ygg)->type == T_BUILTIN)
// 	{
// 		status = ft_builtins(data, av, env);
// 		if (forked)
// 		{
// 			ft_clean_data(data);
// 			exit(status);
// 		}
// 		return (status);
// 	}
// 	if (ft_bifrost(ygg))
// 	{
// 		if (forked)
// 		{
// 			ft_clean_data(data);
// 			exit(127);
// 		}
// 		return (127);
// 	}
// 	if (forked)
// 	{
// 		if (execve(av[0], av, env) < 0)
// 			exit(ft_pd_error(ERR_EXECVE, NULL, 126));
// 	}
// 	else
// 	{
// 		(*ygg)->pid = fork();
// 		if ((*ygg)->pid == -1)
// 			return (WEXITSTATUS(status));
// 		if ((*ygg)->pid == 0)
// 		{
// 			ft_odinson_signal();
// 			if (execve(av[0], av, env) < 0)
// 				exit(ft_pd_error(ERR_EXECVE, NULL, 126));
// 		}
// 		else
// 		{
// 			waitpid((*ygg)->pid, &status, 0);
// 			return (WEXITSTATUS(status));
// 		}
// 	}
// 	return (0);
// }
