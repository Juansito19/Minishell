#ifndef MINISHELL_H
# define MINISHELL_H
# define _XOPEN_SOURCE 700
# define _GNU_SOURCE
# include "../libft/libft.h"
# include "token_tree.h"
# include "builtins.h"
# include "utils.h"
# include "parse.h"
# include "ratatoskr.h"
# include "mimir.h"
# include "banner.h"
# include "errors.h"
# include "signals.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <signal.h>
# include <dirent.h>
# include <termios.h>
# include <term.h>

# ifndef PIPE
#  define PIPE "|"
# endif
# ifndef RED_IN
#  define RED_IN "<"
# endif
# ifndef RED_OUT
#  define RED_OUT ">"
# endif
# ifndef APPEND
#  define APPEND ">>"
# endif
# ifndef HEREDOC
#  define HEREDOC "<<"
# endif
# ifndef SQUOTE
#  define SQUOTE "\'"
# endif
# ifndef DQUOTE
#  define DQUOTE "\""
# endif

# ifndef RED
#  define RED "\033[31m"
# endif
# ifndef YELLOW
#  define YELLOW "\033[33m"
# endif
# ifndef WHITE
#  define WHITE "\033[37m"
# endif
# ifndef VLT
#  define VLT "\033[95m"
# endif
# ifndef MAGENT
#  define MAGENT "\033[96m"
# endif
# ifndef BLUE
#  define BLUE "\033[34m"
# endif
# ifndef RST
#  define RST "\033[0m"
# endif

extern int	g_status;

typedef enum s_type
{
	T_PIPE = 1,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_APPEND,
	T_HEREDOC,
	T_SQUOTE,
	T_DQUOTE,
	T_WORD,
	T_CMD,
	T_BUILTIN,
	T_FD,
	T_EOF,
}	t_type;

/**
 * @brief Token node for lexical analysis.
 * 
 * Represents a single token in the command line input. Tokens are
 * linked together to form the complete tokenized input.
 */
typedef struct s_token
{
	t_type			type;		/* Token classification (word/operator) */
	char			*content;	/* Token string content */
	int				expand;		/* Expand's flag [0]no, [1]yes */
	struct s_token	*next;		/* Pointer to next token in list */
}	t_token;

/**
 * @brief Binary tree node for command execution.
 * 
 * Represents a command or operator in the execution tree. Each node
 * can be a simple command, pipe, or redirection. Tree structure allows
 * for proper command execution order and pipe handling.
 */
typedef struct s_tree
{
	char			**content;		/* Command and arguments array */
	int				infile;			/* Input file descriptor */
	int				outfile;		/* Output file descriptor */
	int				pipe[2];		/* Pipe descriptors [read, write] */
	char			*path;			/* Builtin command identifier */
	t_type			type;			/* Node type (cmd/pipe/redir) */
	struct s_tree	*left;			/* Left child (cmd before pipe) */
	struct s_tree	*right;			/* Right child (cmd after pipe) */
}	t_tree;

/**
 * @brief Main program data structure.
 * 
 * Holds all global state for the minishell program including tokens,
 * execution tree, environment path, and file descriptors. Passed between
 * functions to maintain program state.
 */
typedef struct s_data
{
	t_token	*tokens;		/* Linked list of input tokens */
	t_tree	*yggdrasil;		/* Binary tree of yggdrasil */
	char	*path;			/* PATH environment variable */
	char	**env;			/* Environments variables */
	int		infile;			/* Standard input backup fd */
	int		outfile;		/* Standard output backup fd */
	int		exit_status;	/* Last command exit status */
}	t_data;

#endif
