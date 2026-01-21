/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heimdall.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrosio <jbrosio@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 19:09:27 by jbrosio           #+#    #+#             */
/*   Updated: 2026/01/15 19:09:28 by jbrosio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ========================== */
/* ======== heimdall========= */
/* ========================== */

int	ft_search_path(t_tree **ygg, char **tmp_dir, char **path_dir)
{
	char	*aux;

	aux = NULL;
	if (*tmp_dir)
		free(*tmp_dir);
	aux = ft_strjoin(*path_dir, "/");
	(*tmp_dir) = ft_strjoin(aux, (*ygg)->content[0]);
	if (aux)
		free(aux);
	aux = NULL;
	if (!(*tmp_dir))
	{
		ft_pd_error(ERR_MALLOC, NULL, 12);
		return (-1);
	}
	if (access(*tmp_dir, X_OK) == 0)
		return (0);
	return (1);
}

int	ft_assign_path(t_tree **ygg, char **tmp_dir, char ***path_dir, int *i)
{
	int	pos;

	pos = *i;
	if ((*path_dir)[pos] == NULL)
	{
		ft_free_all(NULL, NULL, tmp_dir, path_dir);
		*i = 127;
		return (ft_pd_error(ERR_CMD_NOT_FOUND, (*ygg)->content[0], 127));
	}
	free((*ygg)->content[0]);
	(*ygg)->content[0] = ft_strdup(*tmp_dir);
	if (!(*ygg)->content[0])
	{
		*i = 12;
		ft_free_all(NULL, NULL, tmp_dir, path_dir);
		return (ft_pd_error(ERR_MALLOC, NULL, 12));
	}
	return (0);
}

int	ft_bifrost(t_tree **ygg, char *tmp_dir)
{
	char	**path_dir;
	int		i;

	if ((ft_strlen((*ygg)->content[0]) == 1 && (*ygg)->content[0][0] == '.'))
		return (ft_pd_error(ERR_CMD_NOT_FOUND, (*ygg)->content[0], 12));
	if ((*ygg)->content[0][0] == '\0')
		return (ft_pd_error(ERR_CMD_NOT_FOUND, (*ygg)->content[0], 12));
	if (access((*ygg)->content[0], X_OK) == 0)
		return (0);
	path_dir = ft_split((*ygg)->path, ':');
	if (!path_dir)
		return (ft_pd_error(NO_FILE_DIR, (*ygg)->content[0], 1));
	i = 0;
	while (path_dir[i])
	{
		if (ft_search_path(ygg, &tmp_dir, &path_dir[i]) == -1)
			return (ft_free_all(NULL, NULL, NULL, &path_dir), 12);
		else if (!ft_search_path(ygg, &tmp_dir, &path_dir[i]))
			break ;
		i++;
	}
	if (ft_assign_path(ygg, &tmp_dir, &path_dir, &i))
		return (i);
	ft_free_all(NULL, NULL, &tmp_dir, &path_dir);
	return (0);
}

int	ft_heimdall(t_data **data, t_tree **ygg, char **env, int forked)
{
	if (!ygg || !(*ygg))
		return (0);
	if ((*ygg)->type == T_PIPE)
		return (ft_heimdall_pipe(data, ygg, env, forked));
	if (ft_is_red((*ygg)->type))
		return (ft_heimdall_redir(data, ygg, env, forked));
	if ((*ygg)->type == T_CMD || (*ygg)->type == T_BUILTIN)
		return (ft_heimdall_cmd(data, ygg, env, forked));
	return (0);
}
