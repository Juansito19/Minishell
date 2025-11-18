#include "../minishel.h"

/* ========================== */
/* ===========tree=========== */
/* ========================== */

t_tree	*ft_tree_init(void **content)
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
