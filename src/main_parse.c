#include "../minishell.h"

int	main(int ac, char **av)
{
	if (ac != 2)
		return (1);
	if (ft_q_p_parse(av[1]))
		printf("no papi");
	else
		printf("%s\n", av[1]);
}