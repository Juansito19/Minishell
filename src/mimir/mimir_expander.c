#include "minishell.h"

/* =============================== */
/* ======== mimir expander ======= */
/* =============================== */

int	ft_find_limit(t_expand **exp, char *s, int i)
{
	(*exp)->limit = 0;
	if (s[i] == '$')
	{
		while (s[++i])
		{
			if (!ft_isalnum(s[i]) && s[i] != '_')
			{
				(*exp)->limit = 1;
				return (i);
			}
		}
	}
	else
	{
		while (s[i])
		{
			if (s[i] == '$')
			{
				(*exp)->limit = 1;
				return (i);
			}
			i++;
		}
	}
	return (i);
}

int	ft_expander_validator(t_expand **exp, int i, int size)
{
	if ((*exp)->split[i][0] != '$')
		return (1);
	else if (size == 1)
		return (1);
	else if (!ft_isalpha((*exp)->split[i][1]) && (*exp)->split[i][1] != '_')
		return (1);
	else
		return (0);
}

void	ft_variable_search(t_expand **exp, char **env, int i, int exit)
{
	if (!ft_strcmp((*exp)->tmp_var, "$?"))
		(*exp)->split[i] = ft_itoa(exit);
	else
		(*exp)->split[i] = ft_get_var_value(env, (*exp)->tmp_var + 1);
	if (!(*exp)->split[i])
		(*exp)->split[i] = ft_strdup("");
	free((*exp)->tmp_var);
	(*exp)->tmp_var = NULL;
}

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
