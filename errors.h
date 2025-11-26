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

#endif