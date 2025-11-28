#include "../minishell.h"

/* ========================== */
/* ========= error ========== */
/* ========================== */

int ft_print_error(int error_code, char *s)
{
	if (s)
		ft_fprintf(2, "%s\n", s);
	if (error_code != 0)
		perror(strerror(error_code));
	return (1);
}
