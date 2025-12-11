#include "minishell.h"

/* ====================== */
/* ======== mimir ======= */
/* ====================== */

/*añado el comentario de '~' para saber que debemos expandirlo
NO ES PERMANENTE*/

void	ft_aux_need_to_expand(t_token **tkn, int state)
{
	int		i;

	i = 0;
	while ((*tkn)->content[i] && (*tkn)->expand == 0)
	{
		if (ft_is_quote((*tkn)->content[i]) == T_DQUOTE && !state)
			state = 2;
		else if (ft_is_quote((*tkn)->content[i]) == T_DQUOTE && state == 2)
			state = 0;
		else if (ft_is_quote((*tkn)->content[i]) == T_SQUOTE && !state)
			state = 1;
		else if (ft_is_quote((*tkn)->content[i]) == T_SQUOTE && state == 1)
			state = 0;
		else if ((*tkn)->content[i] == '$' && (*tkn)->content[i + 1] == '\0')
			return ;
		else if ((*tkn)->content[i] == '$' && state == 1)
			return ;
		else if ((*tkn)->content[i] == '$' && state == 2)
			(*tkn)->expand = 1;
		else if ((*tkn)->content[i] == '$' && !state)
			(*tkn)->expand = 1;
		i++;
	}
}

void	ft_need_to_expand(t_token **token)
{
	t_token	*aux;

	aux = (*token);
	while (aux)
	{
		ft_aux_need_to_expand(&aux, 0);
		aux = aux->next;
	}
}

int	ft_process_var(t_expand **exp, char **env, int exit, char *cont)
{
	int	init;
	int	end;

	init = (*exp)->s_init;
	end = (*exp)->s_end;
	if ((*exp)->init_quote && (*exp)->end_quote)
		(*exp)->var = ft_strtrim(cont + init, (*exp)->end_quote);
	else
		(*exp)->var = ft_strdup(cont);
	if (!(*exp)->var)
		return (ft_pd_error(ERR_MALLOC, NULL, 12));
	if (!ft_strcmp((*exp)->var, "$?"))
		(*exp)->tmp_var = ft_itoa(exit);
	else
		(*exp)->tmp_var = ft_get_var_value(env, (*exp)->var + 1);
	free((*exp)->var);
	return (0);
}

// t_exp_var	*init_vars(char *content)
// {
// 	t_exp_var	*vars;

// 	vars = malloc(1 * sizeof(t_exp_var));
// 	if (!vars)
// 		return (NULL);
// 	vars->content = content;
// 	vars->expand = 0;
// 	vars->next = NULL;
// 	return (vars);
// }

/* 

* a tenter en cuenta *

unovo-ru@c2r5s3:~/42/minishell/minishell$ echo $HOME/$$HOME
/home/unovo-ru/2587068HOME
unovo-ru@c2r5s3:~/42/minishell/minishell$ echo $HO/ME/$HOME
/ME//home/unovo-ru
unovo-ru@c2r5s3:~/42/minishell/minishell$ echo $/HO/ME/$HOME
$/HO/ME//home/unovo-ru
unovo-ru@c2r5s3:~/42/minishell/minishell$ echo $/HO/ME/$HOM
$/HO/ME/
unovo-ru@c2r5s3:~/42/minishell/minishell$ echo $$$HOME

*/

int	ft_check_two_var(t_token **token, t_expand **exp)
{
	int			i;
	int			dollar;

	i = 0;
	while ((*token)->content[i])
	{
		if ((*token)->content[i] == '$' && !dollar)
			dollar = 1;
		if ((*token)->content[i] == '$' && dollar)
		{
			(*exp)->dollar = 1;
			break ;
		}
		i++;
	}
	i = 0;
	while ((*token)->content[i])
	{
		if ((*token)->content[i] == '/')
		{
			(*exp)->slash = 1;
			break ;
		}
		i++;
	}
	if ((*exp)->dollar)
	{
		(*exp)->split = ft_split_dollar((*token)->content, '$');
		if (!(*exp)->split)
			return (-1);
		// hacemos cosas
	}
	else
		return (1);
	return (0);
}

int	ft_expand_var(t_token **token, char **env, int exit_status)
{
	t_expand	*exp;

	exp = ft_init_expanders();
	if (ft_handle_init_quote(&exp, (*token)->content))
		return (ft_clean_expanders(&exp));
	if (ft_handle_end_quote(&exp, (*token)->content))
		return (ft_clean_expanders(&exp));
	if (ft_process_var(&exp, env, exit_status, (*token)->content))
		return (ft_clean_expanders(&exp));
	if (!exp->tmp_var)
	{
		if (ft_no_found_var(&exp, token))
			return (ft_clean_expanders(&exp));
	}
	else
	{
		if (ft_found_var(&exp, token))
			return (ft_clean_expanders(&exp));
	}
	ft_clean_expanders(&exp);
	return (0);
}

int	ft_mimir(t_token **token, char **env, int exit_status)
{
	t_token	*aux;

	if (!env || !*env)
		return (0);
	ft_need_to_expand(token);
	aux = (*token);
	while ((*token))
	{
		if ((*token)->expand)
		{
			if (ft_expand_var(token, env, exit_status))
				return (1);
		}
		(*token) = (*token)->next;
	}
	(*token) = aux;
	return (0);
}




// int	ft_expand_var(t_token **token, char **env, int exit_status)
// {
// 	char	*init_quote;
// 	char	*end_quote;
// 	char	*tmp_var;
// 	char	*aux;
// 	char	*var;
// 	int		s_init;
// 	int		s_end;

// 	init_quote = NULL;
// 	end_quote = NULL;
// 	tmp_var = NULL;
// 	aux = NULL;
// 	var = NULL;

// 	// guardamos las comillas iniciales
// 	s_init = 0;
// 	while ((*token)->content[s_init] && (*token)->content[s_init] != '$')
// 		s_init++;
// 	if (s_init)
// 		init_quote = ft_substr((*token)->content, 0, s_init);
// 	s_end = s_init;

// 	// guardamos las comillas finales
// 	while ((*token)->content[s_end] && !ft_is_quote((*token)->content[s_end]))
// 		s_end++;
// 	if (ft_is_quote((*token)->content[s_end]))
// 		end_quote = ft_substr((*token)->content, s_end, s_init);

// 	// limpiamos las comillas y nos quedamos con la variable
// 	if (init_quote && end_quote)
// 		var = ft_strtrim((*token)->content + s_init, end_quote);
// 	else
// 		var = ft_strdup((*token)->content);

// 	// guardamos el contenido de la variable
// 	if (!ft_strcmp(var, "$?"))
// 		tmp_var = ft_itoa(exit_status);
// 	else
// 		tmp_var = ft_get_var_value(env, var + 1);
// 	free(var);
// 	if (!tmp_var)
// 	{
// 		if (init_quote && end_quote)
// 		{
// 			// tener en cuenta de solo:
// 			// ft_strjoin(init_quote, end_quote);
// 			aux = ft_strjoin(init_quote, "");
// 			var = ft_strjoin(aux, end_quote);
// 			if (!var)
// 			{

// 				return (ft_pd_error(ERR_MALLOC, NULL, 12));
// 			}
// 			free(aux);
// 			free(init_quote);
// 			free(end_quote);
// 		}
// 		else
// 			var = ft_strdup("");
// 		free((*token)->content);
// 		(*token)->content = var;
// 		return (0);
// 	}
// 	else
// 	{
// 		if (init_quote && end_quote)
// 		{
// 			aux = ft_strjoin(init_quote, tmp_var);
// 			var = ft_strjoin(aux, end_quote);
// 			free(aux);
// 			free(init_quote);
// 			free(end_quote);
// 		}
// 		else
// 			var = ft_strdup(tmp_var);
// 		free((*token)->content);
// 		(*token)->content = var;
// 		return (0);
// 	}
// }