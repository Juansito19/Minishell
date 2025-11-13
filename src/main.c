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

int main(int ac, char **av, char **env)
{
	(void)ac;	
	(void)av;
	ft_minishell(env);
	return (0);
}
