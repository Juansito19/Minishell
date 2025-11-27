#include "../minishell.h"

void	ft_check_input(t_data **data, char *input)
{
	if (ft_big_prick_parse(input))
	{
		ft_print_error(0, "Error: Syntax error");
		return ;
	}
	(*data)->tokens = ft_token(input, 0);
	ft_yggdrasil(&(*data)->tokens, &(*data)->yggdrasil, data);
	fprint_tree(&(*data)->yggdrasil);
}

t_data	*ft_init_data(char **env)
{
	t_data	*data;

	data = malloc(1 * sizeof(t_data));
	if (!data)
		return (NULL);
	data->exit_status = -1;
	data->infile = -1;
	data->outfile = -1;
	data->path = NULL;
	ft_find_path(&data, env);
	data->tokens = NULL;
	data->yggdrasil = NULL;
	return (data);
}

int	ft_minishell(char **env)
{
	char	*input;
	t_data	*data;

	data = ft_init_data(env);
	while (1)
	{
		input = readline("bostero$> ");
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		ft_check_input(&data, input);
		add_history(input);
		if (!ft_strncmp(input, "exit", 5))
		{
			free(input);
			ft_clean_data(&data);
			break ;
		}
		ft_free_all(&data->yggdrasil, &data->tokens, input, NULL);
	}
	rl_clear_history();
	return (0);
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;

	ft_random_banner();
	ft_minishell(env);
	return (0);
}
