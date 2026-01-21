#ifndef HEIMDALL_H
# define HEIMDALL_H

typedef struct s_tree	t_tree;
typedef struct s_data	t_data;

/**
 * @brief Redirection handler state structure.
 * 
 * Maintains state information for processing I/O redirections in commands.
 * Tracks file descriptors, tree nodes, and backup streams to properly
 * handle input/output redirections (<, >, <<, >>).
 */
typedef struct s_red
{
	t_tree	*curr;			/* Current redirection node being processed */
	t_tree	*file_node;		/* Node containing target file name */
	t_tree	*cmd_node;		/* Command node to execute after redirection */
	int		fd_out;			/* Output file descriptor for redirection */
	int		fd_in;			/* Input file descriptor for redirection */
	int		tmp_fd;			/* Temporary file descriptor during setup */
	int		flags;			/* Open flags for file operations */
	int		stdin_backup;	/* Backup of original stdin for restoration */
	int		stdout_backup;	/* Backup of original stdout for restoration */
	int		status;			/* Exit status of redirected command */
}	t_red;

/* ============================== */
/* ========== heimdall ========== */
/* ============================== */

/**
 * @brief Searches for command in PATH directories.
 * @param ygg Pointer to command tree node.
 * @param tmp_dir Temporary directory path string.
 * @return 0 on success, error code otherwise.
 */
int		ft_bifrost(t_tree **ygg, char *tmp_dir);

/**
 * @brief Searches command in a specific PATH directory.
 * @param ygg Pointer to command tree node.
 * @param tmp_dir Pointer to temporary directory path.
 * @param path_dir Pointer to PATH directory to search.
 * @return 0 if found, 1 if not found, -1 on error.
 */
int		ft_search_path(t_tree **ygg, char **tmp_dir, char **path_dir);

/**
 * @brief Assigns found path to command in tree node.
 * @param ygg Pointer to command tree node.
 * @param tmp_dir Pointer to temporary directory path.
 * @param path_dir Pointer to array of PATH directories.
 * @param i Pointer to current directory index.
 * @return 0 on success, error code otherwise.
 */
int		ft_assign_path(t_tree **ygg, char **tmp_dir, char ***path_dir, int *i);

/**
 * @brief Main execution dispatcher for commands.
 * @param data Pointer to shell data structure.
 * @param ygg Pointer to command tree node.
 * @param env Environment variables array.
 * @param forked Flag indicating if running in forked process.
 * @return Exit status code of executed command.
 */
int		ft_heimdall(t_data **data, t_tree **ygg, char **env, int forked);

/* ============================== */

/* ================================ */
/* ======== heimdall_cmd ========== */
/* ================================ */

/**
 * @brief Handles execution of command nodes.
 * @param data Pointer to shell data structure.
 * @param ygg Pointer to command tree node.
 * @param env Environment variables array.
 * @param forked Flag indicating if running in forked process.
 * @return 0 on success, error code otherwise.
 */
int		ft_heimdall_cmd(t_data **data, t_tree **ygg, char **env, int forked);

/**
 * @brief Handles builtin command execution.
 * @param data Pointer to shell data structure.
 * @param av Command arguments array.
 * @param forked Flag indicating if running in forked process.
 * @return Exit status of builtin command.
 */
int		ft_handle_builtin(t_data **data, char **av, int forked);

/**
 * @brief Handles command not found errors.
 * @param data Pointer to shell data structure.
 * @param forked Flag indicating if running in forked process.
 * @return Always returns 127 (command not found).
 */
int		ft_handle_bifrost_error(t_data **data, int forked);

/**
 * @brief Executes command in child process.
 * @param data Pointer to shell data structure.
 * @param av Command arguments array.
 * @param env Environment variables array.
 */
void	ft_exec_child(t_data **data, char **av, char **env);

/**
 * @brief Forks and executes command in parent process.
 * @param data Pointer to shell data structure.
 * @param ygg Pointer to command tree node.
 * @param av Command arguments array.
 * @param env Environment variables array.
 * @return Exit status of child process.
 */
int		ft_exec_parent(t_data **data, t_tree **ygg, char **av, char **env);

/* ================================ */

/* ================================ */
/* ======== heimdall_red ========== */
/* ================================ */

/**
 * @brief Handles I/O redirection execution.
 * @param data Pointer to shell data structure.
 * @param ygg Pointer to redirection tree node.
 * @param env Environment variables array.
 * @param forked Flag indicating if running in forked process.
 * @return 0 on success, error code otherwise.
 */
int		ft_heimdall_redir(t_data **data, t_tree **ygg, char **env, int forked);

/**
 * @brief Applies redirections and executes command.
 * @param data Pointer to shell data structure.
 * @param env Environment variables array.
 * @param red Pointer to redirection state structure.
 * @param forked Flag indicating if running in forked process.
 */
void	ft_redir_aux(t_data **data, char **env, t_red *red, int forked);

/**
 * @brief Initializes redirection state structure.
 * @param red Pointer to redirection state structure.
 * @param ygg Pointer to redirection tree node.
 * @param forked Flag indicating if running in forked process.
 * @return Always returns 0.
 */
int		ft_init_red(t_red *red, t_tree **ygg, int forked);

/**
 * @brief Handles input redirection case.
 * @param red Pointer to redirection state structure.
 * @param forked Flag indicating if running in forked process.
 * @return 0 on success, 1 on error.
 */
int		ft_case_in(t_red *red, int forked);

/**
 * @brief Handles output redirection case.
 * @param red Pointer to redirection state structure.
 * @param forked Flag indicating if running in forked process.
 * @return 0 on success, 1 on error.
 */
int		ft_case_out(t_red *red, int forked);

/* ================================ */

/* ================================ */
/* ======== heimdall_pipe ========= */
/* ================================ */

/**
 * @brief Executes left side of pipe in child process.
 * @param data Pointer to shell data structure.
 * @param ygg Pointer to pipe tree node.
 * @param env Environment variables array.
 * @param forked Flag indicating if running in forked process.
 */
void	ft_left_child(t_data **data, t_tree **ygg, char **env, int forked);

/**
 * @brief Executes right side of pipe in child process.
 * @param data Pointer to shell data structure.
 * @param ygg Pointer to pipe tree node.
 * @param env Environment variables array.
 * @param forked Flag indicating if running in forked process.
 */
void	ft_right_child(t_data **data, t_tree **ygg, char **env, int forked);

/**
 * @brief Forks and sets up left side of pipe.
 * @param data Pointer to shell data structure.
 * @param ygg Pointer to pipe tree node.
 * @param env Environment variables array.
 * @param forked Flag indicating if running in forked process.
 * @return PID of forked child process.
 */
int		ft_left_process(t_data **data, t_tree **ygg, char **env, int forked);

/**
 * @brief Forks and sets up right side of pipe.
 * @param data Pointer to shell data structure.
 * @param ygg Pointer to pipe tree node.
 * @param env Environment variables array.
 * @param forked Flag indicating if running in forked process.
 * @return PID of forked child process.
 */
int		ft_right_process(t_data **data, t_tree **ygg, char **env, int forked);

/**
 * @brief Handles pipe execution between two commands.
 * @param data Pointer to shell data structure.
 * @param ygg Pointer to pipe tree node.
 * @param env Environment variables array.
 * @param forked Flag indicating if running in forked process.
 * @return Exit status of right side command.
 */
int		ft_heimdall_pipe(t_data **data, t_tree **ygg, char **env, int forked);

/* ================================ */

#endif