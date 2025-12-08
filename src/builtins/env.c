#include "minishell.h"

// ====== ENV ====== //

int	ft_env(char **env)
{
	if (!env || !*env)
		return (0);
	ft_double_putstr_fd(env, 1);
	return (0);
}
