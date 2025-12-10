#include "minishell.h"

/* ============================ */
/* ======== mimir utils ======= */
/* ============================ */

t_expand	*ft_init_expanders(void)
{
	t_expand	*expander;

	expander = malloc(1 * sizeof(t_expand));
	if (!expander)
		return (NULL);
	expander->init_quote = NULL;
	expander->end_quote = NULL;
	expander->var = NULL;
	expander->tmp_var = NULL;
	expander->aux = NULL;
	expander->s_end = 0;
	expander->s_init = 0;
	return (expander);
}

int	ft_handle_end_quote(t_expand **exp, char *content)
{
	int	i;
	int	size;

	i = (*exp)->s_init;
	size = (*exp)->s_init;
	while (content[i] && !ft_is_quote(content[i]))
		i++;
	if (ft_is_quote(content[i]))
	{
		(*exp)->end_quote = ft_substr(content, i, size);
		if (!(*exp)->end_quote)
			return (ft_pd_error(ERR_MALLOC, NULL, 12));
		(*exp)->s_end = i;
		return (0);
	}
	return (0);
}

int	ft_handle_init_quote(t_expand **exp, char *content)
{
	int	i;

	i = 0;
	while (content[i] && content[i] != '$')
		i++;
	if (i)
	{
		(*exp)->init_quote = ft_substr(content, 0, i);
		if (!(*exp)->init_quote)
			return (ft_pd_error(ERR_MALLOC, NULL, 12));
		(*exp)->s_init = i;
		return (0);
	}
	return (0);
}

int	ft_found_var(t_expand **exp, t_token **token)
{
	if ((*exp)->init_quote && (*exp)->end_quote)
	{
		(*exp)->aux = ft_strjoin((*exp)->init_quote, (*exp)->tmp_var);
		(*exp)->var = ft_strjoin((*exp)->aux, (*exp)->end_quote);
		if (!(*exp)->var)
			return (ft_pd_error(ERR_MALLOC, NULL, 12));
	}
	else
	{
		(*exp)->var = ft_strdup((*exp)->tmp_var);
		if (!(*exp)->var)
			return (ft_pd_error(ERR_MALLOC, NULL, 12));
	}
	free((*token)->content);
	(*token)->content = ft_strdup((*exp)->var);
	if (!(*token)->content)
		return (ft_pd_error(ERR_MALLOC, NULL, 12));
	return (0);
}

int	ft_no_found_var(t_expand **exp, t_token **token)
{
	if ((*exp)->init_quote && (*exp)->end_quote)
	{
		(*exp)->var = ft_strjoin((*exp)->init_quote, (*exp)->end_quote);
		if (!(*exp)->var)
			return (ft_pd_error(ERR_MALLOC, NULL, 12));
	}
	else
		(*exp)->var = ft_strdup("");
	free((*token)->content);
	(*token)->content = ft_strdup((*exp)->var);
	if (!(*token)->content)
		return (ft_pd_error(ERR_MALLOC, NULL, 12));
	return (0);
}
