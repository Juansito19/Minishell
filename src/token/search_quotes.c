#include "minishell.h"

void	ft_put_word(char *s, char **word, int i, int state)
{
	int	j;

	j = -1;
	while (s[i] && !ft_is_metachar(s[i]))
	{
		if (ft_is_quote(s[i]) == T_DQUOTE && state == 0)
			state = 2;
		else if (ft_is_quote(s[i]) == T_DQUOTE && state == 2)
			state = 0;
		else if (ft_is_quote(s[i]) == T_SQUOTE && state == 0)
			state = 1;
		else if (ft_is_quote(s[i]) == T_SQUOTE && state == 1)
			state = 0;
		else if (ft_is_quote(s[i]) == T_DQUOTE && state == 1)
			(*word)[++j] = s[i];
		else if (ft_is_quote(s[i]) == T_SQUOTE && state == 2)
			(*word)[++j] = s[i];
		else if (s[i] == '$' && state == 2)
			(*word)[++j] = s[i];
		else if (s[i] == '$' && state == 1)
			(*word)[++j] = s[i];
		else if (!ft_is_quote(s[i]))
			(*word)[++j] = s[i];
		i++;
	}
}

int	ft_token_word_size(char *s, int i, int count, int state)
{
	while (s[i] && !ft_is_metachar(s[i]))
	{
		if (ft_is_quote(s[i]) == T_DQUOTE && state == 0)
			state = 2;
		else if (ft_is_quote(s[i]) == T_DQUOTE && state == 2)
			state = 0;
		else if (ft_is_quote(s[i]) == T_SQUOTE && state == 0)
			state = 1;
		else if (ft_is_quote(s[i]) == T_SQUOTE && state == 1)
			state = 0;
		else if (ft_is_quote(s[i]) == T_DQUOTE && state == 1)
			count++;
		else if (ft_is_quote(s[i]) == T_SQUOTE && state == 2)
			count++;
		else if (s[i] == '$' && state == 2)
			count++;
		else if (s[i] == '$' && state == 1)
			count++;
		else if (!ft_is_quote(s[i]))
			count++;
		i++;
	}
	return (count);
}

int	ft_token_clean_word(t_token **token)
{
	char	*word;
	int		i;

	i = ft_token_word_size((*token)->content, 0, 0, 0);
	word = malloc(i + 1 * sizeof(char));
	if (!word)
		return (1);
	word[i] = '\0';
	ft_put_word((*token)->content, &word, 0, 0);
	free((*token)->content);
	(*token)->content = word;
	return (0);
}

void	ft_search_quotes(t_token **token)
{
	t_token	*aux;
	int		i;

	aux = (*token);
	while (aux)
	{
		i = 0;
		while (aux->content[i])
		{
			if (ft_is_quote(aux->content[i]))
			{
				ft_token_clean_word(&aux);
				break ;
			}
			i++;
		}
		aux = aux->next;
	}
}

// int	ft_deltoken(t_token **token, t_token **aux, t_token **prev)
// {
// 	if ((*prev))
// 		(*prev)->next = (*aux)->next;
// 	else
// 		(*token) = (*aux)->next;
// 	free((*aux)->content);
// 	free((*aux));
// 	if ((*prev))
// 		(*aux) = (*prev)->next;
// 	else
// 		(*aux) = (*token);
// 	return (0);
// }

// void	ft_search_quotes(t_token **token)
// {
// 	t_token	*aux;
// 	t_token	*prev;
// 	int		i;

// 	aux = (*token);
// 	prev = NULL;
// 	while (aux)
// 	{
// 		i = 0;
// 		while (aux->content[i])
// 		{
// 			if (ft_is_quote(aux->content[i]))
// 			{
// 				ft_token_clean_word(&aux);
// 				if (aux->content[0] == '\0')
// 					ft_deltoken(token, &aux, &prev);
// 				break ;
// 			}
// 			i++;
// 		}
// 		if (!i)
// 			continue ;
// 		prev = aux;
// 		if (aux)
// 		aux = aux->next;
// 	}
// }
