#include "minishell.h"

/* ================================= */
/* ======= yggdrasil branch ======== */
/* ================================= */

int	ft_branch_m(t_token *meta, t_tree **tree, t_token **tokens, t_data **data)
{
	t_token	*left;
	t_token	*right;
	char	**word;

	word = ft_fill_word_type(meta, 1);
	if (!word)
	{
		ft_free_all(tree, tokens, NULL, &word);
		return (ft_pd_error(ERR_MALLOC, NULL, 12));
	}
	(*tree) = ft_tree_init(word, ft_take_meta(meta->content), (*data)->path);
	if (!(*tree))
	{
		ft_free_all(tree, tokens, NULL, &word);
		return (ft_pd_error(ERR_MALLOC, NULL, 12));
	}
	left = ft_put_all_left(tokens, meta);
	right = ft_put_all_right(&meta->next);
	if (left)
		ft_yggdrasil(&left, &(*tree)->left, data);
	if (right)
		ft_yggdrasil(&right, &(*tree)->right, data);
	ft_free_tokens(&left);
	ft_free_tokens(&right);
	return (0);
}

int	ft_branch_w(t_tree **tree, t_token **tokens, char *path)
{
	char	**word;
	t_type	type;

	if (!tokens || !(*tokens))
		return (1);
	word = ft_fill_word_type((*tokens), ft_tk_size((*tokens)));
	if (!word)
	{
		ft_free_all(tree, tokens, NULL, &word);
		return (ft_pd_error(ERR_MALLOC, NULL, 12));
	}
	type = ft_is_builtin(tokens);
	(*tree) = ft_tree_init(word, type, path);
	if (!(*tree))
	{
		ft_free_all(tree, tokens, NULL, &word);
		return (ft_pd_error(ERR_MALLOC, NULL, 12));
	}
	return (0);
}
