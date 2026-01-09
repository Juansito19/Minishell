#include "minishell.h"

// ================= //
// ====== ENV ====== //
// ================= //

int	ft_env(char **env)
{
	int	i;

	i = 0;
	if (!env || !*env)
		return (0);
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
