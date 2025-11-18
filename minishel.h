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
#  define PIPE = "|"
# endif
# ifndef RED_IN
#  define RED_IN = "<"
# endif
# ifndef RED_OUT
#  define RED_OUT = ">"
# endif
# ifndef APPEND
#  define APPEND = ">>"
# endif
# ifndef HEREDOC
#  define HEREDOC = "<<"
# endif
# ifndef SQUOTE
#  define SQUOTE = "\'"
# endif
# ifndef DQUOTE
#  define DQUOTE = "\""
# endif

typedef	enum {
	T_PIPE = 1,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_APPEND,
	T_HEREDOC,
	T_SQUOTE,
	T_DQUOTE,
	T_WORD
} t_token_type;

typedef	struct s_token {
	t_token_type	type;
	char			*content;
	struct s_token	*next;
} t_token;

typedef	struct s_tree {
	char			**content;
	int				infile;
	int				outfile;
	int				pipe[2];
	int				is_builting;
	struct s_tree	*left;
	struct s_tree	*right;
} t_tree;

typedef struct s_data {
	t_token	*tokens;
	t_tree	*cmds;
	char	*path;
	int		infile;
	int		outfile;
	int		exit_status;
} t_data;

/* ========================= */
/* =========tokens========== */
/* ========================= */

t_token	*ft_token_init(void *content, t_token_type type);
t_token	*ft_token(char *s, int i);
void	ft_tokenadd_back(t_token **tokens, t_token *new);
int		ft_token_word(t_token **tokens, char *s, int *ind);
int		ft_token_meta(t_token **tokens, char *s, int *ind, t_token_type type);
void	ft_free_tokens(t_token **head);

/* ========================== */
/* ===========tree=========== */
/* ========================== */

t_tree	*ft_tree_init(void **content);
void	ft_treeadd_right(t_tree **tree, t_tree *new);
void	ft_treeadd_left(t_tree **tree, t_tree *new);

#endif