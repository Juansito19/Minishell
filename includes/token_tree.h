#ifndef TOKEN_TREE_H
# define TOKEN_TREE_H
# include "./minishell.h"

typedef struct s_expand
{
	char	*init_quote;
	char	*end_quote;
	char	**split;
	char	*var;
	char	*tmp_var;
	char	*aux;
	int		s_init;
	int		s_end;
	int		limit;
	int		dollar;
	int		expand;
}	t_expand;

typedef struct s_ex_var
{
	char			*content;
	int				expand;
	struct s_ex_var	*next;
}	t_exp_var;

typedef enum s_type		t_type;
typedef struct s_token	t_token;
typedef struct s_tree	t_tree;
typedef struct s_data	t_data;

/* ================================= */
/* ============tokens=============== */
/* ================================= */

t_token		*ft_token(char *s, int i);
int			ft_token_word(t_token **tokens, char *s, int *ind);
int			ft_token_meta(t_token **tokens, char *s, int *ind, t_type type);

// ================================= //

/* ================================= */
/* ========= tokens utils ========== */
/* ================================= */

t_token		*ft_token_init(void *content, t_type type);
void		ft_tokenadd_back(t_token **tokens, t_token *new);
int			ft_tk_size(t_token *lst);

// ================================= //

/* ================================= */
/* ======== search_quotes ========== */
/* ================================= */

void		ft_search_quotes(t_token **token);
void		ft_put_word(char *s, char **word, int i, int *state);
int			ft_token_word_size(char *s, int i, int count, int state);
int			ft_token_clean_word(t_token **token);

// ================================= //

/* ================================= */
/* ========== yggdrasil ============ */
/* ================================= */

t_token		*ft_put_all_left(t_token **tokens, t_token *token_pipe);
t_token		*ft_put_all_right(t_token **tokens);
char		**ft_fill_word_type(t_token *token, int size);
int			ft_yggdrasil(t_token **tokens, t_tree **tree, t_data **data);

// ================================= //

/* ================================= */
/* ======= yggdrasil branch ======== */
/* ================================= */

int			ft_branch_m(t_token *meta, t_tree **tree,
				t_token **tokens, t_data **data);
int			ft_branch_w(t_tree **tree, t_token **tokens, char *path);

// ================================= //

/* ================================= */
/* ======== yggdrasil utils ======== */
/* ================================= */

t_tree		*ft_tree_init(char **content, t_type type, char *path);
t_token		*ft_search_pipe(t_token **tokens);
t_token		*ft_search_red(t_token **tokens);
void		ft_treeadd_right(t_tree **tree, t_tree *new);
void		ft_treeadd_left(t_tree **tree, t_tree *new);

// ================================= //

/* ================================= */
/* ============= mimir ============= */
/* ================================= */

void		ft_aux_need_to_expand(t_token **tkn, int state);
void		ft_need_to_expand(t_token **token);
int			ft_expand_var(t_token **token, char **env, int exit_status);
int			ft_mimir(t_token **token, char **env, int exit_status);
int			ft_process_var(t_expand **exp, char **env, int exit, char *cont);

/* ================================= */

/* ================================= */
/* ========== mimir utils ========== */
/* ================================= */

t_expand	*ft_init_expanders(void);
int			ft_found_var(t_expand **exp, t_token **token);
int			ft_no_found_var(t_expand **exp, t_token **token);
int			ft_handle_end_quote(t_expand **exp, char *content);
int			ft_handle_init_quote(t_expand **exp, char *content);
int			ft_process_var_aux(t_expand **exp, char **env, int exit);

/* ================================= */

/* ================================= */
/* ========== split utils ========== */
/* ================================= */

char		**ft_split_dollar(char const *s, char c);

/* ================================= */

#endif
