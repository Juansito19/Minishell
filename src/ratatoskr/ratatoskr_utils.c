#include "minishell.h"

/* ================================ */
/* ======= ratatoskr_utils ======== */
/* ================================ */

void	*ft_free_pointers(char *number, char *tmp)
{
	if (tmp)
		free(tmp);
	if (number)
		free(number);
	return (NULL);
}

char	*ft_make_unic_name(void)
{
	static int	n;
	char		*name;
	char		*number;
	char		*tmp;

	name = NULL;
	tmp = ft_strdup(".heredoc_");
	number = ft_itoa(n);
	n++;
	if (!tmp || !number)
	{
		ft_pd_error(ERR_MALLOC, NULL, 12);
		return (ft_free_pointers(number, tmp));
	}
	name = ft_strjoin(tmp, number);
	if (!name)
	{
		ft_pd_error(ERR_MALLOC, NULL, 12);
		return (ft_free_pointers(number, tmp));
	}
	ft_free_pointers(number, tmp);
	return (name);
}
