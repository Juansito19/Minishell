#include "minishell.h"

/* =============================== */
/* ======== heimdall_red ========= */
/* =============================== */

// funcion buena
// Hay que revisar la funcion para crear su propia estructura
// y poder meter todas las variables que necesitemos
// Proximamente hay que recuperar en caso de que el comando falle la salida
// estandar para escribir el error y que no salga por el fd
// int ft_heimdall_redir(t_data **data, t_tree **ygg, char **env, int forked)
// {
// 	t_tree	*curr;
// 	t_tree	*file_node;
// 	t_tree	*cmd_node;
// 	int		fd_out;
// 	int		fd_in;
// 	int		tmp_fd;
// 	int		flags;
// 	// Variables para guardar el estado original
// 	int		stdin_backup;
// 	int		stdout_backup;
// 	int		status;

// 	cmd_node = (*ygg)->left;
// 	curr = *ygg;
// 	fd_out = -1;
// 	fd_in = -1;
// 	stdin_backup = -1;
// 	stdout_backup = -1;
// 	status = 0;

// 	// --- 1. SAVE: Guardamos STDIN y STDOUT originales si no es un fork ---
// 	// Si estamos en un hijo (forked=1), no hace falta porque el hijo muere.
// 	// Pero si es un builtin o shell principal, ES VITAL.
// 	if (!forked)
// 	{
// 		stdin_backup = dup(STDIN_FILENO);
// 		stdout_backup = dup(STDOUT_FILENO);
// 	}

// 	// --- 2. Bucle para abrir archivos (Igual que antes) ---
// 	while (curr && ft_is_red(curr->type))
// 	{
// 		if (curr->right && ft_is_red(curr->right->type))
// 			file_node = curr->right->left;
// 		else
// 			file_node = curr->right;

// 		if (curr->type == T_REDIR_IN)
// 		{
// 			tmp_fd = open(file_node->content[0], O_RDONLY);
// 			if (tmp_fd < 0)
// 			{
// 				// Si falla, hay que restaurar antes de salir si hicimos backups
// 				if (!forked)
// 				{
// 					close(stdin_backup);
// 					close(stdout_backup);
// 				}
// 				return (ft_pd_error(ERR_PERMISSION_DENIED, file_node->content[0], 1));
// 			}
// 			if (fd_in != -1)
// 				close(fd_in);
// 			fd_in = tmp_fd;
// 		}
// 		else
// 		{
// 			flags = O_CREAT | O_WRONLY;
// 			if (curr->type == T_REDIR_OUT)
// 				flags |= O_TRUNC;
// 			else
// 				flags |= O_APPEND;
// 			tmp_fd = open(file_node->content[0], flags, 0644);
// 			if (tmp_fd < 0)
// 			{
// 				if (!forked)
// 				{
// 					close(stdin_backup);
// 					close(stdout_backup);
// 				}
// 				return (ft_pd_error(ERR_PERMISSION_DENIED, file_node->content[0], 1));
// 			}
// 			if (fd_out != -1)
// 				close(fd_out);
// 			fd_out = tmp_fd;
// 		}
// 		if (curr->right && ft_is_red(curr->right->type))
// 			curr = curr->right;
// 		else
// 			break ;
// 	}

// 	// --- 3. Aplicar dup2 (Redirección activa) ---
// 	if (fd_in != -1)
// 	{
// 		dup2(fd_in, STDIN_FILENO);
// 		close(fd_in);
// 	}
// 	if (fd_out != -1)
// 	{
// 		dup2(fd_out, STDOUT_FILENO);
// 		close(fd_out);
// 	}

// 	// --- 4. Ejecutar el comando ---
// 	if (cmd_node)
// 		status = ft_heimdall(data, &cmd_node, env, forked);

// 	// --- 5. RESTORE: Volver a conectar teclado y pantalla ---
// 	if (!forked)
// 	{
// 		// Recuperamos la entrada estándar (teclado)
// 		if (stdin_backup != -1)
// 		{
// 			dup2(stdin_backup, STDIN_FILENO);
// 			close(stdin_backup);
// 		}
// 		// Recuperamos la salida estándar (pantalla)
// 		if (stdout_backup != -1)
// 		{
// 			dup2(stdout_backup, STDOUT_FILENO);
// 			close(stdout_backup);
// 		}
// 	}

// 	return (status);
// }

// 2
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

// 1
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

int	ft_init_red(t_red *red, t_tree **ygg, int forked)
{
	red->cmd_node = (*ygg)->left;
	red->curr = *ygg;
	red->file_node = NULL;
	red->fd_out = -1;
	red->fd_in = -1;
	if (!forked)
	{
		red->stdin_backup = dup(STDIN_FILENO);
		red->stdout_backup = dup(STDOUT_FILENO);
	}
	red->status = -1;
	red->tmp_fd = -1;
	red->flags = -1;
	return (0);
}

int	ft_case_in(t_red *red, int forked)
{
	red->tmp_fd = open(red->file_node->content[0], O_RDONLY);
	if (red->tmp_fd < 0)
	{
		if (!forked)
		{
			close(red->stdin_backup);
			close(red->stdout_backup);
		}
		return (1);
	}
	if (red->fd_in != -1)
		close(red->fd_in);
	red->fd_in = red->tmp_fd;
	return (0);
}

int	ft_case_out(t_red *red, int forked)
{
	red->flags = O_CREAT | O_WRONLY;
	if (red->curr->type == T_REDIR_OUT)
		red->flags |= O_TRUNC;
	else
		red->flags |= O_APPEND;
	red->tmp_fd = open(red->file_node->content[0], red->flags, 0644);
	if (red->tmp_fd < 0)
	{
		if (!forked)
		{
			close(red->stdin_backup);
			close(red->stdout_backup);
		}
		return (1);
	}
	if (red->fd_out != -1)
		close(red->fd_out);
	red->fd_out = red->tmp_fd;
	return (0);
}

void	ft_redir_aux(t_data **data, char **env, t_red *red, int forked)
{
	if (red->fd_in != -1)
	{
		dup2(red->fd_in, STDIN_FILENO);
		close(red->fd_in);
	}
	if (red->fd_out != -1)
	{
		dup2(red->fd_out, STDOUT_FILENO);
		close(red->fd_out);
	}
	if (red->cmd_node)
		red->status = ft_heimdall(data, &red->cmd_node, env, forked);
	if (!forked)
	{
		if (red->stdin_backup != -1)
		{
			dup2(red->stdin_backup, STDIN_FILENO);
			close(red->stdin_backup);
		}
		if (red->stdout_backup != -1)
		{
			dup2(red->stdout_backup, STDOUT_FILENO);
			close(red->stdout_backup);
		}
	}
}

int	ft_heimdall_redir(t_data **data, t_tree **ygg, char **env, int forked)
{
	t_red	red;

	ft_init_red(&red, ygg, forked);
	while (red.curr && ft_is_red(red.curr->type))
	{
		if (red.curr->right && ft_is_red(red.curr->right->type))
			red.file_node = red.curr->right->left;
		else
			red.file_node = red.curr->right;
		if (red.curr->type == T_REDIR_IN)
		{
			if (ft_case_in(&red, forked))
				return (ft_pd_error(NO_FILE_DIR, red.file_node->content[0], 1));
		}
		else
			if (ft_case_out(&red, forked))
				return (ft_pd_error(NO_FILE_DIR, red.file_node->content[0], 1));
		if (red.curr->right && ft_is_red(red.curr->right->type))
			red.curr = red.curr->right;
		else
			break ;
	}
	ft_redir_aux(data, env, &red, forked);
	return (red.status);
}

// FUNCION ANTES DE SEPARAR
// int ft_heimdall_redir(t_data **data, t_tree **ygg, char **env, int forked)
// {
// 	t_red	red;
// 	// t_tree	*curr;
// 	// t_tree	*file_node;
// 	// t_tree	*cmd_node;
// 	// int		fd_out;
// 	// int		fd_in;
// 	// int		tmp_fd;
// 	// int		flags;
// 	// // Variables para guardar el estado original
// 	// int		stdin_backup;
// 	// int		stdout_backup;
// 	// int		status;

// 	// cmd_node = (*ygg)->left;
// 	// curr = *ygg;
// 	// fd_out = -1;
// 	// fd_in = -1;
// 	// stdin_backup = -1;
// 	// stdout_backup = -1;
// 	// status = 0;

// 	ft_init_red(&red, ygg, forked);
// 	// --- 1. SAVE: Guardamos STDIN y STDOUT originales si no es un fork ---
// 	// Si estamos en un hijo (forked=1), no hace falta porque el hijo muere.
// 	// Pero si es un builtin o shell principal, ES VITAL.
// 	// if (!forked)
// 	// {
// 	// 	stdin_backup = dup(STDIN_FILENO);
// 	// 	stdout_backup = dup(STDOUT_FILENO);
// 	// }
// 	// --- 2. Bucle para abrir archivos (Igual que antes) ---
// 	while (red.curr && ft_is_red(red.curr->type))
// 	{
// 		if (red.curr->right && ft_is_red(red.curr->right->type))
// 			red.file_node = red.curr->right->left;
// 		else
// 			red.file_node = red.curr->right;

// 		if (red.curr->type == T_REDIR_IN)
// 		{
// 			red.tmp_fd = open(red.file_node->content[0], O_RDONLY);
// 			if (red.tmp_fd < 0)
// 			{
// 				// Si falla, hay que restaurar antes de salir si hicimos backups
// 				if (!forked)
// 				{
// 					close(red.stdin_backup);
// 					close(red.stdout_backup);
// 				}
// 				return (ft_pd_error(ERR_PERMISSION_DENIED, red.file_node->content[0], 1));
// 			}
// 			if (red.fd_in != -1)
// 				close(red.fd_in);
// 			red.fd_in = red.tmp_fd;
// 		}
// 		else
// 		{
// 			red.flags = O_CREAT | O_WRONLY;
// 			if (red.curr->type == T_REDIR_OUT)
// 				red.flags |= O_TRUNC;
// 			else
// 				red.flags |= O_APPEND;
// 			red.tmp_fd = open(red.file_node->content[0], red.flags, 0644);
// 			if (red.tmp_fd < 0)
// 			{
// 				if (!forked)
// 				{
// 					close(red.stdin_backup);
// 					close(red.stdout_backup);
// 				}
// 				return (ft_pd_error(ERR_PERMISSION_DENIED, red.file_node->content[0], 1));
// 			}
// 			if (red.fd_out != -1)
// 				close(red.fd_out);
// 			red.fd_out = red.tmp_fd;
// 		}
// 		if (red.curr->right && ft_is_red(red.curr->right->type))
// 			red.curr = red.curr->right;
// 		else
// 			break ;
// 	}

// 	// --- 3. Aplicar dup2 (Redirección activa) ---
// 	if (red.fd_in != -1)
// 	{
// 		dup2(red.fd_in, STDIN_FILENO);
// 		close(red.fd_in);
// 	}
// 	if (red.fd_out != -1)
// 	{
// 		dup2(red.fd_out, STDOUT_FILENO);
// 		close(red.fd_out);
// 	}

// 	// --- 4. Ejecutar el comando ---
// 	if (red.cmd_node)
// 		red.status = ft_heimdall(data, &red.cmd_node, env, forked);

// 	// --- 5. RESTORE: Volver a conectar teclado y pantalla ---
// 	if (!forked)
// 	{
// 		// Recuperamos la entrada estándar (teclado)
// 		if (red.stdin_backup != -1)
// 		{
// 			dup2(red.stdin_backup, STDIN_FILENO);
// 			close(red.stdin_backup);
// 		}
// 		// Recuperamos la salida estándar (pantalla)
// 		if (red.stdout_backup != -1)
// 		{
// 			dup2(red.stdout_backup, STDOUT_FILENO);
// 			close(red.stdout_backup);
// 		}
// 	}

// 	return (red.status);
// }
