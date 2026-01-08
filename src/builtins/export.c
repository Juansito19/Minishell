#include "minishell.h"

// ==================== //
// ====== EXPORT ====== //
// ==================== //

char	**ft_no_env(void)
{
	char	**env_cpy;
	char	*pwd;

	env_cpy = ft_calloc(4, sizeof(char *));
	if (!env_cpy)
	{
		ft_pd_error(ERR_MALLOC, NULL, 12);
		return (NULL);
	}
	pwd = getcwd(NULL, 0);
	env_cpy[0] = ft_strjoin("PWD=", pwd);
	env_cpy[1] = ft_strdup("SHLVL=1");
	env_cpy[2] = ft_strdup("OLDPWD");
	free(pwd);
	return (env_cpy);
}

int	ft_export_no_av(char **env)
{
	char	**env_cpy;
	int		i;

	i = 0;
	env_cpy = ft_array_dup(env);
	if (!env_cpy)
		return (ft_pd_error(ERR_MALLOC, NULL, 12));
	ft_sort_env(env_cpy);
	while (env_cpy[i])
	{
		ft_fprintf(1, "declare -x \"%s\"\n", env_cpy[i]);
		i++;
	}
	ft_free_all_array(env_cpy);
	return (0);
}

int	ft_validate_av_export(char *av)
{
	int	i;

	if (!ft_isalpha(av[0]) && av[0] != '_')
		return (1);
	i = 1;
	while (av[i] && av[i] != '=')
	{
		if (!ft_isalnum(av[i]) && av[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

int	ft_get_var(char **env, char *av)
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
		if (!ft_strncmp(env[i], av, len) && env[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

int	ft_export(char ***env, char **av)
{
	int		i;

	if (!av || !(*av))
	{
		if (ft_export_no_av(*env))
			return (1);
		return (0);
	}
	i = 0;
	while (av[i])
	{
		if (ft_validate_av_export(av[i]))
			ft_pd_error(ERR_EXPORT_INVALID, av[i], 1);
		else
		{
			if (ft_change_or_add_var(env, av[i]))
				return (1);
		}
		i++;
	}
	return (0);
}
