#ifndef MIMIR_H
# define MIMIR_H

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

typedef struct s_token	t_token;

/* ================================= */
/* ============= mimir ============= */
/* ================================= */

int			ft_expand_var(t_token **token, char **env, int exit_status);
int			ft_mimir(t_token **token, char **env, int exit_status);
int			ft_process_var(t_expand **exp, char **env, int exit, char *cont);
int			ft_rebuild_var(t_expand **exp);
int			ft_domain_expansion(t_expand **exp, int i, char **env, int exit);

/* ================================= */

/* ================================= */
/* ========== mimir utils ========== */
/* ================================= */

t_expand	*ft_init_expanders(void);
int			ft_found_var(t_expand **exp, t_token **token);
int			ft_no_found_var(t_expand **exp, t_token **token);
int			ft_handle_end_quote(t_expand **exp, char *content);
int			ft_handle_init_quote(t_expand **exp, char *content);

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