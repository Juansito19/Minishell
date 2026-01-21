/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ratatoskr_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrosio <jbrosio@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 19:09:47 by jbrosio           #+#    #+#             */
/*   Updated: 2026/01/15 19:09:48 by jbrosio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ================================ */
/* ======= ratatoskr_utils ======== */
/* ================================ */

void	*ft_free_pointers(char *number, char *tmp)
{
	if (tmp)
		free(tmp);
	if (number)
		free(number);
	return (NULL);
}

char	*ft_make_unic_name(void)
{
	static int	n;
	char		*name;
	char		*number;
	char		*tmp;

	name = NULL;
	tmp = ft_strdup(".heredoc_");
	number = ft_itoa(n);
	n++;
	if (!tmp || !number)
	{
		ft_pd_error(ERR_MALLOC, NULL, 12);
		return (ft_free_pointers(number, tmp));
	}
	name = ft_strjoin(tmp, number);
	if (!name)
	{
		ft_pd_error(ERR_MALLOC, NULL, 12);
		return (ft_free_pointers(number, tmp));
	}
	ft_free_pointers(number, tmp);
	return (name);
}

int	ft_files_destroyer(t_tree **yggdrasil)
{
	if (!(*yggdrasil))
		return (0);
	if ((*yggdrasil)->left)
		ft_files_destroyer(&(*yggdrasil)->left);
	if ((*yggdrasil)->right)
		ft_files_destroyer(&(*yggdrasil)->right);
	if ((*yggdrasil)->type == T_FD)
		if (unlink((*yggdrasil)->content[0]) == -1)
			return (1);
	return (0);
}

int	ft_signal_break(char **tmp_name, int fd, int fd_back)
{
	int	*times;

	times = ft_get_times_ptr(0);
	if (g_status == 130)
	{
		if (*times == 0)
			ft_fprintf(1, "\n");
		*times += 1;
		close(fd);
		ft_hugin_signal();
		dup2(fd_back, STDIN_FILENO);
		close(fd_back);
		free(*tmp_name);
		return (130);
	}
	ft_pd_error(ERR_HEREDOC_CTRLD, *tmp_name, 1);
	free(*tmp_name);
	close(fd);
	dup2(fd_back, STDIN_FILENO);
	close(fd_back);
	return (0);
}
