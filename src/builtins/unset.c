#include "minishell.h"

// =================== //
// ====== UNSET ====== //
// =================== //

int	ft_get_var_unset(char **env, char *av)
{
	int		i;
	int		len;

	len = 0;
	if (!env || !*env)
		return (-1);
	while (av[len] && av[len] != '=')
		len++;
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], av, len))
			return (i);
		i++;
	}
	return (-1);
}

int	ft_validate_av_unset(char *av)
{
	int	i;

	if (!ft_isalpha(av[0]) && av[0] != '_')
		return (1);
	i = 1;
	while (av[i])
	{
		if (!ft_isalnum(av[i]) && av[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

int	ft_unset_var(char ***env, char *av)
{
	int	i;

	i = ft_get_var_unset(*env, av);
	if (i != -1)
	{
		if ((*env)[i])
			free((*env)[i]);
		while ((*env)[i + 1])
		{
			(*env)[i] = (*env)[i + 1];
			i++;
		}
		(*env)[i] = NULL;
	}
	return (0);
}

int	ft_unset(char ***env, char **av)
{
	int		i;

	if (!av || !(*av))
		return (0);
	i = 0;
	while (av[i])
	{
		if (ft_validate_av_unset(av[i]))
			ft_pd_error(ERR_UNSET_INVALID, av[i], 1);
		else
			ft_unset_var(env, av[i]);
		i++;
	}
	return (0);
}
