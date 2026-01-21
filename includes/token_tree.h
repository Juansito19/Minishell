/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_tree.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrosio <jbrosio@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 19:04:56 by jbrosio           #+#    #+#             */
/*   Updated: 2026/01/15 19:04:57 by jbrosio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_TREE_H
# define TOKEN_TREE_H
# include "./minishell.h"

typedef enum s_type		t_type;
typedef struct s_token	t_token;
typedef struct s_tree	t_tree;
typedef struct s_data	t_data;

/* ================================= */
/* ============tokens=============== */
/* ================================= */

/**
 * @brief Main tokenizer, converts input string to token list.
 * @param s Input string to tokenize.
 * @param i Starting index (usually 0).
 * @return Pointer to token list head, NULL on error.
 * @note Handles words, metacharacters (|, <, >, <<, >>), spaces.
 */
t_token		*ft_token(char *s, int i);

/**
 * @brief Creates word token from input string.
 * @param tokens Pointer to token list.
 * @param s String to tokenize.
 * @param ind Index pointer (updated after token creation).
 * @return 0 on success, -1 on error, 0 if size <= 0.
 * @note Handles $ before quotes, respects quote boundaries.
 */
int			ft_token_word(t_token **tokens, char *s, int *ind);

/**
 * @brief Creates metacharacter token (|, <, >, <<, >>).
 * @param tokens Pointer to token list.
 * @param s String containing metacharacter.
 * @param ind Index pointer (updated by 1 or 2).
 * @param type Type of metacharacter token.
 * @return 0 on success, -1 on error.
 * @note Handles double-char operators (<<, >>).
 */
int			ft_token_meta(t_token **tokens, char *s, int *ind, t_type type);

// ================================= //

/* ================================= */
/* ========= tokens utils ========== */
/* ================================= */

/**
 * @brief Initializes new token with content and type.
 * @param content Token string content.
 * @param type Token type classification.
 * @return Pointer to new token, NULL on error.
 * @note Sets expand flag to 0, next to NULL.
 */
t_token		*ft_token_init(void *content, t_type type);

/**
 * @brief Adds token to end of token list.
 * @param tokens Pointer to token list head.
 * @param new Token to add.
 * @note If list empty, sets new as head.
 */
void		ft_tokenadd_back(t_token **tokens, t_token *new);

/**
 * @brief Counts number of tokens in list.
 * @param lst Pointer to token list head.
 * @return Number of tokens in list.
 */
int			ft_tk_size(t_token *lst);

// ================================= //

/* ================================= */
/* ======== search_quotes ========== */
/* ================================= */

/**
 * @brief Processes all tokens, removes quotes from content.
 * @param token Pointer to token list head.
 * @note Changes type to T_CMD after quote removal.
 */
void		ft_search_quotes(t_token **token);

/**
 * @brief Copies string content without quotes to word.
 * @param s Source string with quotes.
 * @param word Destination string (pre-allocated).
 * @param i Starting index.
 * @param state Quote state tracker (0/1/2).
 * @note State: 0=none, 1=single quote, 2=double quote.
 */
void		ft_put_word(char *s, char **word, int i, int *state);

/**
 * @brief Calculates size of string without quotes.
 * @param s String to measure.
 * @param i Starting index.
 * @param count Character counter.
 * @param state Quote state (0=none, 1=single, 2=double).
 * @return Size of string without quote characters.
 */
int			ft_token_word_size(char *s, int i, int count, int state);

/**
 * @brief Removes quotes from token content, updates type.
 * @param token Pointer to token to clean.
 * @return 0 on success, 12 on malloc error.
 * @note Frees old content, allocates new without quotes.
 */
int			ft_token_clean_word(t_token **token);

// ================================= //

/* ================================= */
/* ========== yggdrasil ============ */
/* ================================= */

/**
 * @brief Extracts tokens before pipe into sublist.
 * @param tokens Pointer to full token list.
 * @param token_pipe Pointer to pipe token.
 * @return Pointer to left sublist (before pipe).
 * @note Modifies original list, sets pipe's prev->next to NULL.
 */
t_token		*ft_put_all_left(t_token **tokens, t_token *token_pipe);

/**
 * @brief Extracts tokens after pipe into sublist.
 * @param tokens Pointer to full token list.
 * @return Pointer to right sublist (after pipe).
 * @note Returns token after first element.
 */
t_token		*ft_put_all_right(t_token **tokens);

/**
 * @brief Converts token list to string array for tree content.
 * @param token Pointer to token list.
 * @param size Number of tokens to convert.
 * @return Allocated string array, NULL on error.
 * @note Only processes T_CMD and T_BUILTIN types.
 */
char		**ft_fill_word_type(t_token *token, int size);

/**
 * @brief Main tree builder, converts token list to execution tree.
 * @param tokens Pointer to token list.
 * @param tree Pointer to tree root.
 * @param data Pointer to program data.
 * @return 0 on success, 1 on error.
 * @note Recursively processes pipes and redirections.
 */
int			ft_yggdrasil(t_token **tokens, t_tree **tree, t_data **data);

// ================================= //

/* ================================= */
/* ======= yggdrasil branch ======== */
/* ================================= */

/**
 * @brief Processes metacharacter tokens (redirections/pipes).
 * @param meta Metacharacter token.
 * @param tree Pointer to tree node.
 * @param tokens Pointer to token list.
 * @param data Pointer to program data.
 * @return 0 on success, 1 on error.
 * @note Handles pipes, redirections, sets file descriptors.
 */
int			ft_branch_m(t_token *meta, t_tree **tree,\
			t_token **tokens, t_data **data);

/**
 * @brief Processes word tokens (commands and arguments).
 * @param tree Pointer to tree node.
 * @param tokens Pointer to token list.
 * @param env Environment variables array.
 * @return 0 on success, 1 on error.
 * @note Creates tree node with command content.
 */
int			ft_branch_w(t_tree **tree, t_token **tokens, char **env);

// ================================= //

/* ================================= */
/* ======== yggdrasil utils ======== */
/* ================================= */

/**
 * @brief Initializes new tree node with content and type.
 * @param content Command and arguments array.
 * @param type Node type (cmd/pipe/redir).
 * @param env Environment variables array.
 * @return Pointer to new tree node, NULL on error.
 * @note Initializes fds to -1, sets PATH if T_CMD.
 */
t_tree		*ft_tree_init(char **content, t_type type, char **env);

/**
 * @brief Searches for first pipe token in list.
 * @param tokens Pointer to token list.
 * @return Pointer to pipe token, NULL if not found.
 */
t_token		*ft_search_pipe(t_token **tokens);

/**
 * @brief Searches for first redirection token in list.
 * @param tokens Pointer to token list.
 * @return Pointer to redirection token, NULL if not found.
 * @note Checks T_REDIR_IN, T_REDIR_OUT, T_HEREDOC, T_APPEND.
 */
t_token		*ft_search_red(t_token **tokens);

// ================================= //

#endif
