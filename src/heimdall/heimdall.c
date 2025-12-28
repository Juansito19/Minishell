#include "minishell.h"

int	ft_bifrost(t_tree **ygg)
{
	char	*aux;
	char	*tmp_dir;
	char	**path_dir;
	int		i;

	i = 0;
	tmp_dir = NULL;
	if ((*ygg)->content[0][0] == '.' || (*ygg)->content[0][0] == '\0')
		return (ft_pd_error(ERR_CMD_NOT_FOUND, (*ygg)->content[0], 12));
	if (access((*ygg)->content[0], X_OK) == 0)
		return (0);
	path_dir = ft_split((*ygg)->path, ':');
	if (!path_dir)
		return (ft_pd_error(ERR_MALLOC, NULL, 12));
	while (path_dir[i])
	{
		if (tmp_dir)
			free(tmp_dir);
		aux = ft_strjoin(path_dir[i], "/");
		tmp_dir = ft_strjoin(aux, (*ygg)->content[0]);
		if (!tmp_dir)
		{
			ft_free_all(NULL, NULL, &aux, &path_dir);
			return (ft_pd_error(ERR_MALLOC, NULL, 12));
		}
		if (access(tmp_dir, X_OK) == 0)
			break ;
		free(aux);
		i++;
	}
	if (path_dir[i] == NULL)
	{
		ft_free_all(NULL, NULL, &tmp_dir, &path_dir);
		return (ft_pd_error(ERR_CMD_NOT_FOUND, (*ygg)->content[0], 12));
	}
	free(aux);
	ft_free_all_array(path_dir);
	free((*ygg)->content[0]);
	(*ygg)->content[0] = ft_strdup(tmp_dir);
	if (!(*ygg)->content[0])
	{
		free(tmp_dir);
		return (ft_pd_error(ERR_MALLOC, NULL, 12));
	}
	free(tmp_dir);
	return (0);
}

int	ft_heimdall_cmd(t_data **data, t_tree **ygg, char **env, int forked)
{
	char	**av;
	int		status;

	status = 0;
	av = (*ygg)->content;
	if ((*ygg)->type == T_BUILTIN)
	{
		status = ft_builtins(data, av, env);
		if (forked)
			exit(status);
		return (status);
	}
	if (ft_bifrost(ygg))
	{
		if (forked)
			exit(127);
		return (127);
	}
	if (forked)
	{
		if (execve(av[0], av, env) < 0)
			exit(ft_pd_error(ERR_EXECVE, NULL, 126));
	}
	else
	{
		(*ygg)->pid = fork();
		if ((*ygg)->pid == -1)
			return (WEXITSTATUS(status));
		if ((*ygg)->pid == 0)
		{
			ft_odinson_signal();
			if (execve(av[0], av, env) < 0)
				exit(ft_pd_error(ERR_EXECVE, NULL, 126));
		}
		else
		{
			waitpid((*ygg)->pid, &status, 0);
			return (WEXITSTATUS(status));
		}
	}
	return (0);
}


// Hay que revisar la funcion para crear su propia estructura
// y poder meter todas las variables que necesitemos
// Proximamente hay que recuperar en caso de que el comando falle la salida
// estandar para escribir el error y que no salga por el fd
int ft_heimdall_redir(t_data **data, t_tree **ygg, char **env, int forked)
{
    t_tree  *curr;
    t_tree  *file_node;
    t_tree  *cmd_node;
    int     fd_out;
    int     fd_in;
    int     tmp_fd;
    int     flags;
    // Variables para guardar el estado original
    int     stdin_backup;
    int     stdout_backup;
    int     status;

    cmd_node = (*ygg)->left; 
    curr = *ygg;
    fd_out = -1;
    fd_in = -1;
    stdin_backup = -1;
    stdout_backup = -1;
    status = 0;

    // --- 1. SAVE: Guardamos STDIN y STDOUT originales si no es un fork ---
    // Si estamos en un hijo (forked=1), no hace falta porque el hijo muere.
    // Pero si es un builtin o shell principal, ES VITAL.
    if (!forked)
    {
        stdin_backup = dup(STDIN_FILENO);
        stdout_backup = dup(STDOUT_FILENO);
    }

    // --- 2. Bucle para abrir archivos (Igual que antes) ---
    while (curr && ft_is_red(curr->type))
    {
        if (curr->right && ft_is_red(curr->right->type))
            file_node = curr->right->left; 
        else
            file_node = curr->right;

        if (curr->type == T_REDIR_IN)
        {
            tmp_fd = open(file_node->content[0], O_RDONLY);
            if (tmp_fd < 0) 
            {
                // Si falla, hay que restaurar antes de salir si hicimos backups
                if (!forked)
                {
                    close(stdin_backup);
                    close(stdout_backup);
                }
                return (ft_pd_error(ERR_PERMISSION_DENIED, file_node->content[0], 1));
            }
            if (fd_in != -1) close(fd_in);
            fd_in = tmp_fd;
        }
        else 
        {
            flags = O_CREAT | O_WRONLY;
            if (curr->type == T_REDIR_OUT) flags |= O_TRUNC;
            else flags |= O_APPEND;
            
            tmp_fd = open(file_node->content[0], flags, 0644);
            if (tmp_fd < 0)
            {
                if (!forked)
                {
                    close(stdin_backup);
                    close(stdout_backup);
                }
                return (ft_pd_error(ERR_PERMISSION_DENIED, file_node->content[0], 1));
            }
            if (fd_out != -1) close(fd_out);
            fd_out = tmp_fd;
        }

        if (curr->right && ft_is_red(curr->right->type))
            curr = curr->right;
        else
            break;
    }

    // --- 3. Aplicar dup2 (Redirección activa) ---
    if (fd_in != -1)
    {
        dup2(fd_in, STDIN_FILENO);
        close(fd_in);
    }
    if (fd_out != -1)
    {
        dup2(fd_out, STDOUT_FILENO);
        close(fd_out);
    }

    // --- 4. Ejecutar el comando ---
    if (cmd_node)
        status = ft_heimdall(data, &cmd_node, env, forked);
    
    // --- 5. RESTORE: Volver a conectar teclado y pantalla ---
    if (!forked)
    {
        // Recuperamos la entrada estándar (teclado)
        if (stdin_backup != -1)
        {
            dup2(stdin_backup, STDIN_FILENO);
            close(stdin_backup);
        }
        // Recuperamos la salida estándar (pantalla)
        if (stdout_backup != -1)
        {
            dup2(stdout_backup, STDOUT_FILENO);
            close(stdout_backup);
        }
    }

    return (status);
}

// int ft_heimdall_redir(t_data **data, t_tree **ygg, char **env, int forked)
// {
//     t_tree  *curr;
//     t_tree  *file_node;
//     t_tree  *cmd_node;
//     int     fd_out;
//     int     fd_in;
//     int     tmp_fd;
//     int     flags;

//     // 1. Identificar el comando base (ls) que está a la izquierda del primer nodo
//     cmd_node = (*ygg)->left; 

//     curr = *ygg;
//     fd_out = -1;
//     fd_in = -1;

//     // 2. Bucle para recorrer la cadena de redirecciones hacia la DERECHA
//     while (curr && ft_is_red(curr->type))
//     {
//         // TRUCO: Decidir dónde está el archivo
//         // Si el hijo derecho es OTRA redirección, el archivo está a la IZQUIERDA del hijo derecho.
//         // Si el hijo derecho ya no es redirección, el archivo es el hijo DERECHO directo.
//         if (curr->right && ft_is_red(curr->right->type))
//             file_node = curr->right->left; 
//         else
//             file_node = curr->right;

//         // Abrimos el archivo encontrado
//         if (curr->type == T_REDIR_IN)
//         {
//             tmp_fd = open(file_node->content[0], O_RDONLY);
//             if (tmp_fd < 0) return (ft_pd_error(ERR_PERMISSION_DENIED, file_node->content[0], 1));
//             if (fd_in != -1) close(fd_in);
//             fd_in = tmp_fd;
//         }
//         else // OUTPUT o APPEND
//         {
//             flags = O_CREAT | O_WRONLY;
//             if (curr->type == T_REDIR_OUT)
//                 flags |= O_TRUNC;
//             else
//                 flags |= O_APPEND;
            
//             tmp_fd = open(file_node->content[0], flags, 0644);
//             if (tmp_fd < 0) return (ft_pd_error(ERR_PERMISSION_DENIED, file_node->content[0], 1));
//             if (fd_out != -1) close(fd_out);
//             fd_out = tmp_fd;
//         }

//         // Avanzamos al siguiente nodo de la cadena (hacia la derecha)
//         // Ojo: Si el hijo derecho no era redir, terminamos el bucle
//         if (curr->right && ft_is_red(curr->right->type))
// 		{
//             curr = curr->right;
// 			printf("puto\n");
// 		}
//         else
//             break;
//     }
// 	printf("puto2\n");
//     // 3. Aplicar dup2 (El resto es igual que antes)
//     if (fd_in != -1)
//     {
//         dup2(fd_in, STDIN_FILENO);
//         close(fd_in);
//     }
//     if (fd_out != -1)
//     {
//         dup2(fd_out, STDOUT_FILENO);
//         close(fd_out);
//     }

//     // 4. Ejecutar el comando (ls) que encontramos al principio
//     if (cmd_node)
//         return (ft_heimdall(data, &cmd_node, env, forked));
    
//     return (0);
// }

// int	ft_heimdall_redir(t_data **data, t_tree **ygg, char **env, int forked)
// {
// 	int	fd_file;
// 	int	fd_origin;
// 	int	fd_target;
// 	int	fd_status;
// 	int	status;

// 	status = 0;
// 	fd_file = 0;
// 	fd_origin = -1;
// 	fd_target = -1;
// 	fd_status = 0;
// 	if ((*ygg)->type == T_REDIR_IN)
// 		fd_file = open((*ygg)->right->content[0], O_RDONLY);
// 	else if ((*ygg)->type == T_REDIR_OUT)
// 		fd_file = open((*ygg)->right->content[0], O_CREAT | O_TRUNC | O_WRONLY);
// 	else if ((*ygg)->type == T_APPEND)
// 		fd_file = open((*ygg)->right->content[0], O_CREAT | O_TRUNC | O_WRONLY | O_APPEND);
// 	if (fd_file < 0) // esto creo que es fd_file
// 		return (ft_pd_error(ERR_PERMISSION_DENIED, (*ygg)->right->content[0], 1));
// 	if ((*ygg)->type == T_REDIR_IN)
// 		fd_target = STDIN_FILENO;
// 	else
// 		fd_target = STDOUT_FILENO;
// 	if (!forked)
// 		fd_origin = dup(fd_target);
// 	else
// 	{
// 		dup2(fd_file, fd_target);
// 		close(fd_file);
// 	}
// 	if ((*ygg)->left)
// 		status = ft_heimdall(data, &(*ygg)->left, env, forked);
// 	if (!forked)
// 	{
// 		dup2(fd_origin, fd_target);
// 		close(fd_origin);
// 	}
// 	return (status);
// }

int	ft_heimdall_pipe(t_data **data, t_tree **ygg, char **env, int forked)
{
	int	left_pid;
	int	right_pid;
	int	status;

	status = 0;
	if (pipe((*ygg)->pipe)) // Hay que ver como le damos valor a exit_status a la hora de terminar
		return (ft_pd_error(ERR_PIPE_FAILED, NULL, 32));
	left_pid = fork();
	if (!left_pid)
	{
		ft_odinson_signal();
		forked = 1;
		close((*ygg)->pipe[0]);
		dup2((*ygg)->pipe[1], STDOUT_FILENO);
		close((*ygg)->pipe[1]);
		if ((*ygg)->left)
			ft_heimdall(data, &(*ygg)->left, env, forked);
		exit(status);
	}
	right_pid = fork();
	if (!right_pid)
	{
		ft_odinson_signal();
		forked = 1;
		close((*ygg)->pipe[1]);
		dup2((*ygg)->pipe[0], STDIN_FILENO);
		close((*ygg)->pipe[0]);
		if ((*ygg)->right)
			ft_heimdall(data, &(*ygg)->right, env, forked);
		exit(status);
	}
	close((*ygg)->pipe[0]);
	close((*ygg)->pipe[1]);
	waitpid(left_pid, NULL, 0);
	waitpid(right_pid, &status, 0);
	if (forked)
		exit(WEXITSTATUS(status));
	return (WEXITSTATUS(status));
}

int	ft_heimdall(t_data **data, t_tree **ygg, char **env, int forked)
{
	if (!ygg | !(*ygg))
		return (0);
	if ((*ygg)->type == T_PIPE)
		return (ft_heimdall_pipe(data, ygg, env, forked));
	if (ft_is_red((*ygg)->type))
		return (ft_heimdall_redir(data, ygg, env, forked));
	if ((*ygg)->type == T_CMD || (*ygg)->type == T_BUILTIN)
		return (ft_heimdall_cmd(data, ygg, env, forked));
	return (0);
}
