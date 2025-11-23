#include "../minishell.h"

/* ================================= */
/* ========== tree utils =========== */
/* ================================= */

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
