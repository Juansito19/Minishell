#ifndef UTILS_H
# define UTILS_H
# include "minishell.h"

typedef enum s_type		t_type;
typedef struct s_token	t_token;
typedef struct s_tree	t_tree;
typedef struct s_data	t_data;

/* ============================ */
/* ========== utils =========== */
/* ============================ */

int		ft_find_path(t_data **data, char **envp);

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
int		ft_clean_expanders(t_expand **expander);

/* ============================ */

/* ============================ */
/* ========== print =========== */
/* ============================ */

void	print_token(t_token **token);
void	ft_write_type_branch(t_type type);
void	print_tree(t_tree **tree);
void	print_tree_recursive(t_tree *tree, int depth, char *prefix);
void	fprint_tree(t_tree **tree);

/* ============================ */

#endif
