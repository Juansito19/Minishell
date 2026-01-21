#ifndef RATATOSKR_H
# define RATATOSKR_H

/* =============================== */
/* ========== ratatoskr ========== */
/* =============================== */

/**
 * @brief Finds and marks EOF delimiter tokens in heredoc sequence.
 * @param token Pointer to token list head.
 * @param eof Pointer to store found EOF token.
 * @note Recursively searches for T_EOF type token.
 */
void	ft_find_branch_eof(t_token **token, t_token **eof);

/**
 * @brief Converts heredoc tokens to input redirection with temp file.
 * @param tmp_name Pointer to temporary filename (will be freed).
 * @param eof Pointer to EOF delimiter token.
 * @param token Pointer to heredoc token.
 * @return Always returns 0.
 * @note Changes T_HEREDOC to T_REDIR_IN, T_EOF to T_FD.
 */
int		ft_new_content(char **tmp_name, t_token **eof, t_token **token);

/**
 * @brief Reads heredoc input until delimiter and writes to temp file.
 * @param token Pointer to heredoc token.
 * @param tmp_name Pointer to temporary filename.
 * @param fd File descriptor of temporary file.
 * @param eof Pointer to EOF delimiter token.
 * @return 130 if interrupted by SIGINT, 0 otherwise.
 * @note Handles Ctrl+C (g_status 130) and Ctrl+D interruptions.
 */
int		ft_chg_b(t_token **token, char **tmp_name, int fd, t_token **eof);

/**
 * @brief Main heredoc handler, processes all heredocs in token list.
 * @param token Pointer to token list head.
 * @return 0 on success, 1 on error.
 * @note Creates temp files, sets up signals, processes recursively.
 */
int		ft_ratatoskr(t_token **token);

/**
 * @brief Marks tokens following T_HEREDOC as T_EOF delimiters.
 * @param token Pointer to token list head.
 * @note Traverses entire token list sequentially.
 */
void	ft_search_eof(t_token **token);

/* =============================== */

/* =============================== */
/* ====== ratatoskr_utils ======== */
/* =============================== */

/**
 * @brief Frees two string pointers safely.
 * @param number First string to free.
 * @param tmp Second string to free.
 * @return Always returns NULL.
 */
void	*ft_free_pointers(char *number, char *tmp);

/**
 * @brief Generates unique temporary filename for heredoc.
 * @return Allocated string with format ".heredoc_N", NULL on error.
 * @note Uses static counter to ensure uniqueness.
 */
char	*ft_make_unic_name(void);

/**
 * @brief Recursively deletes all heredoc temporary files in tree.
 * @param yggdrasil Pointer to execution tree root.
 * @return 0 on success, 1 if unlink fails.
 * @note Only removes files marked with T_FD type.
 */
int		ft_files_destroyer(t_tree **yggdrasil);

/**
 * @brief Handles heredoc interruption cleanup and restoration.
 * @param tmp_name Pointer to delimiter string (freed internally).
 * @param fd File descriptor of temporary file.
 * @param fd_back Backup file descriptor for STDIN.
 * @return 130 if SIGINT (Ctrl+C), 0 if Ctrl+D.
 * @note Restores STDIN, closes fds, manages newline printing.
 */
int		ft_signal_break(char **tmp_name, int fd, int fd_back);

/* =============================== */

#endif
