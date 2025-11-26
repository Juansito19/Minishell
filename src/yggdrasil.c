#include "../minishell.h"

/* ========================== */
/* ===========tree=========== */
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

// ESTO SE COMENTO POR LAS DUDAS DE QUE VUELVA A USARSE
// int	ft_branch_pipe(t_token *pipe, t_tree **tree, t_token **tokens)
// {
// 	t_token	*left;
// 	t_token	*right;
// 	char	**word;

// 	word = ft_fill_word_type(pipe, 1);
// 	if (!word)
// 	{
// 		ft_free_all(tree, tokens, word);
// 		return (1);
// 	}
// 	(*tree) = ft_tree_init(word, T_PIPE);
// 	if (!(*tree))
// 	{
// 		ft_free_all(tree, tokens, word);
// 		return (1);
// 	}
// 	left = ft_put_all_left(tokens, pipe);
// 	right = ft_put_all_right(&pipe->next);
// 	ft_yggdrasil(&left, &(*tree)->left);
// 	ft_yggdrasil(&right, &(*tree)->right);
// 	ft_free_tokens(&left);
// 	ft_free_tokens(&right);
// 	return (0);
// }

// ESTO SE COMENTO POR LAS DUDAS DE QUE VUELVA A USARSE
// int	ft_branch_red(t_token *red, t_tree **tree, t_token **tokens)
// {
// 	t_token	*left;
// 	t_token	*right;
// 	char	**word;

// 	word = ft_fill_word_type(red, 1);
// 	if (!word)
// 	{
// 		ft_free_all(tree, tokens, word);
// 		return (1);
// 	}
// 	(*tree) = ft_tree_init(word, ft_is_red(red->content));
// 	if (!(*tree))
// 	{
// 		ft_free_all(tree, tokens, word);
// 		return (1);
// 	}
// 	left = ft_put_all_left(tokens, red);
// 	right = ft_put_all_right(&red->next);
// 	ft_yggdrasil(&left, &(*tree)->left);
// 	ft_yggdrasil(&right, &(*tree)->right);
// 	ft_free_tokens(&left);
// 	ft_free_tokens(&right);
// 	return (0);
// }

int	ft_branch_meta(t_token *meta, t_tree **tree, t_token **tokens)
{
	t_token	*left;
	t_token	*right;
	char	**word;

	word = ft_fill_word_type(meta, 1);
	if (!word)
	{
		ft_free_all(tree, tokens, NULL, word);
		return (1);
	}
	(*tree) = ft_tree_init(word, ft_take_meta(meta->content));
	if (!(*tree))
	{
		ft_free_all(tree, tokens, NULL, word);
		return (1);
	}
	left = ft_put_all_left(tokens, meta);
	right = ft_put_all_right(&meta->next);
	ft_yggdrasil(&left, &(*tree)->left);
	ft_yggdrasil(&right, &(*tree)->right);
	ft_free_tokens(&left);
	ft_free_tokens(&right);
	return (0);
}

int	ft_branch_word(t_tree **tree, t_token **tokens)
{
	char	**word;

	word = ft_fill_word_type((*tokens), ft_tk_size((*tokens)));
	if (!word)
	{
		ft_free_all(tree, tokens, NULL, word);
		return (1);
	}
	(*tree) = ft_tree_init(word, ft_is_builtin((*tokens)));
	if (!(*tree))
	{
		ft_free_all(tree, tokens, NULL, word);
		return (1);
	}
	return (0);
}

void	ft_yggdrasil(t_token **tokens, t_tree **tree)
{
	t_token	*token_pipe;
	t_token	*token_red;

	token_pipe = ft_search_pipe(tokens);
	if (token_pipe)
	{
		if (ft_branch_meta(token_pipe, tree, tokens))
			return ;
		return ;
	}
	else
	{
		token_red = ft_search_red(tokens);
		if (token_red)
		{
			if (ft_branch_meta(token_red, tree, tokens))
				return ;
			return ;
		}
		else
		{
			if (ft_branch_word(tree, tokens))
				return ;
		}
	}
}

// FUNCION ANTIGUA DEL ARBOL
// void	ft_yggdrasil(t_token **tokens, t_tree **tree)
// {
// 	t_token	*token_pipe;
// 	t_token	*token_red;

// 	token_pipe = ft_search_pipe(tokens);
// 	if (token_pipe)
// 	{
// 		if (ft_branch_pipe(token_pipe, tree, tokens))
// 			return ;
// 		// word = ft_fill_word_type(token_pipe, 1);
// 		// if (!word)
// 		// 	return (ft_free_all(tree, tokens, word));
// 		// (*tree) = ft_tree_init(word, T_PIPE);
// 		// if (!(*tree))
// 		// 	return (ft_free_all(tree, tokens, word));
// 		// left = ft_put_all_left(tokens, token_pipe);
// 		// right = ft_put_all_right(&token_pipe->next);
// 		// ft_yggdrasil(&left, &(*tree)->left);
// 		// ft_yggdrasil(&right, &(*tree)->right);
// 		// ft_free_tokens(&left);
// 		// ft_free_tokens(&right);
// 		return ;
// 	}
// 	else
// 	{
// 		token_red = ft_search_red(tokens);
// 		if (token_red)
// 		{
// 			if (ft_branch_red(token_red, tree, tokens))
// 				return ;
// 			// word = ft_fill_word_type(token_red, 1);
// 			// if (!word)
// 			// 	return (ft_free_all(tree, tokens, word));
// 			// (*tree) = ft_tree_init(word, ft_is_red(token_red->content));
// 			// if (!(*tree))
// 			// 	return (ft_free_all(tree, tokens, word));
// 			// left = ft_put_all_left(tokens, token_red);
// 			// right = ft_put_all_right(&token_red->next);
// 			// ft_yggdrasil(&left, &(*tree)->left);
// 			// ft_yggdrasil(&right, &(*tree)->right);
// 			// ft_free_tokens(&left);
// 			// ft_free_tokens(&right);
// 			return ;
// 		}
// 		else
// 		{
// 			if (ft_branch_word(tree, tokens))
// 				return ;
// 			// word = ft_fill_word_type((*tokens), ft_tk_size((*tokens)));
// 			// if (!word)
// 			// 	return (ft_free_all(tree, tokens, word));
// 			// (*tree) = ft_tree_init(word, ft_is_builtin((*tokens)));
// 			// if (!(*tree))
// 			// 	return (ft_free_all(tree, tokens, word));
// 		}
// 	}
// 	return ;
// }