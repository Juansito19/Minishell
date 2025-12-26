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
# define ERR_NO_SUCH_FILE "minishell: %s: No such file or directory\n"
# define ERR_PERMISSION_DENIED "minishell: %s: Permission denied\n"
# define ERR_IS_DIRECTORY "minishell: %s: Is a directory\n"
# define ERR_NOT_DIRECTORY "minishell: %s: Not a directory\n"
# define ERR_VAR_NOTFOUND "minishell: %s variable not found in environment\n"

# define ERR_CD_TOO_MANY_ARGS "minishell: cd: too many arguments\n"
# define ERR_CD_NO_HOME "minishell: cd: HOME not set\n"
# define ERR_CD_NO_SUCH_FILE "minishell: cd: %s: No such file or directory\n"
# define ERR_EXPORT_INVALID "minishell : export: `%s': not a valid identifier\n"
# define ERR_UNSET_INVALID "minishell : unset: `%s': not a valid identifier\n"
# define ERR_EXIT_NUMERIC "minishell: exit: %s: numeric argument required\n"
# define ERR_EXIT_TOO_MANY "minishell: exit: too many arguments\n"

# define ERR_SIGNAL "minishell: signal: signal %s fail\n"

/* ============================ */
/* ========== error =========== */
/* ============================ */

int			ft_print_error(int error_code, char *s);
int			ft_pd_error(char *format, char *s, int error_code);

/* ============================ */

#endif