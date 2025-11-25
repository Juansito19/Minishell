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

/* comrpobamos en las primeras etapas que las pipes que manejamos son correctas
1.- no hay pipes en el inicio ni en el final
2.- no hay pipes seguidas (error por ahora)
*/

int	pipe_check(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == '|' && s[i + 1] == '|')
			return (1);
		if (s[0] == '|')
			return (1);
		if (s[i] == '|' && s[i + 1] == '\0')
			return (1);
	}
	return (0);
}

int	redir_check_(char *s)
{
	int	i;

	i = 0;
	while ()
}
