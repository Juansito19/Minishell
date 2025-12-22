#include "minishell.h"

int	g_status = 0;

void	ft_check_input(t_data **data, char *input)
{
	if (ft_big_prick_parse(input))
	{
		ft_print_error(0, "Error: Syntax error");
		return ;
	}
	(*data)->tokens = ft_token(input, 0);
	printf("====PRIMERO====\n");
	print_token(&(*data)->tokens);
	ft_mimir(&(*data)->tokens, (*data)->env, (*data)->exit_status);
	ft_search_quotes(&(*data)->tokens);
	printf("====SEGUNDO====\n");
	print_token(&(*data)->tokens);
	ft_search_eof(&(*data)->tokens);
	ft_yggdrasil(&(*data)->tokens, &(*data)->yggdrasil, data);
	ft_ratatoskr(&(*data)->yggdrasil);
	fprint_tree(&(*data)->yggdrasil);
}

t_data	*ft_init_data(char **env)
{
	t_data	*data;

	data = malloc(1 * sizeof(t_data));
	if (!data)
	{
		ft_pd_error(ERR_MALLOC, NULL, 12);
		return (NULL);
	}
	data->exit_status = 0;
	data->infile = -1;
	data->outfile = -1;
	data->path = NULL;
	ft_find_path(&data, env);
	data->env = ft_array_dup(env);
	data->tokens = NULL;
	data->yggdrasil = NULL;
	return (data);
}

int	ft_minishell(t_data **data)
{
	char	*input;

	input = NULL;
	while (1)
	{
		ft_hugin_signal();
		input = readline("bostero$> ");
		if (!input)
		{
			free(input);
			ft_clean_data(data);
			printf("exit\n");
			break ;
		}
		ft_check_input(data, input);
		add_history(input);
		ft_odin_signal();
		// if (!ft_strncmp(input, "exit", 5))
		// {
		// 	free(input);
		// 	ft_clean_data(data);
		// 	break ;
		// }
		free(input);
		ft_heimdall(data, &(*data)->yggdrasil, (*data)->env, 0);
		ft_files_destroyer(&(*data)->yggdrasil);
		ft_free_all(&(*data)->yggdrasil, &(*data)->tokens, &input, NULL);
	}
	rl_clear_history();
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_data	*data;

	(void)ac;
	(void)av;
	data = ft_init_data(env);
	if (!data)
		return (ft_pd_error(ERR_MALLOC, NULL, 12));
	// ft_random_banner();
	ft_banner_3();
	ft_minishell(&data);
	return (0);
}
