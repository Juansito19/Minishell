#include "minishell.h"

/* ========================= */
/* ======== tokens ========= */
/* ========================= */

int	ft_token_size(char *s)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	while (s[i])
	{
		if (ft_is_quote(s[i]) == T_DQUOTE && !quote)
			quote = 2;
		else if (ft_is_quote(s[i]) == T_DQUOTE && quote == 2)
			quote = 0;
		else if (ft_is_quote(s[i]) == T_SQUOTE && !quote)
			quote = 1;
		else if (ft_is_quote(s[i]) == T_SQUOTE && quote == 1)
			quote = 0;
		if (ft_is_metachar(s[i]) && !quote)
			break ;
		if (!i && !quote && s[i] == ' ')
			return (-1);
		if (s[i] == ' ' && !quote)
			return (i);
		i++;
	}
	return (i);
}

int	ft_token_word(t_token **tokens, char *s, int *ind)
{
	t_token	*new;
	char	*word;
	int		size;

	size = ft_token_size(s);
	if (size < 0)
		return (0);
	word = ft_substr(s, 0, size);
	if (!word)
		return (-1);
	new = ft_token_init(word, T_WORD);
	if (!new)
	{
		free(word);
		return (-1);
	}
	ft_tokenadd_back(tokens, new);
	*ind += size;
	return (0);
}

int	ft_token_meta(t_token **tokens, char *s, int *ind, t_type type)
{
	t_token	*new;
	char	*word;

	if (s[0] == '<' && s[1] == '<')
		word = ft_substr(s, 0, 2);
	else if (s[0] == '>' && s[1] == '>')
		word = ft_substr(s, 0, 2);
	else
		word = ft_substr(s, 0, 1);
	if (!word)
		return (-1);
	new = ft_token_init(word, type);
	if (!new)
	{
		free(word);
		return (-1);
	}
	ft_tokenadd_back(tokens, new);
	if (type == T_HEREDOC || type == T_APPEND)
		*ind += 2;
	else
		*ind += 1;
	return (0);
}

t_token	*ft_token(char *s, int i)
{
	t_token	*token;
	int		error;

	token = NULL;
	error = 0;
	while (s[i])
	{
		if (ft_is_space(s[i]))
			i++;
		if (s[i] == '<' && s[i + 1] && s[i + 1] == '<')
			error = ft_token_meta(&token, s + i, &i, T_HEREDOC);
		else if (s[i] == '>' && s[i + 1] && s[i + 1] == '>')
			error = ft_token_meta(&token, s + i, &i, T_APPEND);
		else if (ft_is_metachar(s[i]))
			error = ft_token_meta(&token, s + i, &i, ft_is_metachar(s[i]));
		else
			error = ft_token_word(&token, s + i, &i);
		if (error < 0)
		{
			ft_free_tokens(&token);
			return (NULL);
		}
	}
	return (token);
}
