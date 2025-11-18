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
	char *s = ft_dblstr_join(av+1);
	token = ft_token(s, 0);
	print_nodes(&token);
	ft_free_tokens(&token);
	free(s);
	// ft_minishell(env);
	return (0);
}
