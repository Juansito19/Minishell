#include "minishell.h"

/* ========================== */
/* ========= signals ======== */
/* ========================== */

void	ft_hugin_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_fprintf(1, "\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_status = 130;
	}
}

int	ft_hugin_signal(void)
{
	struct sigaction	sa;
	struct sigaction	sa_ign;

	sa.sa_handler = &ft_hugin_handler;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGINT, &sa, NULL) == -1)
		return (ft_pd_error(ERR_SIGNAL, "SIGINT", 1));
	sa_ign.sa_handler = SIG_IGN;
	sa_ign.sa_flags = SA_RESTART;
	sigemptyset(&sa_ign.sa_mask);
	if (sigaction(SIGQUIT, &sa_ign, NULL) == -1)
		return (ft_pd_error(ERR_SIGNAL, "SIGQUIT", 1));
	return (0);
}

static void	ft_munin_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_status = 130;
		rl_on_new_line();
		rl_replace_line("", 0);
		close(STDIN_FILENO);
	}
}

int	ft_munin_signal(void)
{
	struct sigaction	sa;
	struct sigaction	sa_ign;

	sa.sa_handler = &ft_munin_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGINT, &sa, NULL) == -1)
		return (ft_pd_error(ERR_SIGNAL, "SIGINT", 1));
	sa_ign.sa_handler = SIG_IGN;
	sa_ign.sa_flags = SA_RESTART;
	if (sigaction(SIGQUIT, &sa_ign, NULL) == -1)
		return (ft_pd_error(ERR_SIGNAL, "SIGQUIT", 1));
	return (0);
}
