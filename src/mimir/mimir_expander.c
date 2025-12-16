#include "minishell.h"

/* =============================== */
/* ======== mimir expander ======= */
/* =============================== */

void	ft_find_dollar(t_expand **exp)
{
	int	i;
	int	dollar;

	i = 0;
	dollar = 0;
	while ((*exp)->var[i])
	{
		if ((*exp)->var[i] == '$' && !dollar)
			dollar = 1;
		else if ((*exp)->var[i] == '$' && dollar)
		{
			(*exp)->dollar = 1;
			break ;
		}
		i++;
	}
}

void	ft_find_limit(t_expand **exp)
{
	int	i;

	i = 0;
	while ((*exp)->var[i])
	{
		if ((*exp)->var[i] == '/')
		{
			(*exp)->limit = 1;
			break ;
		}
		i++;
	}
}
