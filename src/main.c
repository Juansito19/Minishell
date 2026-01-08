#include "minishell.h"

int	g_status = 0;

void	ft_check_input(t_data **data, char *input)
{
	g_status = 0;
	if (ft_big_prick_parse(input))
	{
		(*data)->exit_status = 2;
		ft_print_error(0, "Minishell: error: Syntax error");
		return ;
	}
	(*data)->tokens = ft_token(input, 0);
	// printf("====PRIMERO====\n");
	// print_token(&(*data)->tokens);
	ft_mimir(&(*data)->tokens, (*data)->env, (*data)->exit_status);
	ft_search_quotes(&(*data)->tokens);
	ft_search_eof(&(*data)->tokens);
	ft_ratatoskr(&(*data)->tokens);
	// printf("====SEGUNDO====\n");
	// print_token(&(*data)->tokens);
	ft_yggdrasil(&(*data)->tokens, &(*data)->yggdrasil, data);
	// fprint_tree(&(*data)->yggdrasil);
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

/* 

cosas a revisar:
con comandos_
echo "" | ""
echo "" | echo ""
ls "" | ""
ls "" | ls ""

aca sale este mensaje de error sin salto de linea
bostero$> ls "" | ls ""
ademas habria que verificar el temita de "/usr/bin/ls" deberia ser "ls"
/usr/bin/ls: /usr/bin/ls: cannot access ''cannot access '': No such file or directory: No such file or directory

*/

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
		ft_check_input(data, input);
		free(input);
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
