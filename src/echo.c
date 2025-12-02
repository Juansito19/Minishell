#include "../minishell.h"

/*

el primer parametro me dice cuantos argumentos trabajamos:
no es lo mismo:
	echo hola
	echo -n hola
	echo -n hola que tal
el int me dice:
echo			-> ac[0] el propio builtin
-n				-> ac[1] (flag que cambia el comportamiento si lo hay)
hola que tal	-> ac[2, 3, ...] (lo que se debe imprimir como tal)
*/

static void	write_bucle(int i, char **str)
{
	int	j;

	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			ft_putchar_fd(str[i][j], 1);
			j++;
		}
		if (str[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
}

int	ft_echo(int ac, char **str)
{
	int	i;
	int	j;

	if (ac < 2 || str[1] == NULL)
	{
		ft_putchar_fd('\n', 1);
		return (0);
	}
	if (ac >= 2)
	{
		i = 1;
		if (ft_strncmp(str[i], "-n", 2))
		{
			write_bucle(i, str);
			ft_putchar_fd('\n', 1);
		}
		else
		{
			if (str[i + 1])
			{
				i++;
				write_bucle(i, str);
			}
			else if (str[i + 1] == NULL)
				i++;
		}
	}
	return (0);
}
