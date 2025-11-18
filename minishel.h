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
	char			**content;
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

#endif