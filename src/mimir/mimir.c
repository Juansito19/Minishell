#include "minishell.h"

/* ====================== */
/* ======== mimir ======= */
/* ====================== */

int	ft_append_val(char **res, char *str, int i, t_data **data)
{
	int		len;
	char	*var_name;
	char	*val;

	if (str[i + 1] == '?')
	{
		ft_add_str(res, ft_itoa((*data)->exit_status));
		return (i + 2);
	}
	len = 0;
	while (str[i + 1 + len] && (ft_isalnum(str[i + 1 + len])
			|| str[i + 1 + len] == '_'))
		len++;
	if (len == 0)
	{
		ft_add_char(res, '$');
		return (i + 1);
	}
	var_name = ft_substr(str, i + 1, len);
	val = ft_get_var_value((*data)->env, var_name);
	ft_add_str(res, val);
	free(var_name);
	return (i + 1 + len);
}

void	ft_flags_state(char s, int *state)
{
	if (s == '\'' && *state == 0)
		*state = 1;
	else if (s == '\'' && *state == 1)
		*state = 0;
	else if (s == '\"' && *state == 0)
		*state = 2;
	else if (s == '\"' && *state == 2)
		*state = 0;
}

char	*ft_process_new_expansion(char *str, t_data **data)
{
	char	*res;
	int		i;
	int		state;

	res = ft_strdup("");
	if (!res)
		return (NULL);
	i = 0;
	state = 0;
	while (str[i])
	{
		ft_flags_state(str[i], &state);
		if (str[i] == '$' && state != 1 && (ft_isalnum(str[i + 1])
				|| str[i + 1] == '_' || str[i + 1] == '?'))
			i = ft_append_val(&res, str, i, data);
		else
		{
			ft_add_char(&res, str[i]);
			i++;
		}
	}
	return (res);
}

int	ft_expand_var(t_token **token, t_data **data)
{
	char	*new_content;

	if (!token || !*token || !(*token)->content)
		return (0);
	new_content = ft_process_new_expansion((*token)->content, data);
	if (!new_content)
		return (ft_pd_error(ERR_MALLOC, NULL, 12));
	free((*token)->content);
	(*token)->content = new_content;
	return (0);
}

int	ft_mimir(t_token **token, t_data **data)
{
	t_token	*aux;

	if (!(*data)->env || !(*data)->env[0])
		return (0);
	ft_need_to_expand(token);
	aux = (*token);
	while ((*token))
	{
		if ((*token)->expand)
		{
			if (ft_expand_var(token, data))
				return (1);
		}
		(*token) = (*token)->next;
	}
	(*token) = aux;
	return (0);
}
