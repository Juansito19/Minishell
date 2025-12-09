#include "minishell.h"

/* ========================== */
/* ========= utils ========== */
/* ========================== */

void	ft_random_banner(void)
{
	pid_t	pid;
	int		banner_choice;

	pid = getpid();
	banner_choice = (pid % 4) + 1;
	if (banner_choice == 1)
		ft_banner_1();
	else if (banner_choice == 2)
		ft_banner_2();
	else if (banner_choice == 3)
		ft_banner_3();
	else
		ft_banner_4a();
}

int	ft_find_path(t_data **data, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			(*data)->path = ft_strdup(envp[i]);
			if (!(*data)->path)
				return (ft_print_error(12, NULL));
			break ;
		}
		i++;
	}
	if (!(*data)->path)
	{
		// ft_print_error(0, "Error: PATH variable not found in environment\n");
		return (1);
	}
	return (0);
}
