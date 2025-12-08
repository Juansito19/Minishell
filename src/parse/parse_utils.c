#include "minishell.h"

/* ============================ */
/* ======= parse_utils ======== */
/* ============================ */

/*MODIFICAR FUNCIONES PARSEO COMILLAS, USAR BANDERAS INT*/
/*MODIFICAR FUNCIONES PARSEO COMILLAS, USAR BANDERAS INT*/
/*MODIFICAR FUNCIONES PARSEO COMILLAS, USAR BANDERAS INT*/

// void	ft_real_quote(t_token **token)
// {
// 	t_token	*aux;
// 	int		f_quote;

// 	f_quote = 0;
// 	if (!(*token) || !token)
// 		return ;
// 	aux = (*token);
// 	while ((*token))
// 	{
// 		if (!f_quote && ft_is_quote((*token)->content[0]) == 6)
// 			f_quote = 1;
// 		else if (!f_quote && ft_is_quote((*token)->content[0]) == 7)
// 			f_quote = 2;
// 		else if (f_quote == 1 && ft_is_quote((*token)->content[0]) == 6)
// 			f_quote = 0;
// 		else if (f_quote == 2 && ft_is_quote((*token)->content[0]) == 7)
// 			f_quote = 0;
// 		else if (f_quote == 2 && ft_is_quote((*token)->content[0]) == 6)
// 			(*token)->type = T_CMD;
// 		else if (f_quote == 1 && ft_is_quote((*token)->content[0]) == 7)
// 			(*token)->type = T_CMD;
// 		else
// 			(*token)->type = T_CMD;
// 		(*token) = (*token)->next;
// 	}
// 	(*token) = aux;
// }

char	ft_quote_track(char c)
{
	char	quote;

	quote = 0;
	if (!quote && (c == '\'' || c == '\"'))
		quote = c;
	else
		quote = 0;
	return (quote);
}

int	ft_redir_bucle_check(char *s, char quote)
{
	int		i;

	i = 0;
	while (s[i])
	{
		quote = ft_quote_track(s[i]);
		if ((s[i] == '>' || s[i] == '<') && !quote)
		{
			if (s[i] == '>' && s[i + 1] == '>')
				i += 2;
			else if (s[i] == '<' && s[i + 1] == '<')
				i += 2;
			else
				i++;
			while (s[i] && s[i] <= 32)
				i++;
			if (s[i] == '>' || s[i] == '<' || s[i] == '|' || s[i] == '\0')
				return (1);
			continue ;
		}
		i++;
	}
	return (0);
}
