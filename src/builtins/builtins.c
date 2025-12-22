#include "minishell.h"

/* ========================== */
/* ======== builtin ========= */
/* ========================== */

static int	ft_count_words(char **av)
{
	int	i;

	i = 0;
	if (!av)
		return (0);
	while (av[i])
		i++;
	return (i);
}

int	ft_builtins(t_data **data, char **av, char **env)
{
	// printf("hola\n");
	if (!ft_strcmp("cd", av[0]))
		return (ft_cd(&(*data)->env, av[1]));
	else if (!ft_strcmp("echo", av[0]))
		return (ft_echo(ft_count_words(av), av));
	else if (!ft_strcmp("env", av[0]))
		return (ft_env(env));
	else if (!ft_strcmp("exit", av[0]))
		return (ft_exit(data, &(*data)->env, av + 1));
	else if (!ft_strcmp("export", av[0]))
		return (ft_export(&(*data)->env, av + 1));
	else if (!ft_strcmp("pwd", av[0]))
		return (ft_pwd());
	else if (!ft_strcmp("unset", av[0]))
		return (ft_unset(&(*data)->env, av + 1));
	return (0);
}