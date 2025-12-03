#ifndef BUILTINS_H
# define BUILTINS_H

/* ============================ */
/* ========= builtin ========== */
/* ============================ */

// =========== PWD ============ //

int			ft_pwd(void);

// =========== CD ============= //

char		*ft_get_var_value(char **env, char *key);
int			ft_update_pwd_vars(char ***env, char *oldpwd);
char		*ft_take_path(char ***env, char *av);
int			ft_cd(char ***env, char *av);

// ========= EXPORT =========== //

void		ft_sort_env(char **env);
int			ft_export_no_av(char **env);
int			ft_validate_av_export(char *av);
int			ft_get_var(char **env, char *av);
char		**ft_add_var(char **env, char *var);
int			ft_change_or_add_var(char ***env, char *av);
int			ft_export(char ***env, char **av);

// ========== UNSET =========== //

int			ft_validate_av_unset(char *av);
int			ft_unset_var(char ***env, char *av);
int			ft_unset(char ***env, char **av);

#endif
