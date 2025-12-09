#ifndef PARSE_H
# define PARSE_H

/* ============================ */
/* ========== parse =========== */
/* ============================ */

int			ft_open_quote(char *input);
int			ft_pipe_check(char *s);
int			ft_redir_check(char *s);
int			ft_big_prick_parse(char *input);

/* ============================ */

/* ============================ */
/* ====== parse_utils_1 ======= */
/* ============================ */

int			ft_redir_bucle_check(char *s, char quote);
char		ft_quote_track(char c, char quote);
void		ft_real_quote(t_token **token);

/* ============================ */

#endif
