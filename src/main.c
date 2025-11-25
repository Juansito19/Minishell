#include "../minishell.h"

int	ft_minishell(char **env)
{
	char	*input;
	t_token	*token;
	t_tree	*tree = NULL;

	(void)env;
	printf("holi\n");
	while (1)
	{
		input = readline("bostero $> ");
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		// if (ft_strlen(input))
		// 	add_history(input);
		token = ft_token(input, 0);
		ft_yggdrasil(&token, &tree);
		fprint_tree(&tree);
		if (!ft_strncmp(input, "exit", ft_strlen("exit")))
		{
			ft_free_all(&tree, &token, &input);
			break ;
		}
		ft_free_all(&tree, &token, &input);
		// ft_free_tokens(&token);
		// ft_clean_yggdrasil(&tree);
		// free(input);
	}
	// ft_free_tokens(&token);
	// ft_clean_yggdrasil(&tree);
	// free(input);
	// rl_clear_history();
	return (0);
}


int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	// t_token *token;
	// t_token *token_pipe;
	// t_token *token_red;
	// t_token *tokens_left;
	// t_token *tokens_right;
	// t_tree *tree;

	/* CREAMOS LOS TOKENS */
	ft_banner_1();
	ft_minishell(env);
	// token = ft_token(s, 0);
	// print_token(&token);
	// printf("llega 1\n");
	// ft_yggdrasil(&token, &tree);
	// printf("llega 2\n");
	// fprint_tree(&tree);
	// printf("llega 3\n");
	// char **sss = ft_fill_word_type(token, ft_tk_size(token));
	// printf("\n\nDOBLE ARRAY\n\n");
	// ft_double_putstr_fd(sss, 1);
	// ft_free_all_array(sss);

	// /* BUSCAMOS EL NODO PIPE */	
	// token_pipe = ft_search_pipe(&token);
	// if (token_pipe)
	// 	printf("token_pipe = %s\n", token_pipe->content);
	// else
	// 	printf("no encontro nada");

	// /* BUSCAMOS EL NODO RED */	
	// token_red = ft_search_red(&token);
	// if (token_red)
	// 	printf("token_red = %s\n", token_red->content);
	// else
	// 	printf("no encontro nada");
	
	/* CREAMOS EL ARBOL */
	// tree = ft_tree_init(ft_split(token_pipe->content, ' '), token_pipe->type);
	// if (!tree)
	// {
	// 	printf("error con tree");
	// 	return (0);
	// }
	// printf("\ntree = %s\n", *tree->content);

	// /* PONEMOS TODO A LA IZQUIERDA */
	// tokens_left = ft_put_all_left(&token, token_pipe);
	// if (!tokens_left)
	// 	return (printf("error con token_left\n"));
	// printf("\nnodos a la izquierda\n");
	// print_nodes(&tokens_left);

	// /* PONEMOS TODO A LA DERECHA */
	// tokens_right = ft_put_all_right(&token_pipe->next);
	// if (!tokens_right)
	// 	return (printf("error con token_right\n"));
	// printf("\nnodos a la derecha\n");
	// print_nodes(&tokens_right);

	// ft_free_tokens(&tokens_left);
	// ft_free_tokens(&tokens_right);
	// free(s);
	// ft_minishell(env);
	return (0);
}
