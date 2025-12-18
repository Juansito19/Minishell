#ifndef TOKEN_TREE_H
# define TOKEN_TREE_H
# include "./minishell.h"

/**
 * @brief Variable expansion state tracker (Mimir's wisdom).
 * 
 * Holds temporary data during environment variable expansion process.
 * Tracks quotes, variable names, and positions to properly expand $VAR
 * tokens while respecting quote contexts. Named after Mimir, the Norse
 * god of knowledge, as it reveals hidden values from the environment.
 */
typedef struct s_expand
{
	char	*init_quote;	/* Text before $ (prefix) */
	char	*end_quote;		/* Text after variable (suffix) */
	char	**split;		/* Split result by $ delimiter */
	char	*var;			/* Variable name to expand */
	char	*tmp_var;		/* Expanded value from environment */
	char	*aux;			/* Auxiliary string for concatenation */
	int		s_init;			/* Start position of variable */
	int		s_end;			/* End position of variable */
	int		limit;			/* Boundary limit for parsing */
	int		dollar;			/* Dollar sign position tracker */
	int		expand;			/* Expansion flag: [0]no, [1]yes */
}	t_expand;

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
/* ========= mimir expander ======== */
/* ================================= */

int			ft_find_limit(t_expand **exp, char *s, int i);
int			ft_expander_validator(t_expand **exp, int i, int size);
void		ft_variable_search(t_expand **exp, char **env, int i, int exit);
void		ft_need_to_expand(t_token **token);
void		ft_aux_need_to_expand(t_token **tkn, int state);

/* ================================= */

/* ================================= */
/* ========== split utils ========== */
/* ================================= */

char		**ft_split_dollar(char const *s, char c);

/* ================================= */

#endif
