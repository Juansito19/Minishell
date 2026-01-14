#include "minishell.h"

/* =============================== */
/* ======== mimir expander ======= */
/* =============================== */

int	ft_find_limit(t_expand **exp, char *s, int i)
{
	(*exp)->limit = 0;
	if (s[i] != '$')
	{
		while (s[i] && s[i] != '$')
			i++;
		if (s[i])
			(*exp)->limit = 1;
		return (i);
	}
	if (s[++i] == '?')
	{
		(*exp)->limit = 1;
		return (i + 1);
	}
	while (s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
		i++;
	if (s[i])
		(*exp)->limit = 1;
	return (i);
}

// int	ft_find_limit(t_expand **exp, char *s, int i)
// {
// 	(*exp)->limit = 0;
// 	if (s[i] == '$')
// 	{
// 		while (s[++i])
// 		{
// 			if ((!ft_isalnum(s[i]) && s[i] != '_') || s[i] == '?')
// 			{
// 				(*exp)->limit = 1;
// 				if (s[i] == '?')
// 					return (i + 1);
// 				return (i);
// 			}
// 		}
// 	}
// 	else
// 	{
// 		while (s[i])
// 		{
// 			if (s[i] == '$')
// 			{
// 				(*exp)->limit = 1;
// 				return (i);
// 			}
// 			i++;
// 		}
// 	}
// 	return (i);
// }

// (8 lineas)
// Esta funcion retorna uno cada vez que haya que ignorar la posicion 
// en el split
int	ft_expander_validator(t_expand **exp, int i, int size)
{
	// Si no tiene el $ en la primera posicion ES recorte
	if ((*exp)->split[i][0] != '$')
		return (1);
	// Si el size de este string es de 1 es un caracter sobrante
	else if (size == 1)
		return (1);
	// Si el siguiente no es caracter o '_' es el final de una variable
	else if (!ft_isalpha((*exp)->split[i][1]) && (*exp)->split[i][1] != '_')
	{
		if ((*exp)->split[i][1] == '?')
			return (0);
		return (1);
	}
	else
		return (0);
}

// (8 lineas)
// Esta funcion es la que busca el valor de la variable de entorno
// Hace la compracion entre $? o $#variable#
// Si no lo encuentra lo deja en string vacio
void	ft_variable_search(t_expand **exp, char **env, int i, int exit)
{
	// Si la variable "$?" ponemos la ultima salida, sino buscamos la variable
	if (!ft_strcmp((*exp)->tmp_var, "$?"))
		(*exp)->split[i] = ft_itoa(exit);
	else
		(*exp)->split[i] = ft_get_var_value(env, (*exp)->tmp_var + 1);
	// Si devuelve NULL, no la encontramos. 
	// Entonces solo ponemos un string vacio
	if (!(*exp)->split[i])
		(*exp)->split[i] = ft_strdup("");
	// Liberamos tmp_var
	free((*exp)->tmp_var);
	(*exp)->tmp_var = NULL;
}

// void	ft_aux_need_to_expand(t_token **tkn, int state)
// {
// 	int		i;

// 	i = 0;
// 	while ((*tkn)->content[i] && (*tkn)->expand == 0)
// 	{
// 		if (ft_is_quote((*tkn)->content[i]) == T_DQUOTE && !state)
// 			state = 2;
// 		else if (ft_is_quote((*tkn)->content[i]) == T_DQUOTE && state == 2)
// 			state = 0;
// 		else if (ft_is_quote((*tkn)->content[i]) == T_SQUOTE && !state)
// 			state = 1;
// 		else if (ft_is_quote((*tkn)->content[i]) == T_SQUOTE && state == 1)
// 			state = 0;
// 		else if ((*tkn)->content[i] == '$' && (*tkn)->content[i + 1] == '\0')		// 
// 			return ;																// 
// 		else if ((*tkn)->content[i] == '$' && state == 1)							// 
// 			return ;																//  esto es al pedo
// 		else if ((*tkn)->content[i] == '$' && state == 2)							// 
// 			(*tkn)->expand = 1;														// 
// 		else if ((*tkn)->content[i] == '$' && !state)		--------->				aqui esta el cambio
// 			(*tkn)->expand = 1;
// 		i++;
// 	}
// }

// En mimir_expander.c

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
		if ((*tkn)->content[i] == '$' && state != 1 && (*tkn)->content[i + 1])
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
