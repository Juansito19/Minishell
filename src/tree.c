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
	new_tree->is_builting = -1;
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

// t_tree	*ft_tree(t_token **tokens, t_tree *tree)
// {
// 	t_token	*token_pipe;

// 	token_pipe = ft_search_pipe(tokens);
// 	if (token_pipe)
// 	{
// 		tree = ft_tree_init(&token_pipe->content, T_PIPE);
// 		if (!tree)
// 			return (NULL);
		
// 	}
// 	else
// 		return (funcion_para_comando_simple());
// }
