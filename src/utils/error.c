#include "minishell.h"

/* ========================== */
/* ========= error ========== */
/* ========================== */

int	ft_print_error(int error_code, char *s)
{
	if (s)
		ft_fprintf(2, "%s\n", s);
	if (error_code != 0)
		perror(strerror(error_code));
	return (1);
}

int	ft_pd_error(char *format, char *s, int error_code)
{
	if (s)
		ft_fprintf(error_code, format, s);
	else
		ft_fprintf(error_code, format);
	return (error_code);
}
