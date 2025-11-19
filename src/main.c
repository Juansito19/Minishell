#include "../minishel.h"

int	ft_minishell(char **env)
{
	char *input;

	(void)env;
	while (1)
	{
		input = readline("putito $> ");
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (ft_strlen(input))
			add_history(input);
		if (!ft_strncmp(input, "exit", ft_strlen("exit")))
			break ;
		// printf("%s\n", input);
		free(input);
	}
	rl_clear_history();
	free(input);
	return (0);
}

void	print_nodes(t_token **token)
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

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)env;
	t_token *token;
	t_token *token_pipe;
	t_token *tokens_left;
	t_token *tokens_right;
	// t_tree *tree;

	/* CREAMOS LOS TOKENS */
	char *s = ft_dblstr_join(av+1);
	token = ft_token(s, 0);
	print_nodes(&token);

	/* BUSCAMOS EL NODO PIPE */	
	token_pipe = ft_search_pipe(&token);
	if (token_pipe)
		printf("token_pipe = %s\n", token_pipe->content);
	else
		printf("no encontro nada");
	
	/* CREAMOS EL ARBOL */
	// tree = ft_tree_init(ft_split(token_pipe->content, ' '), token_pipe->type);
	// if (!tree)
	// {
	// 	printf("error con tree");
	// 	return (0);
	// }
	// printf("\ntree = %s\n", *tree->content);

	/* PONEMOS TODO A LA IZQUIERDA */
	tokens_left = ft_put_all_left(&token, token_pipe);
	if (!tokens_left)
		return (printf("error con token_left\n"));
	printf("\nnodos a la izquierda\n");
	print_nodes(&tokens_left);

	/* PONEMOS TODO A LA DERECHA */
	tokens_right = ft_put_all_right(&token_pipe->next);
	if (!tokens_right)
		return (printf("error con token_right\n"));
	printf("\nnodos a la derecha\n");
	print_nodes(&tokens_right);

	ft_free_tokens(&tokens_left);
	ft_free_tokens(&tokens_right);
	ft_free_tokens(&token);
	free(s);
	// ft_minishell(env);
	return (0);
}
