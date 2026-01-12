#include "minishell.h"

/* ========================== */
/* ========= error ========== */
/* ========================== */

int	ft_print_cd_error(char *path)
{
	struct stat	st;

	if (access(path, F_OK) == -1)
		ft_pd_error(ERR_NO_SUCH_FILE, "cd", 1);
	else if (stat(path, &st) == -1)
		ft_pd_error(ERR_CD_STAT, NULL, 1);
	else if (!S_ISDIR(st.st_mode))
		ft_pd_error(ERR_CD_NO_DIR, path, 1);
	else if (access(path, X_OK) == -1)
		ft_pd_error(PER_DENIED, path, 1);
	free(path);
	return (1);
}

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
		ft_fprintf(2, format, s);
	else
		ft_fprintf(2, format);
	return (error_code);
}
