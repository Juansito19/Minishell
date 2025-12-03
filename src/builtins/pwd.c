#include "minishell.h"

// ====== PWD ====== //

/*
función ft_pwd():
    buffer = crear buffer de tamaño PATH_MAX
    si getcwd(buffer, PATH_MAX) falla:
        imprimir error
        retornar 1
    imprimir buffer
    liberar buffer
    retornar 0
*/

int	ft_pwd(void)
{
	char	*buffer;

	buffer = getcwd(NULL, 0);
	if (!buffer)
		return (ft_print_error(0, "pwd : error : buff too small"));
	ft_printf("%s\n", buffer);
	free(buffer);
	return (0);
}
