#include "minishell.h"

// ================= //
// ====== ENV ====== //
// ================= //

int	ft_env(char **env)
{
	if (!env || !*env)
		return (0);
	ft_double_putstr_fd(env, 1);
	ft_fprintf(1, "_=/usr/bin/env\n");
	return (0);
}
