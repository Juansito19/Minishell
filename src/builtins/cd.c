#include "minishell.h"

// ====== CD ====== //

/*
función ft_cd(argumentos, env):
    si no hay argumentos:
        path = obtener variable HOME del env
        si HOME no existe:
            error "HOME not set"
            retornar 1
    sino:
        path = argumentos[1]
    
    guardar_pwd_actual = getcwd()
    
    si chdir(path) falla:
        imprimir error "No such file or directory"
        retornar 1
    
    actualizar variable OLDPWD = guardar_pwd_actual
    actualizar variable PWD = getcwd() nuevo
    retornar 0

chdir() - cambia de directorio
getenv() o buscar en tu array de env

cd sin argumentos → va a HOME
cd - → va al directorio anterior (OLDPWD)
cd .. → sube un nivel
*/

// int	ft_change_env_value(char ***env, char *key, char *new_value, int i)
// {
// 	char	*search_value;
// 	char	*value;

// 	search_value = ft_strjoin(key, "=");
// 	if (!search_value)
// 		return (ft_print_error(12, NULL));
// 	while ((*env)[i])
// 	{
// 		if (!ft_strncmp((*env)[i], search_value, ft_strlen(search_value)))
// 		{
// 			free((*env)[i]);
// 			value = ft_strjoin(search_value, new_value);
// 			if (!value)
// 			{
// 				free(search_value);
// 				ft_print_error(0, ERR_MALLOC);
// 			}
// 			(*env)[i] = value;
// 			free(search_value);
// 			return (0);
// 		}
// 		i++;
// 	}
// 	free(search_value);
// 	return (1);
// }

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
