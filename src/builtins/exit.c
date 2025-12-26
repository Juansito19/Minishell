#include "minishell.h"

// ================= //
// ====== EXIT ===== //
// ================= //

static void	ft_terminator(t_data **data, char *status, int err)
{
	ft_fprintf(1, "exit\n");
	if (err)
	{
		ft_pd_error(ERR_EXIT_NUMERIC, status, err);
		ft_clean_data(data);
		clear_history();
		exit(2);
	}
	ft_clean_data(data);
	clear_history();
	exit(err);
}

int	ft_exit(t_data **data, char **status)
{
	int	i;
	int	j;
	int	exit_status;

	i = 0;
	exit_status = (*data)->exit_status;
	if (!status || !*status)
		ft_terminator(data, NULL, exit_status);
	while (status[i])
	{
		j = 0;
		while (status[i][j])
		{
			if (!ft_isdigit(status[i][j]))
				ft_terminator(data, status[i], 2);
			else if (ft_isdigit(status[i][j]))
				j++;
		}
		if (status[i + 1])
			return (ft_pd_error(ERR_EXIT_TOO_MANY, NULL, 1));
		break ;
	}
	exit(0);
}
