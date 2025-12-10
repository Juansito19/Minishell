#include "minishell.h"

/* ====================== */
/* ====== expander ====== */
/* ====================== */

// Hay que agregar la logica para " echo $? "
// EXPANDE $USER
// EXPANDE "$USER"
// EXPANDE "'$USER'"
// NO EXPANDE 

void	ft_need_to_expand(t_token **token)
{
	t_token	*aux;
	int		state;
	int		i;

	state = 0;
	aux = (*token);
	while (aux)
	{
		i = 0;
		while (aux->content[i] && aux->expand == 0)
		{
			if (ft_is_quote(aux->content[i]) == T_DQUOTE && !state)
				state = 2;
			else if (ft_is_quote(aux->content[i]) == T_DQUOTE && state == 2)
				state = 0;
			else if (ft_is_quote(aux->content[i]) == T_SQUOTE && !state)
				state = 1;
			else if (ft_is_quote(aux->content[i]) == T_SQUOTE && state == 1)
				state = 0;
			else if (aux->content[i] == '$' && state == 1)
				break ;
			else if (aux->content[i] == '$' && state == 2)
				aux->expand = 1;
			else if (aux->content[i] == '$' && !state)
				aux->expand = 1;
			i++;
		}
		state = 0;
		aux = aux->next;
	}
}

int	ft_expand_var(t_token **token, char **env)
{
	char	*init_quote;
	char	*end_quote;
	char	*tmp_var;
	char	*aux;
	char	*var;
	int		s_init;
	int		s_end;

	init_quote = NULL;
	end_quote = NULL;
	tmp_var = NULL;
	aux = NULL;
	var = NULL;

	// guardamos las comillas iniciales
	s_init = 0;
	while ((*token)->content[s_init] && (*token)->content[s_init] != '$')
		s_init++;
	if (s_init)
		init_quote = ft_substr((*token)->content, 0, s_init);
	s_end = s_init;
	printf("init_quote -> %s\n", init_quote);

	// guardamos las comillas finales
	while ((*token)->content[s_end] && !ft_is_quote((*token)->content[s_end]))
		s_end++;
	if (ft_is_quote((*token)->content[s_end]))
		end_quote = ft_substr((*token)->content, s_end, s_init);
	printf("end_quote -> %s\n", end_quote);

	// limpiamos las comillas y nos quedamos con la variable
	// if (init_quote && end_quote)
	// 	var = ft_substr((*token)->content, s_init, s_end);
	// else
	// 	var = ft_substr((*token)->content, s_init, s_end);
	if (init_quote && end_quote)
		var = ft_strtrim((*token)->content + s_init, end_quote);
	else
		var = ft_strdup((*token)->content);

	printf("var -> %s\n", var);
	// guardamos el contenido de la variable
	tmp_var = ft_get_var_value(env, var + 1);
	free(var);
	if (!tmp_var)
	{
		if (init_quote && end_quote)
		{
			// tener en cuenta de solo:
			// ft_strjoin(init_quote, end_quote);
			aux = ft_strjoin(init_quote, "");
			var = ft_strjoin(aux, end_quote);
			free(aux);
			free(init_quote);
			free(end_quote);
		}
		else
			var = ft_strdup("");
		free((*token)->content);
		(*token)->content = var;
		return (0);
	}
	else
	{
		if (init_quote && end_quote)
		{
			aux = ft_strjoin(init_quote, tmp_var);
			var = ft_strjoin(aux, end_quote);
			free(aux);
			free(init_quote);
			free(end_quote);
		}
		else
			var = ft_strdup(tmp_var);
		free((*token)->content);
		(*token)->content = var;
		return (0);
	}
}

int	ft_expand(t_token **token, char **env)
{
	t_token	*aux;

	if (!env || !*env)
		return (0);
	ft_need_to_expand(token);
	aux = (*token);
	while ((*token))
	{
		if ((*token)->expand)
			ft_expand_var(token, env);
		(*token) = (*token)->next;
	}
	(*token) = aux;
	return (0);
}
