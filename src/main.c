#include "../minishel.h"

int main(int ac, char **av)
{
	if (ac < 2)
		return (0);
	ft_double_putstr_fd(av, 1);
	return (0);
}
