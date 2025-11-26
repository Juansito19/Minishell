#include "../minishell.h"

t_data	*ft_init_data(void)
{
	t_data	*data;

	data = malloc(1 * sizeof(t_data));
	if (!data)
		return (NULL);
	data->exit_status = -1;
	data->infile = -1;
	data->outfile = -1;
	data->path = NULL;
	data->tokens = NULL;
	data->yggdrasil = NULL;
	return (data);
}

int	ft_minishell(char **env)
{
	char	*input;
	t_data	*data;

	data = ft_init_data();
	(void)env;
	while (1)
	{
		input = readline("bostero$> ");
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		// if (ft_strlen(input))
		// 	add_history(input);
		data->tokens = ft_token(input, 0);
		ft_yggdrasil(&data->tokens, &data->yggdrasil);
		fprint_tree(&data->yggdrasil);
		if (!ft_strncmp(input, "exit", ft_strlen("exit")))
		{
			free(input);
			ft_clean_data(&data);
			break ;
		}
		ft_free_all(&data->yggdrasil, &data->tokens, &input, NULL);
	}
	// rl_clear_history();
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
