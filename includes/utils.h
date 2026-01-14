#ifndef UTILS_H
# define UTILS_H
# include "minishell.h"

typedef enum s_type		t_type;
typedef struct s_token	t_token;
typedef struct s_tree	t_tree;
typedef struct s_data	t_data;
typedef struct s_expand	t_expand;

/* ============================ */
/* ========== utils =========== */
/* ============================ */

int		ft_find_path(t_tree **tree, char **envp);
int		*ft_get_times_ptr(int reset);
void	ft_reset_heredoc_times(void);

/* ============================ */

/* ============================ */
/* ====== type_validator ====== */
/* ============================ */

int		ft_is_metachar(char c);
t_type	ft_is_builtin(t_token **token);
t_type	ft_is_red(t_type type);
t_type	ft_take_meta(char *content);
t_type	ft_is_quote(char c);

/* ============================ */

/* ============================ */
/* ========== clean =========== */
/* ============================ */

void	ft_clean_yggdrasil(t_tree **tree);
void	ft_free_tokens(t_token **head);
void	ft_clean_data(t_data **data);
void	*ft_free_all(t_tree **tree, t_token **token, char **input, char ***s);

/* ============================ */

#endif
