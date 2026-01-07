#ifndef HEIMDALL_H
# define HEIMDALL_H

typedef struct s_tree	t_tree;
typedef struct s_data	t_data;

/* ============================== */
/* ========== heimdall ========== */
/* ============================== */

typedef struct s_red
{
	t_tree	*curr;
	t_tree	*file_node;
	t_tree	*cmd_node;
	int		fd_out;
	int		fd_in;
	int		tmp_fd;
	int		flags;
	int		stdin_backup;
	int		stdout_backup;
	int		status;
}	t_red;

int		ft_bifrost(t_tree **ygg);
int		ft_search_path(t_tree **ygg, char **tmp_dir, char **path_dir);
int		ft_assign_path(t_tree **ygg, char **tmp_dir, char ***path_dir, int *i);
int		ft_heimdall_cmd(t_data **data, t_tree **ygg, char **env, int forked);
int		ft_heimdall_redir(t_data **data, t_tree **ygg, char **env, int forked);
int		ft_init_red(t_red *red, t_tree **ygg, int forked);
int		ft_case_in(t_red *red, int forked);
int		ft_case_out(t_red *red, int forked);
void	ft_redir_aux(t_data **data, char **env, t_red *red, int forked);
int		ft_heimdall_pipe(t_data **data, t_tree **ygg, char **env, int forked);
int		ft_left_pid(int status, t_tree **ygg, t_data **data, int *forked);
int		ft_right_pid(int status, t_tree **ygg, t_data **data, int *forked);
int		ft_heimdall(t_data **data, t_tree **ygg, char **env, int forked);

/* ============================== */

#endif
