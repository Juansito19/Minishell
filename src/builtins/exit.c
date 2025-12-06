#include "minishell.h"

static void	ft_terminator(t_data **data, char ***env, char **input)
{
	ft_clean_data(data);
	ft_free_all(NULL, NULL, input, env);
	clear_history();
}

int	ft_exit(t_data **data, char ***env, char **input, char **status)
{
	int	i;
	int	j;
	int	exit_status;

	i = 0;
	exit_status = (*data)->exit_status;
	ft_terminator(data, env, input);
	if (!status)
		exit(exit_status);
	while (status[i])
	{
		j = 0;
		while (status[i][j])
		{
			if (!ft_isdigit(status[i][j]))
				exit(ft_pd_error(ERR_EXIT_NUMERIC, status[i], 2));
			else if (ft_isdigit(status[i][j]))
				j++;
		}
		if (status[i + 1])
			exit(ft_pd_error(ERR_EXIT_TOO_MANY, NULL, 1));
		break ;
	}
	exit(ft_atoi(status[i]));
}
