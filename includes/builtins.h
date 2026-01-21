/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrosio <jbrosio@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 19:04:35 by jbrosio           #+#    #+#             */
/*   Updated: 2026/01/15 19:04:36 by jbrosio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

/* ============================ */
/* ========= builtin ========== */
/* ============================ */

/**
 * @brief Counts the number of words in an array.
 * @param av Array of strings to count.
 * @return Number of elements in the array.
 */
int		ft_count_words(char **av);

/**
 * @brief Executes the appropriate builtin command.
 * @param data Pointer to shell data structure.
 * @param av Command arguments array.
 * @param env Environment variables array.
 * @return 0 on success, error code otherwise.
 */
int		ft_builtins(t_data **data, char **av, char **env);

// =========== PWD ============ //

/**
 * @brief Prints the current working directory.
 * @param env Environment variables array.
 * @return 0 on success, error code otherwise.
 */
int		ft_pwd(char **env);

// =========== CD ============= //

/**
 * @brief Gets the value of an environment variable.
 * @param env Environment variables array.
 * @param key Variable name to search for.
 * @return Pointer to value string, or NULL if not found.
 */
char	*ft_get_var_value(char **env, char *key);

/**
 * @brief Updates PWD and OLDPWD environment variables.
 * @param env Pointer to environment variables array.
 * @param oldpwd Previous working directory path.
 * @return 0 on success, error code otherwise.
 */
int		ft_update_pwd_vars(char ***env, char *oldpwd);

/**
 * @brief Gets the target path for cd command.
 * @param env Pointer to environment variables array.
 * @param av Argument passed to cd command.
 * @return Pointer to path string, or NULL on error.
 */
char	*ft_take_path(char ***env, char *av);

/**
 * @brief Searches and removes OLDPWD from environment.
 * @param env Pointer to environment variables array.
 * @return 0 on success, error code otherwise.
 */
int		ft_search_oldpwd(char ***env);

/**
 * @brief Changes the current working directory.
 * @param env Pointer to environment variables array.
 * @param av Command arguments array.
 * @return 0 on success, error code otherwise.
 */
int		ft_cd(char ***env, char **av);

// ========= EXPORT =========== //

/**
 * @brief Increments the SHLVL environment variable.
 * @param env Pointer to environment variables array.
 */
void	ft_increment_shlvl(char ***env);

/**
 * @brief Creates a minimal default environment.
 * @return Pointer to newly allocated environment array.
 */
char	**ft_no_env(void);

/**
 * @brief Sorts environment variables alphabetically.
 * @param env Environment variables array to sort.
 */
void	ft_sort_env(char **env);

/**
 * @brief Displays environment in export format.
 * @param env Environment variables array.
 * @param i Starting index (should be -1).
 * @param j Secondary index (should be -1).
 * @return 0 on success, error code otherwise.
 */
int		ft_export_no_av(char **env, int i, int j);

/**
 * @brief Validates export argument syntax.
 * @param av Argument string to validate.
 * @return 0 if valid, 1 if invalid.
 */
int		ft_validate_av_export(char *av);

/**
 * @brief Finds a variable in environment array.
 * @param env Environment variables array.
 * @param av Variable name to search for.
 * @return Index if found, -1 if not found, -2 if no value.
 */
int		ft_get_var(char **env, char *av);

/**
 * @brief Adds a new variable to environment array.
 * @param env Environment variables array.
 * @param var Variable string to add.
 * @return Pointer to new environment array, or NULL on error.
 */
char	**ft_add_var(char **env, char *var);

/**
 * @brief Changes existing variable or adds new one.
 * @param env Pointer to environment variables array.
 * @param av Variable string to change or add.
 * @return 0 on success, error code otherwise.
 */
int		ft_change_or_add_var(char ***env, char *av);

/**
 * @brief Exports variables to environment.
 * @param env Pointer to environment variables array.
 * @param av Arguments array with variables to export.
 * @return 0 on success, error code otherwise.
 */
int		ft_export(char ***env, char **av);

// ========== UNSET =========== //

/**
 * @brief Finds a variable index in environment for unset.
 * @param env Environment variables array.
 * @param av Variable name to search for.
 * @return Index if found, -1 if not found.
 */
int		ft_get_var_unset(char **env, char *av);

/**
 * @brief Validates unset argument syntax.
 * @param av Argument string to validate.
 * @return 0 if valid, 1 if invalid.
 */
int		ft_validate_av_unset(char *av);

/**
 * @brief Removes a variable from environment array.
 * @param env Pointer to environment variables array.
 * @param av Variable name to remove.
 * @return 0 on success, error code otherwise.
 */
int		ft_unset_var(char ***env, char *av);

/**
 * @brief Unsets variables from environment.
 * @param env Pointer to environment variables array.
 * @param av Arguments array with variables to unset.
 * @return 0 on success, error code otherwise.
 */
int		ft_unset(char ***env, char **av);

// ========== ECHO =========== //

/**
 * @brief Implements the echo builtin command.
 * @param ac Argument count.
 * @param str Arguments array.
 * @return 0 on success, error code otherwise.
 */
int		ft_echo(int ac, char **str);

/**
 * @brief Writes strings to output in a loop.
 * @param i Starting index in string array.
 * @param str Array of strings to write.
 */
void	write_bucle(int i, char **str);

/**
 * @brief Checks for -n flag in echo arguments.
 * @param ind Pointer to store index after flags.
 * @param str Arguments array to check.
 * @return 1 if -n flag found, 0 otherwise.
 */
int		ft_flag_echo(int *ind, char **str);

// ========== ENV =========== //

/**
 * @brief Displays environment variables.
 * @param env Environment variables array.
 * @param av Command arguments array.
 * @return 0 on success, error code otherwise.
 */
int		ft_env(char **env, char **av);

// ========== EXIT =========== //

/**
 * @brief Implements the exit builtin command.
 * @param data Pointer to shell data structure.
 * @param status Exit status arguments array.
 * @return 0 on success, error code otherwise.
 */
int		ft_exit(t_data **data, char **status);

/* ============================ */

#endif
