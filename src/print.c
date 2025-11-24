#include "../minishell.h"


void	print_token(t_token **token)
{
	t_token *temp;
	int i;

	i = 0;
	temp = (*token);
	while (temp)
	{
		printf("───────────────────────────────────\n");
		printf(">> [%d] = %s\n", i, temp->content);
		printf("───────────────────────────────────\n");
		i++;
		temp = temp->next;
	}
}

void	ft_write_type_branch(t_token_type type)
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
}

void	print_tree(t_tree **tree)
{
	t_tree	*tmp_left;
	t_tree	*tmp_right;

	if (!(*tree))
		return ;
	ft_write_type_branch((*tree)->type);
	ft_double_putstr_fd((*tree)->content, 1);
	printf("───────────────────────────────────\n");
	tmp_left = (*tree);
	while (tmp_left->left)
	{
		printf("───────────────────────────────────\n");
		printf("[left]\n");
		print_tree(&tmp_left->left);
		tmp_left = tmp_left->left;
	}
	tmp_right = (*tree);
	while (tmp_right->right)
	{
		printf("───────────────────────────────────\n");
		printf("[right]\n");
		print_tree(&tmp_right->right);
		tmp_right = tmp_right->right;
	}
}

void	print_tree_recursive(t_tree *tree, int depth, char *prefix)
{
	int	i;

	if (!tree)
		return ;
	for (i = 0; i < depth; i++)
		printf("	");
	printf("%s", prefix);
	ft_write_type_branch(tree->type);
	for (i = 0; i < depth; i++)
		printf("	");
	ft_double_putstr_fd(tree->content, 1);
	printf("\n");
	if (tree->left)
		print_tree_recursive(tree->left, depth + 1, "├─L─ ");
	if (tree->right)
		print_tree_recursive(tree->right, depth + 1, "└─R─ ");
}

void	fprint_tree(t_tree **tree)
{
	printf("\n=== ÁRBOL BINARIO ===\n");
	print_tree_recursive(*tree, 0, "ROOT ");
	printf("=====================\n");
}
