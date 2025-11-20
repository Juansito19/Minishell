#include "../minishel.h"

/* ========================== */
/* ===========tree=========== */
/* ========================== */

t_tree	*ft_tree_init(char **content, t_token_type type)
{
	t_tree	*new_tree;

	new_tree = (t_tree *)malloc(1 * sizeof(t_tree));
	if (!new_tree)
		return (NULL);
	new_tree->right = NULL;
	new_tree->left = NULL;
	new_tree->infile = -1;
	new_tree->outfile = -1;
	new_tree->pipe[0] = -1;
	new_tree->pipe[1] = -1;
	new_tree->path = NULL;
	new_tree->type = type;
	new_tree->content = content;
	return (new_tree);
}

void	ft_treeadd_right(t_tree **tree, t_tree *new)
{
	if (!*tree)
		(*tree) = new;
	else
	{
		while ((*tree)->right)
			tree = &(*tree)->right;
		(*tree)->right = new;
	}
}

void	ft_treeadd_left(t_tree **tree, t_tree *new)
{
	if (!*tree)
		(*tree) = new;
	else
	{
		while ((*tree)->left)
			tree = &(*tree)->left;
		(*tree)->left = new;
	}
}

t_token	*ft_search_pipe(t_token **tokens)
{
	t_token	*tmp;

	tmp = (*tokens);
	if (!tokens || !(*tokens))
		return (NULL);
	while (tmp)
	{
		if (tmp->type == T_PIPE)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

t_token_type ft_is_red(char *content)
{
	if (!ft_strncmp(content, "<<", 3))
        return (T_HEREDOC);
    else if (!ft_strncmp(content, ">>", 3))
        return (T_APPEND);
    else if (!ft_strncmp(content, "<", 3))
        return (T_REDIR_IN);
    else if (!ft_strncmp(content, ">", 3))
        return (T_REDIR_OUT);
    return (0);
}

t_token	*ft_search_red(t_token **tokens)
{
	t_token	*tmp;

	tmp = (*tokens);
	if (!tokens || !(*tokens))
		return (NULL);
	while (tmp)
	{
		if (tmp->type == ft_is_red(tmp->content))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

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
	printf("size = %d\n", size);
	while (i < size)
	{
		content[i] = ft_strdup(aux->content);
		if (!content[i])
		{
			ft_free_all_array(content);
			free(content);
			return (NULL);
		}
		printf("content[%d] = %s\n", i, content[i]);
		aux = aux->next;
		i++;
	}
	return (content);
}

t_token_type	ft_is_builtin(t_token *token)
{
	if (!ft_strncmp(token->content, "echo", 5))
		return (T_BUILTIN);
	else if (!ft_strncmp(token->content, "cd", 3))
		return (T_BUILTIN);
	else if (!ft_strncmp(token->content, "pwd", 4))
		return (T_BUILTIN);
	else if (!ft_strncmp(token->content, "export", 7))
		return (T_BUILTIN);
	else if (!ft_strncmp(token->content, "unset", 6))
		return (T_BUILTIN);
	else if (!ft_strncmp(token->content, "exit", 5))
		return (T_BUILTIN);
	else if (!ft_strncmp(token->content, "env", 4))
		return (T_BUILTIN);
	return (T_CMD);
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
// 
// t_tree	*ft_tree(t_token **tokens, t_tree *tree)
// {
	// t_token	*token_pipe;
	// t_token	*token_left;
	// t_token	*token_right;
// 
	// token_pipe = ft_search_pipe(tokens);
	// if (token_pipe)
	// {
		// tree = ft_tree_init(&token_pipe->content, T_PIPE);
		// if (!tree)
			// return (NULL);
		// token_left = ft_put_all_left()
	// }
	// else
		// return (funcion_para_comando_simple());
// }

void	ft_tree(t_token **tokens, t_tree **tree)
{
	t_token	*token_pipe;
	t_token	*token_red;

	// if (!(*tree)->left && !(*tree)->right)
	// 	return ;
	// if (!(*tree))
	// 	return ;
	// else
	// {
	token_pipe = ft_search_pipe(tokens);
	if (token_pipe)
	{
		(*tree) = ft_tree_init(&token_pipe->content, T_PIPE);
		if (!tree)
			return ;
		ft_tree(ft_put_all_left(tokens, token_pipe), &(*tree)->left);
		ft_tree(ft_put_all_right(&token_pipe->next), &(*tree)->right);
	}
	else
	{
		token_red = ft_search_red(tokens);
		if (token_red)
		{
			(*tree) = ft_tree_init(&token_red->content, ft_red_type(token_red->content));
			if (!tree)
				return ;
			ft_tree(ft_put_all_left(tokens, token_red), &(*tree)->left);
			ft_tree(ft_put_all_right(&token_red->next), &(*tree)->right);
		}
		else
		{
			(*tree) = ft_tree_init(ft_fill_word_type((*tokens), ft_tk_size((*tokens))), ft_is_builtin((*tokens)));
		}
	}
	return ;
	// }
	
}
/* [ls] [-l] - [wc] [-l]*/