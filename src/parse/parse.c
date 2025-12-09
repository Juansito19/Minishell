#include "minishell.h"

/* ========================== */
/* ========= parse ========== */
/* ========================== */

/* ========== funcion principial =========== */

int	ft_big_prick_parse(char *input)
{
	if (ft_open_quote(input))
		return (1);
	if (ft_pipe_check(input))
		return (1);
	if (ft_redir_check(input))
		return (1);
	return (0);
}

/* ========== parseo comillas =========== */

int	ft_open_quote(char *input)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (input[i])
	{
		if (!quote)
		{
			if (input[i] == '\"' || input[i] == '\'')
				quote = input[i];
		}
		else
			if (input[i] == quote)
				quote = 0;
		i++;
	}
	if (quote)
		return (1);
	return (0);
}

/* ========== parseo redirecciones =========== */

int	ft_redir_check(char *s)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (s[i] && ft_is_space(s[i]))
		i++;
	if (s[i] == '<')
		return (1);
	if (ft_redir_bucle_check(s, quote))
		return (1);
	return (0);
}

/* ========== parseo pipes =========== */

int	ft_pipe_check(char *s)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (s[i] && ft_is_space(s[i]))
		i++;
	if (s[i] == '|')
		return (1);
	while (s[i])
	{
		quote = ft_quote_track(s[i], quote);
		if (s[i] == '|' && !quote)
		{
			i++;
			while (s[i] && ft_is_space(s[i]))
				i++;
			if (s[i] == '|' || s[i] == '\0')
				return (1);
			continue ;
		}
		i++;
	}
	return (0);
}
