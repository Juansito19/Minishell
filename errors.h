#ifndef ERRORS_H
# define ERRORS_H

# define ERR_SYNTAX "minishell: syntax error"
# define ERR_UNEXPECTED_TOKEN "minishell: syntax error near unexpected token `%s'"
# define ERR_UNCLOSED_QUOTE "minishell: unexpected EOF while looking for matching `%c'"
# define ERR_NEWLINE "minishell: syntax error near unexpected token `newline'"

# define ERR_PIPE_FAILED "minishell: pipe failed"
# define ERR_FORK_FAILED "minishell: fork failed"

# define ERR_MALLOC "minishell: memory allocation failed"
# define ERR_EXECVE "minishell: execve failed"

# define ERR_CMD_NOT_FOUND "%s: command not found"
# define ERR_NO_SUCH_FILE "%s: No such file or directory"
# define ERR_PERMISSION_DENIED "%s: Permission denied"
# define ERR_IS_DIRECTORY "%s: Is a directory"
# define ERR_NOT_DIRECTORY "%s: Not a directory"

# define ERR_CD_TOO_MANY_ARGS "cd: too many arguments"
# define ERR_CD_NO_HOME "cd: HOME not set"
# define ERR_CD_NO_SUCH_FILE "cd: No such file or directory"
# define ERR_EXPORT_INVALID "export: `%s': not a valid identifier"
# define ERR_UNSET_INVALID "unset: `%s': not a valid identifier"
# define ERR_EXIT_NUMERIC "exit: %s: numeric argument required"
# define ERR_EXIT_TOO_MANY "exit: too many arguments"

#endif