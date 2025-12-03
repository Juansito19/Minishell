#include "minishell.h"

/* ========================== */
/* ======= yggdrasil ======== */
/* ========================== */

t_token	*ft_put_all_left(t_token **tokens, t_token *token_pipe)
{
	t_token	*left_tokens;
	t_token	*tmp;
	t_token	*new;
	char	*cpy;

	tmp = (*tokens);
	left_tokens = NULL;
	while (tmp && tmp != token_pipe)
	{
		cpy = ft_strdup(tmp->content);
		if (!cpy)
		{
			ft_free_tokens(&tmp);
			return (NULL);
		}
		new = ft_token_init(cpy, tmp->type);
		if (!new)
		{
			free(cpy);
			return (NULL);
		}
		ft_tokenadd_back(&left_tokens, new);
		tmp = tmp->next;
	}
	return (left_tokens);
}

t_token	*ft_put_all_right(t_token **tokens)
{
	t_token	*right_tokens;
	t_token	*tmp;
	t_token	*new;
	char	*cpy;

	tmp = (*tokens);
	right_tokens = NULL;
	while (tmp)
	{
		cpy = ft_strdup(tmp->content);
		if (!cpy)
		{
			ft_free_tokens(&right_tokens);
			return (NULL);
		}
		new = ft_token_init(cpy, tmp->type);
		if (!new)
		{
			ft_free_tokens(&right_tokens);
			return (free(cpy), NULL);
		}
		ft_tokenadd_back(&right_tokens, new);
		tmp = tmp->next;
	}
	return (right_tokens);
}

char	**ft_fill_word_type(t_token *token, int size)
{
	char	**content;
	t_token	*aux;
	int		i;

	content = ft_calloc(size + 1, sizeof(char *));
	if (!content)
		return (NULL);
	i = 0;
	aux = token;
	while (i < size)
	{
		content[i] = ft_strdup(aux->content);
		if (!content[i])
		{
			ft_free_all_array(content);
			free(content);
			return (NULL);
		}
		aux = aux->next;
		i++;
	}
	return (content);
}

void	ft_yggdrasil(t_token **tokens, t_tree **tree, t_data **data)
{
	t_token	*token_pipe;
	t_token	*token_red;

	token_pipe = ft_search_pipe(tokens);
	if (token_pipe)
	{
		if (ft_branch_m(token_pipe, tree, tokens, data))
			return ;
		return ;
	}
	else
	{
		token_red = ft_search_red(tokens);
		if (token_red)
		{
			if (ft_branch_m(token_red, tree, tokens, data))
				return ;
			return ;
		}
		else
		{
			if (ft_branch_w(tree, tokens, (*data)->path))
				return ;
		}
	}
}
