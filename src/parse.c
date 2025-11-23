#include "../minishell.h"

/* ========================== */
/* ==========parse=========== */
/* ========================== */

int	ft_open_quote(char *input)
{
	int	s_quote;
	int	d_quote;

	s_quote = 0;
	d_quote = 0;
	while (*input)
	{
		if (*input == '\"')
			d_quote++;
		if (*input == '\'')
			s_quote++;
		input++;
	}
	if (s_quote % 2 != 0)
		return (1);
	if (d_quote % 2 != 0)
		return (1);
	return (0);
}
