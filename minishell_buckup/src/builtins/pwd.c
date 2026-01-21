/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrosio <jbrosio@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 19:09:10 by jbrosio           #+#    #+#             */
/*   Updated: 2026/01/15 19:09:11 by jbrosio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ================= //
// ====== PWD ====== //
// ================= //

int	ft_pwd(char **env)
{
	char	*buffer;

	buffer = ft_get_var_value(env, "PWD");
	if (!buffer)
	{
		buffer = getcwd(NULL, 0);
		if (!buffer)
			return (ft_pd_error(ERR_PWD, NULL, 1));
	}
	ft_printf("%s\n", buffer);
	free(buffer);
	return (0);
}
