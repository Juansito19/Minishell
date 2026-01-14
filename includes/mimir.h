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

int		ft_append_val(char **res, char *str, int i, t_data **data);
void	ft_flags_state(char s, int *state);
int		ft_expand_var(t_token **token, t_data **data);
char	*ft_process_new_expansion(char *str, t_data **data);
int		ft_mimir(t_token **token, t_data **data);

/* ================================= */

/* ================================= */
/* ========== mimir utils ========== */
/* ================================= */

void	ft_need_to_expand(t_token **token);
void	ft_aux_need_to_expand(t_token **tkn, int state);
void	ft_add_char(char **s, char c);
void	ft_add_str(char **s, char *add);

/* ================================= */

#endif