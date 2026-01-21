/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrosio <jbrosio@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 19:08:50 by jbrosio           #+#    #+#             */
/*   Updated: 2026/01/15 19:08:51 by jbrosio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ================= //
// ====== ENV ====== //
// ================= //

int	ft_env(char **env, char **av)
{
	int	i;

	i = 0;
	if (!env || !*env)
		return (0);
	if (ft_count_words(av) > 1)
		return (ft_pd_error(NO_FILE_DIR, av[1], 1));
	while (env[i])
	{
		if (ft_strchr(env[i], '='))
		{
			ft_putstr_fd(env[i], 1);
			ft_fprintf(1, "\n");
		}
		i++;
	}
	ft_fprintf(1, "_=/usr/bin/env\n");
	return (0);
}
