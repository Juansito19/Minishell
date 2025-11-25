#include "../minishell.h"

/* ========================== */
/* ==========clean=========== */
/* ========================== */

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

void	ft_clean_yggdrasil(t_tree **tree)
{
	t_tree	*tmp_left;
	t_tree	*tmp_right;

	if (!(*tree))
		return ;
	tmp_left = (*tree)->left;
	if (tmp_left)
		ft_clean_yggdrasil(&tmp_left);
	tmp_right = (*tree)->right;
	if (tmp_right)
		ft_clean_yggdrasil(&tmp_right);
	ft_free_all_array((*tree)->content);
	free((*tree));
}

void	ft_free_all(t_tree **tree, t_token **token, char **input)
{
	if ((*tree))
		ft_clean_yggdrasil(tree);
	if ((*token))
		ft_free_tokens(token);
	if ((*input))
		free(*input);
}
