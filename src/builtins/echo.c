#include "minishell.h"

// ====== ECHO ====== //

void	write_bucle(int i, char **str)
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

int	ft_flag_echo(int *ind, char **str)
{
	int	i;
	int	j;
	int	n_flag;

	i = 0;
	n_flag = 0;
	while (str[i])
	{
		if (!ft_strncmp(str[i], "-n", 2))
		{
			j = 2;
			while (str[i][j] && str[i][j] == 'n')
				j++;
			if (str[i][j] == '\0')
				n_flag = 1;
			else
				break ;
		}
		else
			break ;
		i++;
	}
	*ind = i;
	return (n_flag);
}

int	ft_echo(int ac, char **str)
{
	int	i;
	int	n_flag;

	n_flag = 0;
	if (ac < 2 || str[2] == NULL)
	{
		ft_putchar_fd('\n', 1);
		return (0);
	}
	if (ac >= 2)
	{
		n_flag = ft_flag_echo(&i, str + 2);
		if (n_flag)
			write_bucle(i, str + 2);
		else
		{
			write_bucle(i, str + 2);
			ft_putchar_fd('\n', 1);
		}
	}
	return (0);
}
