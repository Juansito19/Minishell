#include "minishell.h"

int	g_status = 0;

static int	ft_check_input(t_data **data, char *input)
{
	g_status = 0;
	if (ft_big_prick_parse(input))
	{
		(*data)->exit_status = 2;
		ft_print_error(0, "Minishell: error: Syntax error");
		free(input);
		input = NULL;
		return (1);
	}
	(*data)->tokens = ft_token(input, 0);
	ft_mimir(&(*data)->tokens, data);
	ft_search_quotes(&(*data)->tokens);
	ft_search_eof(&(*data)->tokens);
	ft_ratatoskr(&(*data)->tokens);
	ft_yggdrasil(&(*data)->tokens, &(*data)->yggdrasil, data);
	if (g_status == 130)
	{
		(*data)->exit_status = g_status;
		ft_files_destroyer(&(*data)->yggdrasil);
		ft_free_all(&(*data)->yggdrasil, &(*data)->tokens, &input, NULL);
		return (1);
	}
	free(input);
	input = NULL;
	return (0);
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
	data->env = NULL;
	if (!env || !*env)
		data->env = ft_no_env();
	else
		data->env = ft_array_dup(env);
	data->tokens = NULL;
	data->yggdrasil = NULL;
	return (data);
}

int	ft_minishell(t_data **data, int status)
{
	char	*input;

	input = NULL;
	while (1)
	{
		ft_hugin_signal();
		if (isatty(STDIN_FILENO))
			input = readline("bostero$> ");
		else
			input = readline("");
		if (!input)
			break ;
		add_history(input);
		if (ft_check_input(data, input))
			continue ;
		ft_odin_signal();
		status = ft_heimdall(data, &(*data)->yggdrasil, (*data)->env, 0);
		(*data)->exit_status = status;
		ft_files_destroyer(&(*data)->yggdrasil);
		ft_free_all(&(*data)->yggdrasil, &(*data)->tokens, NULL, NULL);
	}
	ft_clean_data(data);
	rl_clear_history();
	return (0);
}

/*
	Que nos intenten romper la minishell
	Ponerla bonita ;)
	Poner los comentarios en los .h de las funciones tipo brief
	Hacer la historia en el Readme
	Agregar los cabeceros
*/

int	main(int ac, char **av, char **env)
{
	t_data	*data;

	(void)ac;
	(void)av;
	data = ft_init_data(env);
	if (!data)
		return (ft_pd_error(ERR_MALLOC, NULL, 12));
	if (isatty(STDIN_FILENO))
		ft_banner_3();
	ft_minishell(&data, 0);
	if (isatty(STDIN_FILENO))
		ft_fprintf(1, "exit\n");
	return (0);
}
