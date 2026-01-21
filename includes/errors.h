/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrosio <jbrosio@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 19:04:37 by jbrosio           #+#    #+#             */
/*   Updated: 2026/01/15 19:15:01 by jbrosio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# define ERR_SYNTAX "minishell: syntax error\n"
# define ERR_UNEXPECTED_TOKEN "minishell: syntax error\
near unexpected token `%s'\n"
# define ERR_UNCLOSED_QUOTE "minishell: unexpected EOF\
while looking for matching `%c'\n"
# define ERR_NEWLINE "minishell: syntax error near unexpected token `newline'\n"

# define ERR_PIPE_FAILED "minishell: pipe: pipe failed\n"
# define ERR_FORK_FAILED "minishell: fork: fork failed\n"

# define ERR_MALLOC "minishell: malloc: memory allocation failed\n"
# define ERR_EXECVE "minishell: execve: execve failed\n"

# define ERR_CMD_NOT_FOUND "minishell: %s: command not found\n"
# define NO_FILE_DIR "minishell: %s: No such file or directory\n"
# define PER_DENIED "minishell: %s: Permission denied\n"
# define ERR_IS_DIRECTORY "minishell: %s: Is a directory\n"
# define ERR_NOT_DIRECTORY "minishell: %s: Not a directory\n"
# define ERR_VAR_NOTFOUND "minishell: %s variable not found in environment\n"
# define ERR_TOO_MANY_ARGS "minishell: %s: too many arguments\n"

# define ERR_RATA "minishell: ratatosker: open fail\n"

# define ERR_CD_TOO_MANY_ARGS "minishell: cd: too many arguments\n"
# define ERR_CD_NO_DIR "minishell: cd: not a directory\n"
# define ERR_CD_NO_HOME "minishell: cd: HOME not set\n"
# define ERR_CD_NO_OLDPWD "minishell: cd: OLDPWD not set\n"
# define ERR_CD_NO_SUCH_FILE "minishell: cd: %s: No such file or directory\n"
# define ERR_CD_STAT "minishell: cd: : Error accessing file info\n"
# define ERR_EXPORT_INVALID "minishell: export: `%s': not a valid identifier\n"
# define ERR_UNSET_INVALID "minishell: unset: `%s': not a valid identifier\n"
# define ERR_EXIT_NUMERIC "minishell: exit: %s: numeric argument required\n"
# define ERR_EXIT_TOO_MANY "minishell: exit: too many arguments\n"

# define ERR_HEREDOC_CTRLD "minishell: warning: here-document delimited \
by end-of-file (wanted `%s')\n"

# define ERR_SIGNAL "minishell: signal: signal %s fail\n"

# define ERR_PWD "pwd: getcwd: cannot access parent directories\n"

/* ============================ */
/* ========== error =========== */
/* ============================ */

/**
 * @brief Prints appropriate error message for cd command.
 * @param path Path that caused the error.
 * @return Always returns 1 (error code).
 */
int	ft_print_cd_error(char *path);

/**
 * @brief Prints error message with optional system error.
 * @param error_code System error code (0 for none).
 * @param s Custom error message string.
 * @return Always returns 1 (error code).
 */
int	ft_print_error(int error_code, char *s);

/**
 * @brief Prints formatted error message to stderr.
 * @param format Format string for error message.
 * @param s String to include in formatted message.
 * @param error_code Error code to return.
 * @return The provided error_code value.
 */
int	ft_pd_error(char *format, char *s, int error_code);

/* ============================ */

#endif