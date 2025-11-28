#include "../minishell.h"

/* ========================== */
/* ======== builtin ========= */
/* ========================== */


/*

función ft_pwd():
    buffer = crear buffer de tamaño PATH_MAX
    si getcwd(buffer, PATH_MAX) falla:
        imprimir error
        retornar 1
    imprimir buffer
    liberar buffer
    retornar 0

*/

// ====== PWD ====== //

int	ft_pwd()
{
	char	*buffer;

	buffer = getcwd(NULL, 0);
	if (!buffer)
		return (ft_print_error(0, "pwd : error : buff too small"));
	ft_printf("%s\n", buffer);
	free(buffer);
	return (0);
}

// ====== CD ====== //

char	*ft_get_env_var(char **env, char *key)
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
				ft_print_error(12, NULL);
				return (NULL);
			}
			free(search_value);
			return (value);
		}
	}
	return (NULL);
}

int	ft_change_env_value(char **env, char *key, char *new_value, int i)
{
	char	*search_value;
	char	*value;

	search_value = ft_strjoin(key, "=");
	if (!search_value)
		return (ft_print_error(12, NULL));
	while (env[i])
	{
		if (!ft_strncmp(env[i], search_value, ft_strlen(search_value)))
		{
			free(env[i]);
			value = ft_strjoin(search_value, new_value);
			if (!value)
			{
				free(search_value);
				return (ft_print_error(12, NULL));
			}
			env[i] = value;
			free(search_value);
			return (0);
		}
		i++;
	}
	free(search_value);
	return (1);
}

/*

CD
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

int	ft_cd(char **env, char *av)
{
	char	*path;
	char	*pwd_now;

	if (!av)
	{
		path = ft_get_env_var(env, "HOME");
		if (!path)
			return (ft_print_error(0, ERR_CD_NO_HOME));
	}
	else
		path = av;
	pwd_now = getcwd(NULL, 0);
	if (chdir(path))
		return (ft_print_error(0, ERR_CD_NO_SUCH_FILE));
	if (ft_change_env_value(env, "OLDPWD", pwd_now, 0))
		return (ft_print_error(0, "cd: error change env value"));
	pwd_now = getcwd(NULL, 0);
	if (ft_change_env_value(env, "PWD", pwd_now, 0))
		return (ft_print_error(0, "cd: error change env value"));
	return (0);
}

/* 
EXPORT
Sin argumentos: muestra todas las variables de entorno ordenadas con formato declare -x VAR="value"
Con argumentos: crea o modifica variables de entorno

función ft_export_sin_args(env):
    copiar array de env
    ordenar alfabéticamente la copia
    para cada variable en copia:
        imprimir "declare -x " + variable
    liberar copia

función ft_export(argumentos, env):
    si no hay argumentos:
        ft_export_sin_args(env)
        retornar
    
    para cada argumento:
        si no es un identificador válido (debe empezar con letra o _, solo letras/números/_):
            imprimir error "not a valid identifier"
            continuar
        
        separar nombre y valor por '='
        si la variable ya existe en env:
            actualizar su valor
        sino:
            añadir nueva variable al env

*/

/* 
UNSET

función ft_unset(argumentos, env):
    para cada argumento:
        si no es un identificador válido:
            imprimir error "not a valid identifier"
            continuar
        
        buscar variable en env
        si existe:
            eliminarla del array de env
            reorganizar el array

*/