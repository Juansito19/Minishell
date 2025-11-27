#include "../minishell.h"

int	main(int ac, char **av)
{
	if (ac != 2)
		return (1);
	if (ft_big_prick_parse(av[1]))
		printf("no papi");
	else
		printf("%s\n", av[1]);
}