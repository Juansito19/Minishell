#include "../minishell.h"

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
		// free(current);
		current = next;
	}
}

void	ft_clean_yggdrasil(t_tree **tree)
{
	t_tree	*tmp_left;
	t_tree	*tmp_right;

	if (!(*tree))
		return ;
	tmp_left = (*tree);
	if (tmp_left->left)
	{
		ft_free_all_array((*tree)->content);
		ft_clean_yggdrasil(&tmp_left->left);
		free(*tree);
		return ;
	}
	tmp_right = (*tree);
	if (tmp_right->right)
	{
		ft_free_all_array((*tree)->content);
		ft_clean_yggdrasil(&tmp_right->right);
		free((*tree));
		return ;
	}
	ft_free_all_array((*tree)->content);
	free((*tree));
}

