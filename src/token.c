#include "../minishell.h"

/* ========================= */
/* =========tokens========== */
/* ========================= */

int	ft_token_word(t_token **tokens, char *s, int *ind)
{
	t_token	*new;
	char	*word;
	int		i;

	i = 0;
	while (s[i] && !ft_is_metachar(s[i]) && s[i] != ' ')
		i++;
	word = ft_substr(s, 0, i);
	if (!word)
		return (-1);
	new = ft_token_init(word, T_WORD);
	if (!new)
	{
		free(word);
		return (-1);
	}
	ft_tokenadd_back(tokens, new);
	*ind += i;
	return (0);
}

int	ft_token_meta(t_token **tokens, char *s, int *ind, t_token_type type)
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
		else if (s[i] == '<' && s[i+1] && s[i+1] == '<')
			error = ft_token_meta(&token, s+i, &i, T_HEREDOC);
		else if (s[i] == '>' && s[i+1] && s[i+1] == '>')
			error = ft_token_meta(&token, s+i, &i, T_APPEND);
		else if (ft_is_metachar(s[i]))
			error = ft_token_meta(&token, s+i, &i, ft_is_metachar(s[i]));
		else
			error = ft_token_word(&token, s+i, &i);
		if (error < 0)
		{
			ft_free_tokens(&token);
			return (NULL);
		}
	}
	return (token);
}
