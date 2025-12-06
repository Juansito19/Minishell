#include "minishell.h"

/* ========================== */
/* ==========print=========== */
/* ========================== */

void	print_token(t_token **token)
{
	t_token	*temp;
	int		i;

	i = 0;
	temp = (*token);
	while (temp)
	{
		ft_printf("───────────────────────────────────\n");
		ft_printf(">> [%d] = %s\n", i, temp->content);
		ft_printf(">> type -> %d\n", temp->type);
		ft_write_type_branch(temp->type);
		ft_printf("───────────────────────────────────\n");
		i++;
		temp = temp->next;
	}
}

void	ft_write_type_branch(t_type type)
{
	if (type == T_PIPE)
		printf("branch [PIPE]\n");
	if (type == T_APPEND)
		printf("branch [>>]\n");
	if (type == T_HEREDOC)
		printf("branch [<<]\n");
	if (type == T_REDIR_IN)
		printf("branch [<]\n");
	if (type == T_REDIR_OUT)
		printf("branch [>]\n");
	if (type == T_SQUOTE)
		printf("branch [\']\n");
	if (type == T_DQUOTE)
		printf("branch [\"]\n");
	if (type == T_CMD)
		printf("branch [command]\n");
	if (type == T_BUILTIN)
		printf("branch [builtin]\n");
	if (type == T_EOF)
		printf("branch [EOF]\n");
}

void	print_tree(t_tree **tree)
{
	t_tree	*tmp_left;
	t_tree	*tmp_right;

	if (!(*tree))
		return ;
	ft_write_type_branch((*tree)->type);
	ft_double_putstr_fd((*tree)->content, 1);
	ft_printf("───────────────────────────────────\n");
	tmp_left = (*tree);
	while (tmp_left->left)
	{
		ft_printf("───────────────────────────────────\n");
		ft_printf("[left]\n");
		print_tree(&tmp_left->left);
		tmp_left = tmp_left->left;
	}
	tmp_right = (*tree);
	while (tmp_right->right)
	{
		ft_printf("───────────────────────────────────\n");
		ft_printf("[right]\n");
		print_tree(&tmp_right->right);
		tmp_right = tmp_right->right;
	}
}

void	print_tree_recursive(t_tree *tree, int depth, char *prefix)
{
	if (!tree)
		return ;
	for (int i = 0; i < depth; i++)
		ft_printf("    ");
	ft_printf("%s", prefix);
	ft_write_type_branch(tree->type);
	for (int j = 0; j < depth; j++)
		ft_printf("    ");
	for (int i = 0; tree->content[i]; i++)
		ft_printf("%s$\n", tree->content[i]);
	ft_printf("\n");
	if (tree->left)
		print_tree_recursive(tree->left, depth + 1, "├─L─ ");
	if (tree->right)
		print_tree_recursive(tree->right, depth + 1, "└─R─ ");
}

void	fprint_tree(t_tree **tree)
{
	ft_printf("\n=== ÁRBOL BINARIO ===\n");
	print_tree_recursive(*tree, 0, "ROOT ");
	ft_printf("=====================\n");
}
