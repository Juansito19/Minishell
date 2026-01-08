#include "minishell.h"

// ================ //
// ====== CD ====== //
// ================ //

char	*ft_get_var_value(char **env, char *key)
{
	char	*search_value;
	char	*value;
	int		i;

	i = -1;
	search_value = ft_strjoin(key, "=");
	if (!search_value)
		return (NULL);
	while (env[++i])
	{
		if (!ft_strncmp(env[i], search_value, ft_strlen(search_value)))
		{
			value = ft_strdup(env[i] + ft_strlen(search_value));
			if (!value)
			{
				free(search_value);
				ft_print_error(0, ERR_MALLOC);
				return (NULL);
			}
			free(search_value);
			return (value);
		}
	}
	free(search_value);
	return (NULL);
}

int	ft_search_oldpwd(char ***env)
{
	int	i;

	i = 0;
	while (ft_strncmp("OLDPWD", (*env)[i], ft_strlen((*env)[i])))
		i++;
	if (!ft_strncmp("OLDPWD", (*env)[i], ft_strlen((*env)[i])))
	{
		if ((*env)[i])
			free((*env)[i]);
		while ((*env)[i + 1])
		{
			(*env)[i] = (*env)[i + 1];
			i++;
		}
		(*env)[i] = NULL;
		return (0);
	}
	else
		return (1);
}

int	ft_update_pwd_vars(char ***env, char *oldpwd)
{
	char	*pwd_now;
	char	*tmp;

	if (oldpwd)
	{
		tmp = ft_strjoin("OLDPWD=", oldpwd);
		if (!tmp)
			return (ft_pd_error(ERR_MALLOC, NULL, 12));
		ft_change_or_add_var(env, tmp);
		ft_search_oldpwd(env);
		free(tmp);
	}
	pwd_now = getcwd(NULL, 0);
	if (pwd_now)
	{
		tmp = ft_strjoin("PWD=", pwd_now);
		if (!tmp)
			return (ft_pd_error(ERR_MALLOC, NULL, 12));
		ft_change_or_add_var(env, tmp);
		free(tmp);
		free(pwd_now);
	}
	return (0);
}

char	*ft_take_path(char ***env, char *av)
{
	char	*path;

	if (!av || !(*av))
	{
		path = ft_get_var_value(*env, "HOME");
		if (!path)
		{
			ft_pd_error(ERR_CD_NO_SUCH_FILE, "HOME", 1);
			return (NULL);
		}
	}
	else if (!ft_strcmp(av, "-"))
	{
		path = ft_get_var_value(*env, "OLDPWD");
		if (!path)
		{
			ft_pd_error(ERR_CD_NO_SUCH_FILE, "OLDPWD", 1);
			return (NULL);
		}
		ft_printf("%s\n", path);
	}
	else
		path = ft_strdup(av);
	return (path);
}

int	ft_cd(char ***env, char *av)
{
	char	*path;
	char	*oldpwd;

	path = ft_take_path(env, av);
	if (!path)
		return (1);
	oldpwd = getcwd(NULL, 0);
	if (chdir(path))
	{
		free(oldpwd);
		free(path);
		return (ft_pd_error(ERR_CD_NO_SUCH_FILE, path, 1));
	}
	if (ft_update_pwd_vars(env, oldpwd))
	{
		free(oldpwd);
		free(path);
		return (1);
	}
	free(oldpwd);
	free(path);
	return (0);
}
