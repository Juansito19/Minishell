#include "../minishel.h"

/* ========================= */
/* =========tokens========== */
/* ========================= */

t_token	*ft_token_init(void *content, t_token_type type)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(1 * sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->next = NULL;
	new_token->content = content;
	new_token->type = type;
	return (new_token);
}

void	ft_tokenadd_back(t_token **tokens, t_token *new)
{
	if (!*tokens)
		(*tokens) = new;
	else
	{
		while ((*tokens)->next)
			tokens = &(*tokens)->next;
		(*tokens)->next = new;
	}
}

int	ft_tk_size(t_token *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

void	ft_free_tokens(t_token **head)
{
	t_token	*current;
	t_token	*next;

	current = (*head);
	if (!(*head))
		return ;
	while (current)
	{
		next = current->next;
		free(current->content);
		free(current);
		current = next;
	}
}

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
		if (s[i] == ' ') //agregar mas tipos de espacios
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

/* 

text < ls -l | wc -l

*/