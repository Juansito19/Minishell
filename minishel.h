#ifndef MINISHEL_H
# define MINISHEL_H
# include "libft/libft.h"

typedef	enum {
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_REDIR_APPEND,
	T_REDIR_HEREDOC,
	T_SQUOTE,
	T_DQUOTE,
	T_WORD
} t_token_type;

typedef	struct s_node {
	t_token_type	type;
	struct s_node	*left;
	struct s_node	*right;
	char			**content;
} t_node;

typedef	struct s_cmd {
	char	**av;
	int		infile;
	int		outfile;
} t_cmd;

typedef struct s_data {
	t_node	*tokens;
	t_cmd	*cmds;
	char	*path;
	int		infile;
	int		outfile;
	int		exit_status;
} t_data;

#endif