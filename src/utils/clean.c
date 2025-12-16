#include "minishell.h"

/* ========================== */
/* ========= clean ========== */
/* ========================== */

void	ft_free_tokens(t_token **head)
{
	t_token	*current;
	t_token	*next;

	if (!(*head))
		return ;
	current = (*head);
	while (current)
	{
		next = current->next;
		if (current->content)
			free(current->content);
		free(current);
		current = next;
	}
	*head = NULL;
}

int	ft_clean_expanders(t_expand **expander)
{
	if ((*expander)->init_quote)
		free((*expander)->init_quote);
	printf("10\n");
	if ((*expander)->end_quote)
		free((*expander)->end_quote);
	printf("20\n");
	if ((*expander)->var)
		free((*expander)->var);
	printf("30\n");
	if ((*expander)->split)
	ft_free_all_array((*expander)->split);
	printf("40\n");
	if ((*expander)->tmp_var)
		free((*expander)->tmp_var);
	printf("50\n");
	if ((*expander)->aux)
		free((*expander)->aux);
	printf("60\n");
	free((*expander));
	return (1);
}

void	ft_clean_yggdrasil(t_tree **tree)
{
	if (!(*tree))
		return ;
	if ((*tree)->left)
		ft_clean_yggdrasil(&(*tree)->left);
	if ((*tree)->right)
		ft_clean_yggdrasil(&(*tree)->right);
	if ((*tree)->content)
		ft_free_all_array((*tree)->content);
	if ((*tree)->path)
		free((*tree)->path);
	free((*tree));
	*tree = NULL;
}

void	ft_clean_data(t_data **data)
{
	if (!(*data))
		return ;
	if ((*data)->path)
		free((*data)->path);
	if ((*data)->env)
		ft_free_all_array((*data)->env);
	if ((*data)->yggdrasil)
		ft_clean_yggdrasil(&(*data)->yggdrasil);
	if ((*data)->tokens)
		ft_free_tokens(&(*data)->tokens);
	free((*data));
}

void	*ft_free_all(t_tree **tree, t_token **token, char **input, char ***s)
{
	if (tree)
	{
		ft_clean_yggdrasil(tree);
		*tree = NULL;
	}
	if (token)
	{
		ft_free_tokens(token);
		*token = NULL;
	}
	if (s)
	{
		ft_free_all_array(*s);
		*s = NULL;
	}
	if (input)
	{
		free(*input);
		*input = NULL;
	}
	return (NULL);
}
