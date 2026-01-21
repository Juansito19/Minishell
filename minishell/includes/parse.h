#ifndef PARSE_H
# define PARSE_H

/* ============================ */
/* ========== parse =========== */
/* ============================ */

/**
 * @brief Checks if string has unclosed quotes.
 * @param input String to check for quote matching.
 * @return 1 if unclosed quote found, 0 if all quotes are closed.
 * @note Handles both single (') and double (") quotes.
 */
int			ft_open_quote(char *input);

/**
 * @brief Validates pipe syntax in string.
 * @param s String to check for pipe errors.
 * @return 1 if syntax error found, 0 if valid.
 * @note Detects: pipe at start, consecutive pipes, or pipe at end.
 */
int			ft_pipe_check(char *s);

/**
 * @brief Validates redirection syntax in string.
 * @param s String to check for redirection errors.
 * @return 1 if syntax error found, 0 if valid.
 * @note Detects: single '<' at start, or invalid redirection patterns.
 */
int			ft_redir_check(char *s);

/**
 * @brief Main parsing validation for shell input.
 * @param input User input string to validate.
 * @return 1 if syntax error found, 0 if valid.
 * @note Checks for: unclosed quotes, invalid pipes, invalid redirections.
 */
int			ft_big_prick_parse(char *input);

/* ============================ */

/* ============================ */
/* ======= parse_utils ======== */
/* ============================ */

/**
 * @brief Checks for invalid redirection syntax in string.
 * @param s String to check for redirection errors.
 * @param quote Initial quote state (typically 0).
 * @return 1 if syntax error found, 0 if valid.
 * @note Detects: consecutive redirections, redirections followed by
 *       pipe/nothing, or invalid token after redirection.
 */
int			ft_redir_bucle_check(char *s, char quote);

/**
 * @brief Tracks quote state while parsing a character.
 * @param c Current character to check.
 * @param quote Current quote state (0, '\'', or '"').
 * @return Updated quote state after processing the character.
 * @note Opens quote if c is quote and not in quote. Closes if matches.
 */
char		ft_quote_track(char c, char quote);
void		ft_real_quote(t_token **token);

/* ============================ */

#endif
