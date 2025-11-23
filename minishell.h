#ifndef MINISHEL_H
# define MINISHEL_H
# include "libft/libft.h"
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

typedef	enum {
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
	T_FD
} t_token_type;

// typedef	enum {
// 	T_CMD,
// 	T_ECHO,
// 	T_CD,
// 	T_PWD,
// 	T_EXPORT,
// 	T_UNSET,
// 	T_EXIT,
// 	T_ENV
// } t_builtin;

/**
 * @brief Token node for lexical analysis.
 * 
 * Represents a single token in the command line input. Tokens are
 * linked together to form the complete tokenized input.
 */
typedef struct s_token
{
	t_token_type	type;		/* Token classification (word/operator) */
	char			*content;	/* Token string content */
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
	char			*path;		/* Builtin command identifier */
	t_token_type	type;			/* Node type (cmd/pipe/redir) */
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
	t_tree	*cmds;			/* Binary tree of commands */
	char	*path;			/* PATH environment variable */
	int		infile;			/* Standard input backup fd */
	int		outfile;		/* Standard output backup fd */
	int		exit_status;	/* Last command exit status */
}	t_data;

/* ========================= */
/* =========tokens========== */
/* ========================= */

t_token			*ft_token(char *s, int i);
int				ft_token_word(t_token **tokens, char *s, int *ind);
int				ft_token_meta(t_token **tokens, char *s, int *ind, t_token_type type);

/* _____________________________________________________________________ */

/* ================================= */
/* ========= tokens utils ========== */
/* ================================= */

t_token			*ft_token_init(void *content, t_token_type type);
void			ft_tokenadd_back(t_token **tokens, t_token *new);
void			ft_free_tokens(t_token **head);
int				ft_tk_size(t_token *lst);

/* _____________________________________________________________________ */

/* ============================ */
/* =========== tree =========== */
/* ============================ */

t_token			*ft_put_all_left(t_token **tokens, t_token *token_pipe);
t_token			*ft_put_all_right(t_token **tokens);
void			ft_treeadd_right(t_tree **tree, t_tree *new);
void			ft_treeadd_left(t_tree **tree, t_tree *new);
char			**ft_fill_word_type(t_token *token, int	size);
void			ft_yggdrasil(t_token **tokens, t_tree **tree);

/* _____________________________________________________________________ */

/* ================================= */
/* ========== tree utils =========== */
/* ================================= */

t_tree			*ft_tree_init(char **content, t_token_type type);
t_token			*ft_search_pipe(t_token **tokens);
t_token			*ft_search_red(t_token **tokens);
void			ft_treeadd_right(t_tree **tree, t_tree *new);
void			ft_treeadd_left(t_tree **tree, t_tree *new);

/* _____________________________________________________________________ */

/* ============================ */
/* ========== utils =========== */
/* ============================ */

int				ft_is_metachar(char c);
t_token_type	ft_is_builtin(t_token *token);
t_token_type 	ft_is_red(char *content);

/* _____________________________________________________________________ */

/* ============================ */
/* ========== parse =========== */
/* ============================ */

int				ft_open_quote(char *input);

/* _____________________________________________________________________ */


/* ============================ */
/* ========== banner ========== */
/* ============================ */

void    ft_banner_1(void);
void    ft_banner_2(void);
void    ft_banner_3(void);
void    ft_banner_4a(void);
void    ft_banner_4b(void);

/* _____________________________________________________________________ */

#endif