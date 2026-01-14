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

int	ft_find_path(t_tree **tree, char **envp)
{
	int	i;

	i = 0;
	if (!envp || !*envp)
		return (1);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			(*tree)->path = ft_strdup(envp[i] + 5);
			if (!(*tree)->path)
				return (ft_pd_error(ERR_MALLOC, NULL, 12));
			break ;
		}
		i++;
	}
	if (!(*tree)->path)
		return (1);
	return (0);
}

int	*ft_get_times_ptr(int reset)
{
	static int	times;

	if (reset)
		times = 0;
	return (&times);
}

void	ft_reset_heredoc_times(void)
{
	ft_get_times_ptr(1);
}
