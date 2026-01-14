#include "minishell.h"

// Estas señales son solo para el proceso padre (ignora)
int	ft_odin_signal(void)
{
	struct sigaction	sa;
	struct sigaction	sa_ign;

	sa.sa_handler = SIG_IGN;
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

// static void	ft_son_handler(int sig)
// {
// 	if (sig == SIGINT)
// 		ft_fprintf(1, "\n");
// }

// Estas señales son solo para los procesos hijos en el ejecutor
int	ft_odinson_signal(void)
{
	struct sigaction	sa;

	// sa.sa_handler = &ft_son_handler;
	sa.sa_handler = SIG_DFL;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGINT, &sa, NULL) == -1)
		return (ft_pd_error(ERR_SIGNAL, "SIGINT", 1));
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		return (ft_pd_error(ERR_SIGNAL, "SIGQUIT", 1));
	return (0);
}
