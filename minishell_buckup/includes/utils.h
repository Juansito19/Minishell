/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrosio <jbrosio@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 19:04:32 by jbrosio           #+#    #+#             */
/*   Updated: 2026/01/15 19:04:33 by jbrosio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include "minishell.h"

typedef enum s_type		t_type;
typedef struct s_token	t_token;
typedef struct s_tree	t_tree;
typedef struct s_data	t_data;
typedef struct s_expand	t_expand;

/* ============================ */
/* ========== utils =========== */
/* ============================ */

int		ft_find_path(t_tree **tree, char **envp);

/**
 * @brief Gets pointer to static heredoc interruption counter.
 * @param reset If 1, resets counter to 0; if 0, returns pointer.
 * @return Pointer to static interrupt counter.
 * @note Used to track heredoc interruptions for newline handling.
 */
int		*ft_get_times_ptr(int reset);

/**
 * @brief Resets heredoc interruption counter to zero.
 * @note Wrapper function that calls ft_get_times_ptr(1).
 */
void	ft_reset_heredoc_times(void);

/* ============================ */

/* ============================ */
/* ====== type_validator ====== */
/* ============================ */

/**
 * @brief Checks if character is a metacharacter (<, >, |).
 * @param c Character to check.
 * @return Token type (T_REDIR_IN/T_REDIR_OUT/T_PIPE) or 0.
 */
int		ft_is_metachar(char c);

/**
 * @brief Determines if token content is a builtin command.
 * @param token Pointer to token to check.
 * @return T_BUILTIN if builtin, T_EOF/T_FD if special, T_CMD else.
 * @note Checks: echo, cd, pwd, export, unset, exit, env.
 */
t_type	ft_is_builtin(t_token **token);

/**
 * @brief Validates if type is a redirection operator.
 * @param type Token type to check.
 * @return Same type if redirection, 0 otherwise.
 * @note Checks: T_REDIR_IN, T_REDIR_OUT, T_HEREDOC, T_APPEND.
 */
t_type	ft_is_red(t_type type);

/**
 * @brief Identifies token type from metacharacter string.
 * @param content String to analyze (|, <, >, <<, >>).
 * @return Corresponding token type or 0 if not metacharacter.
 */
t_type	ft_take_meta(char *content);

/**
 * @brief Checks if character is a quote (' or ").
 * @param c Character to check.
 * @return T_SQUOTE, T_DQUOTE, or 0 if not a quote.
 */
t_type	ft_is_quote(char c);

/* ============================ */

/* ============================ */
/* ========== clean =========== */
/* ============================ */

/**
 * @brief Recursively frees execution tree and its content.
 * @param tree Pointer to tree root.
 * @note Frees content array, path string, and all child nodes.
 */
void	ft_clean_yggdrasil(t_tree **tree);

/**
 * @brief Frees entire token linked list.
 * @param head Pointer to token list head.
 * @note Frees content strings and token nodes, sets head to NULL.
 */
void	ft_free_tokens(t_token **head);

/**
 * @brief Frees all data structure components.
 * @param data Pointer to main data structure.
 * @note Frees path, env, yggdrasil tree, tokens, and data itself.
 */
void	ft_clean_data(t_data **data);

/**
 * @brief Frees multiple resources in one call.
 * @param tree Execution tree to free (optional).
 * @param token Token list to free (optional).
 * @param input Input string to free (optional).
 * @param s String array to free (optional).
 * @return Always returns NULL.
 * @note Pass NULL for resources that don't need freeing.
 */
void	*ft_free_all(t_tree **tree, t_token **token, char **input, char ***s);

/* ============================ */

#endif
