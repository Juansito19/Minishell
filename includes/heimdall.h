#ifndef HEIMDALL_H
# define HEIMDALL_H

typedef struct s_tree	t_tree;
typedef struct s_data	t_data;

/* ============================== */
/* ========== heimdall ========== */
/* ============================== */

int	ft_bifrost(t_tree **ygg, char **av);
int	ft_haimdall_cmd(t_data **data, t_tree **ygg, char **env, int forked);
int	ft_haimdall_redir(t_data **data, t_tree **ygg, char **env, int forked);
int	ft_haimdall_pipe(t_data **data, t_tree **ygg, char **env, int forked);
int	ft_haimdall(t_data **data, t_tree **ygg, char **env, int forked);

/* ============================== */

#endif
