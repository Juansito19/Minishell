#include "../minishell.h"

/* ========================== */
/* ==========parse=========== */
/* ========================== */

// int	ft_open_quote(char *input)
// {
// 	int	s_quote;
// 	int	d_quote;

// 	s_quote = 0;
// 	d_quote = 0;
// 	while (*input)
// 	{
// 		if (*input == '\"')
// 			d_quote++;
// 		if (*input == '\'')
// 			s_quote++;
// 		input++;
// 	}
// 	if (s_quote % 2 != 0)
// 		return (1);
// 	if (d_quote % 2 != 0)
// 		return (1);
// 	return (0);
// }

/*NO ESTA MAL PERO LE FALTAN COSAS SEGUN IA, SEGUN LA 
NUEVA GESTIONA LA MEZCLA DE COMILLAS TRATANDOLAS COMO CHAR*/

int	ft_q_p_parse(char *input)
{
	if (ft_open_quote(input))
		return (1);
	if (ft_pipe_check(input))
		return (1);
	return (0);
}

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

/* comrpobamos en las primeras etapas que las pipes que manejamos son correctas
1.- no hay pipes en el inicio ni en el final
2.- no hay pipes seguidas (error por ahora)

IMPORTANTE(ESTO NO APLICA EN CASO DE COMILLAS:
P.J: echo "| hola ||")


*/
/*ambas fallan todavia cuando encuentro dos pipes seguidos
o dos redirs seguidos
"     || "
"   <>   "

no funciona, intentar con flags

*/

int	redir_check(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[0] == '<' || s[0] == '>')
			return (1);
		else if (s[i] == '<' || s[i] == '>')
		{
			i++;
			while (s[i] < 33)
			{
				if (s[i] == '\0')
					return (1);
				if (s[i] == '<' || s[i] == '>')
					return (1);
				i++;
			}
			if (s[i] > 32 && ((s[i] != '<' || s[i] != '>')))
				return (0);
			else
				return (1);
		}
	}
	return (0);
}

static char	ft_quote_track(char c)
{
	char	quote;

	quote = 0;
	if (!quote && (c == '\'' || c == '\"'))
		quote = c;
	else
		quote = 0;
	return (quote);
}

int	ft_pipe_check(char *s)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (s[i] && s[i] <= 32)
		i++;
	if (s[i] == '|')
		return (1);
	while (s[i])
	{
		quote = ft_quote_track(s[i]);
		if (s[i] == '|' && !quote)
		{
			i++;
			while (s[i] && s[i] <= 32)
				i++;
			if (s[i] == '|' || s[i] == '\0')
				return (1);
			continue ;
		}
		i++;
	}
	return (0);
}

/*Después de > , >> , < debe haber un ﬁlename*/
// int	pipe_check_ia(char *s)
// {
// 	int		i;
// 	int		in_quote;
// 	char	quote_type;

// 	i = 0;
// 	in_quote = 0;
// 	quote_type = 0;
// 	while (s[i] && s[i] <= 32)
// 		i++;
// 	if (s[i] == '|')
// 		return (1);
// 	while (s[i])
// 	{
// 		if ((s[i] == '\'' || s[i] == '\"') && !in_quote)
// 		{
// 			in_quote = 1;
// 			quote_type = s[i];
// 		}
// 		else if (s[i] == quote_type && in_quote)
// 			in_quote = 0;

// 		if (s[i] == '|' && !in_quote)
// 		{
// 			i++;
// 			while (s[i] && s[i] <= 32)
// 				i++;
// 			if (s[i] == '|' || s[i] == '\0')
// 				return (1);
// 			continue ;
// 		}
// 		i++;
// 	}
// 	// i--;
// 	// while (i >= 0 && s[i] <= 32)
// 	// 	i--;
// 	// if (i >= 0 && s[i] == '|')
// 	// 	return (1);
// 	return (0);
// }
