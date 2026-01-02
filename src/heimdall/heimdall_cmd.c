#include "minishell.h"

/* =============================== */
/* ======== heimdall_cmd ========= */
/* =============================== */

// int	ft_heimdall_cmd(t_data **data, t_tree **ygg, char **env, int forked)
// {
// 	char	**av;
// 	int		status;

// 	status = 0;
// 	av = (*ygg)->content;
// 	if ((*ygg)->type == T_BUILTIN)
// 	{
// 		status = ft_builtins(data, av, env);
// 		if (forked)
// 			exit(status);
// 		return (status);
// 	}
// 	if (ft_bifrost(ygg))
// 	{
// 		if (forked)
// 			exit(127);
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

int	ft_heimdall_cmd(t_data **data, t_tree **ygg, char **env, int forked)
{
	char	**av;
	int		status;

	status = 0;
	av = (*ygg)->content;
	if ((*ygg)->type == T_BUILTIN)
	{
		status = ft_builtins(data, av, env);
		if (forked)
		{
			ft_clean_data(data);
			exit(status);
		}
		return (status);
	}
	if (ft_bifrost(ygg))
	{
		if (forked)
		{
			ft_clean_data(data);
			exit(127);
		}
		return (127);
	}
	if (forked)
	{
		if (execve(av[0], av, env) < 0)
			exit(ft_pd_error(ERR_EXECVE, NULL, 126));
	}
	else
	{
		(*ygg)->pid = fork();
		if ((*ygg)->pid == -1)
			return (WEXITSTATUS(status));
		if ((*ygg)->pid == 0)
		{
			ft_odinson_signal();
			if (execve(av[0], av, env) < 0)
				exit(ft_pd_error(ERR_EXECVE, NULL, 126));
		}
		else
		{
			waitpid((*ygg)->pid, &status, 0);
			return (WEXITSTATUS(status));
		}
	}
	return (0);
}
