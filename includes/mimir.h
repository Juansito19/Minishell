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

/**
 * @brief Appends expanded variable value to result string.
 * @param res Pointer to result string being built.
 * @param str Source string containing variable reference.
 * @param i Current position in source string.
 * @param data Pointer to shell data structure.
 * @return New position in string after variable.
 */
int		ft_append_val(char **res, char *str, int i, t_data **data);

/**
 * @brief Updates quote state during string parsing.
 * @param s Character being processed.
 * @param state Pointer to current quote state.
 */
void	ft_flags_state(char s, int *state);

/**
 * @brief Expands environment variables in token content.
 * @param token Pointer to token to expand.
 * @param data Pointer to shell data structure.
 * @return 0 on success, error code otherwise.
 */
int		ft_expand_var(t_token **token, t_data **data);

/**
 * @brief Processes string and expands all variables.
 * @param str String containing variables to expand.
 * @param data Pointer to shell data structure.
 * @return New string with expanded variables, or NULL on error.
 */
char	*ft_process_new_expansion(char *str, t_data **data);

/**
 * @brief Main variable expansion controller for token list.
 * @param token Pointer to token list to process.
 * @param data Pointer to shell data structure.
 * @return 0 on success, error code otherwise.
 */
int		ft_mimir(t_token **token, t_data **data);

/* ================================= */

/* ================================= */
/* ========== mimir utils ========== */
/* ================================= */

/**
 * @brief Marks tokens that need variable expansion.
 * @param token Pointer to token list to analyze.
 */
void	ft_need_to_expand(t_token **token);

/**
 * @brief Helper to check if token needs expansion.
 * @param tkn Pointer to token being checked.
 * @param state Current quote state.
 */
void	ft_aux_need_to_expand(t_token **tkn, int state);

/**
 * @brief Appends a single character to string.
 * @param s Pointer to target string.
 * @param c Character to append.
 */
void	ft_add_char(char **s, char c);

/**
 * @brief Appends a string to another string.
 * @param s Pointer to target string.
 * @param add String to append (will be freed).
 */
void	ft_add_str(char **s, char *add);

/* ================================= */
#endif