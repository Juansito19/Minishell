#ifndef RATATOSKR_H
# define RATATOSKR_H

/* ========== ratatoskr ========== */

void	ft_search_eof(t_token **token);
char	*ft_make_unic_name(void);
void	ft_find_branch_eof(t_tree **yggdrasil, t_tree **eof);
int		ft_ratatoskr(t_tree **yggdrasil);


#endif
