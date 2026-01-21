/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrosio <jbrosio@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 19:04:08 by jbrosio           #+#    #+#             */
/*   Updated: 2026/01/15 19:04:09 by jbrosio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ========================== //
// ====== EXPORT_UTILS ====== //
// ========================== //

void	ft_increment_shlvl(char ***env)
{
	char	*shlvl_str;
	char	*new_shlvl;
	int		shlvl;

	shlvl_str = ft_get_var_value(*env, "SHLVL");
	if (!shlvl_str)
		shlvl = 0;
	else
	{
		shlvl = ft_atoi(shlvl_str);
		free(shlvl_str);
	}
	shlvl++;
	shlvl_str = ft_itoa(shlvl);
	if (!shlvl_str)
		return ;
	new_shlvl = ft_strjoin("SHLVL=", shlvl_str);
	free(shlvl_str);
	if (!new_shlvl)
		return ;
	ft_change_or_add_var(env, new_shlvl);
	free(new_shlvl);
}

void	ft_sort_env(char **env)
{
	char	*aux;
	int		i;
	int		j;

	i = 0;
	while (env[i])
	{
		j = i + 1;
		while (env[j])
		{
			if (ft_strcmp(env[i], env[j]) > 0)
			{
				aux = env[j];
				env[j] = env[i];
				env[i] = aux;
			}
			j++;
		}
		i++;
	}
}

char	**ft_add_var(char **env, char *var)
{
	char	**res;
	int		size;
	int		i;

	i = 0;
	size = 0;
	while (env && env[size])
		size++;
	res = ft_calloc(size + 2, sizeof(char *));
	if (!res)
		return (NULL);
	while (env && env[i])
	{
		res[i] = ft_strdup(env[i]);
		if (!res[i])
			return (ft_free_all_array(res));
		i++;
	}
	res[i] = ft_strdup(var);
	if (!res[i])
		return (ft_free_all_array(res));
	if (env)
		ft_free_all_array(env);
	return (res);
}

int	ft_change_or_add_var(char ***env, char *av)
{
	char	**new_env;
	int		i;

	i = ft_get_var(*env, av);
	if (i == -2)
		return (0);
	if (i != -1)
	{
		if ((*env) && (*env)[i])
			free((*env)[i]);
		(*env)[i] = ft_strdup(av);
		if (!(*env)[i])
		{
			ft_pd_error(ERR_MALLOC, NULL, 12);
			return (1);
		}
	}
	else
	{
		new_env = ft_add_var((*env), av);
		if (!new_env)
			return (ft_pd_error(ERR_MALLOC, NULL, 12));
		(*env) = new_env;
	}
	return (0);
}
