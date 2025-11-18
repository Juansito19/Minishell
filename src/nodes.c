#include "../minishel.h"

/* ========================= */
/* ===========cmd=========== */
/* ========================= */


t_tree	*ft_tree_init(void **content)
{
	t_tree	*new_cmd;

	new_cmd = (t_tree *)malloc(1 * sizeof(t_tree));
	if (!new_cmd)
		return (NULL);
	new_cmd->next = NULL;
	new_cmd->infile = 0;
	new_cmd->outfile = 0;
	new_cmd->pipe[0] = 0;
	new_cmd->pipe[1] = 1;
	new_cmd->is_builting = 0;
	new_cmd->av = content;
	return (new_cmd);
}

t_token	*ft_token_init(void **content)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(1 * sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->left = NULL;
	new_token->right = NULL;
	new_token->content = content;
	return (new_token);
}

void	ft_cmdadd_back(t_cmd **cmd, t_cmd *new)
{
	if (!*cmd)
		(*cmd) = new;
	else
	{
		while ((*cmd)->next)
			cmd = &(*cmd)->next;
		(*cmd)->next = new;
	}
}

void	ft_cmdsclean(t_cmd **cmds)
{
	t_cmd	*aux;

	if (!cmds)
		return ;
	while (*cmds)
	{
		aux = (*cmds)->next;
		free((*cmds)->av);
		free((*cmds));
		*cmds = aux;
	}
	*cmds = NULL;
}

/* ========================= */
/* =========tokens========== */
/* ========================= */

void	ft_tokenadd_right(t_token **tokens, t_token *new)
{
	if (!*tokens)
		(*tokens) = new;
	else
	{
		while ((*tokens)->right)
			tokens = &(*tokens)->right;
		(*tokens)->right = new;
	}
}

void	ft_tokenadd_left(t_token **tokens, t_token *new)
{
	if (!*tokens)
		(*tokens) = new;
	else
	{
		while ((*tokens)->left)
			tokens = &(*tokens)->left;
		(*tokens)->left = new;
	}
}


/* 

si posicion es = a "
todo lo que haya dentro que se != de la " SE GUARDA


*/