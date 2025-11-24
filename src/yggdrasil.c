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

char	**ft_fill_word_type(t_token *token, int	size)
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

// void	ft_treesclean(t_tree **trees)
// {
// 	t_tree	*aux;

// 	if (!trees)
// 		return ;
// 	while (*trees)
// 	{
// 		aux = (*trees)->next;
// 		free((*trees)->av);
// 		free((*trees));
// 		*trees = aux;
// 	}
// 	*trees = NULL;
// }

void	ft_yggdrasil(t_token **tokens, t_tree **tree)
{
	t_token	*token_pipe;
	t_token	*token_red;
	t_token	*left;
	t_token	*right;

	token_pipe = ft_search_pipe(tokens);
	if (token_pipe)
	{
		(*tree) = ft_tree_init(ft_fill_word_type(token_pipe, 1), T_PIPE);
		if (!tree)
			return ;
		left = ft_put_all_left(tokens, token_pipe);
		right = ft_put_all_right(&token_pipe->next);
		ft_yggdrasil(&left, &(*tree)->left);
		ft_yggdrasil(&right, &(*tree)->right);
		ft_free_tokens(&left);
		ft_free_tokens(&right);
		return ;
	}
	else
	{
		token_red = ft_search_red(tokens);
		if (token_red)
		{
			(*tree) = ft_tree_init(ft_fill_word_type(token_red, 1), ft_is_red(token_red->content));
			if (!tree)
				return ;
			left = ft_put_all_left(tokens, token_red);
			right = ft_put_all_right(&token_red->next);
			ft_yggdrasil(&left, &(*tree)->left);
			ft_yggdrasil(&right, &(*tree)->right);
			ft_free_tokens(&left);
			ft_free_tokens(&right);
			return ;
		}
		else
			(*tree) = ft_tree_init(ft_fill_word_type((*tokens), ft_tk_size((*tokens))), ft_is_builtin((*tokens)));
	}
	return ;
}

// void	ft_tree(t_token **tokens, t_tree **tree)
// {
// 	t_token	*token_pipe;
// 	t_token	*token_red;
// 	t_token	*left;
// 	t_token	*right;

// 	// if (!(*tree)->left && !(*tree)->right)
// 	// 	return ;
// 	// if (!(*tree))
// 	// 	return ;
// 	// else
// 	// {
// 	token_pipe = ft_search_pipe(tokens);
// 	if (token_pipe)
// 	{
// 		(*tree) = ft_tree_init(ft_fill_word_type(token_pipe, 1), T_PIPE);
// 		if (!tree)
// 			return ;
// 		left = ft_put_all_left(tokens, token_pipe);
// 		right = ft_put_all_right(&token_pipe->next);
// 		ft_tree(&left, &(*tree)->left);
// 		ft_tree(&right, &(*tree)->right);
// 		// ft_tree(ft_put_all_left(tokens, token_pipe), &(*tree)->left);
// 		// ft_tree(ft_put_all_right(&token_pipe->next), &(*tree)->right);
// 	}
// 	else
// 	{
// 		token_red = ft_search_red(tokens);
// 		if (token_red)
// 		{
// 			(*tree) = ft_tree_init(ft_fill_word_type(token_red, 1), ft_is_red(token_red->content));
// 			if (!tree)
// 				return ;
// 			left = ft_put_all_left(tokens, token_red);
// 			right = ft_put_all_right(&token_red->next);
// 			ft_tree(&left, &(*tree)->left);
// 			ft_tree(&right, &(*tree)->right);
// 			// ft_tree((t_token **)ft_put_all_left(tokens, token_red), &(*tree)->left);
// 			// ft_tree((t_token **)ft_put_all_right(&token_red->next), &(*tree)->right);
// 		}
// 		else
// 		{
// 			(*tree) = ft_tree_init(ft_fill_word_type((*tokens), ft_tk_size((*tokens))), ft_is_builtin((*tokens)));
// 		}
// 	}
// 	return ;
// }