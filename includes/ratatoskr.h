#ifndef RATATOSKR_H
# define RATATOSKR_H

/* =============================== */
/* ========== ratatoskr ========== */
/* =============================== */

void	ft_find_branch_eof(t_token **token, t_token **eof);
int		ft_new_content(char **tmp_name, t_token **eof, t_token **token);
int		ft_chg_b(t_token **token, char **tmp_name, int fd, t_token **eof);
int		ft_ratatoskr(t_token **token);
void	ft_search_eof(t_token **token);

/* =============================== */

/* =============================== */
/* ====== ratatoskr_utils ======== */
/* =============================== */

void	*ft_free_pointers(char *number, char *tmp);
char	*ft_make_unic_name(void);
int		ft_files_destroyer(t_tree **yggdrasil);
int		ft_signal_break(char **tmp_name, int fd, int fd_back, t_token **eof);

/* =============================== */

#endif
