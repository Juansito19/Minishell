#ifndef HEIMDALL_H
# define HEIMDALL_H

typedef struct s_tree	t_tree;
typedef struct s_data	t_data;

/* ============================== */
/* ========== heimdall ========== */
/* ============================== */

int	ft_bifrost(t_tree **ygg);
int	ft_search_path(t_tree **ygg, char **tmp_dir, char **path_dir);
int	ft_assign_path(t_tree **ygg, char **tmp_dir, char ***path_dir, int *i);
int	ft_heimdall_cmd(t_data **data, t_tree **ygg, char **env, int forked);
int	ft_heimdall_redir(t_data **data, t_tree **ygg, char **env, int forked);
int	ft_heimdall_pipe(t_data **data, t_tree **ygg, char **env, int forked);
int	ft_heimdall(t_data **data, t_tree **ygg, char **env, int forked);

/* ============================== */

#endif
