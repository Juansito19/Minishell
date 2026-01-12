#ifndef BUILTINS_H
# define BUILTINS_H

/* ============================ */
/* ========= builtin ========== */
/* ============================ */

int		ft_count_words(char **av);
int		ft_builtins(t_data **data, char **av, char **env);

// =========== PWD ============ //

int		ft_pwd(char **env);

// =========== CD ============= //

char	*ft_get_var_value(char **env, char *key);
int		ft_update_pwd_vars(char ***env, char *oldpwd);
char	*ft_take_path(char ***env, char *av);
int		ft_search_oldpwd(char ***env);
int		ft_cd(char ***env, char **av);

// ========= EXPORT =========== //

char	**ft_no_env(void);
void	ft_sort_env(char **env);
int		ft_export_no_av(char **env, int i, int j);
int		ft_validate_av_export(char *av);
int		ft_get_var(char **env, char *av);
char	**ft_add_var(char **env, char *var);
int		ft_change_or_add_var(char ***env, char *av);
int		ft_export(char ***env, char **av);


// ========== UNSET =========== //

int		ft_validate_av_unset(char *av);
int		ft_unset_var(char ***env, char *av);
int		ft_unset(char ***env, char **av);

// ========== ECHO =========== //

int		ft_echo(int ac, char **str);
void	write_bucle(int i, char **str);
int		ft_flag_echo(int *ind, char **str);

// ========== ENV =========== //

int		ft_env(char **env);

// ========== EXIT =========== //

int		ft_exit(t_data **data, char **status);

/* ============================ */

#endif
