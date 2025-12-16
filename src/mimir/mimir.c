#include "minishell.h"

/* ====================== */
/* ======== mimir ======= */
/* ====================== */

void	ft_find_dollar(t_expand **exp, char *s)
{
	int	i;
	int	dollar;

	i = 0;
	dollar = 0;
	while (s[i])
	{
		if (s[i] == '$' && !dollar)
			dollar = 1;
		else if (s[i] == '$' && dollar)
		{
			(*exp)->dollar = 1;
			break ;
		}
		i++;
	}
}

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

// int	ft_find_limit(t_expand **exp, char *s)
// {
// 	int	i;

// 	i = 0;
// 	(*exp)->limit = 0;
// 	while (s[i])
// 	{
// 		if (s[i] == '$' && s[i + 1])
// 		{
// 			while (s[++i])
// 			{
// 				if (!ft_isalnum(s[i]) && s[i] != '_')
// 				{
// 					(*exp)->limit = 1;
// 					return (i);
// 				}
// 			}
// 		}
// 		i++;
// 	}
// 	return (i);
// }

// int	ft_limit_dollar_expand(char	*s)
// {
// 	int		i;
// 	int		limit;

// 	i = 0;
// 	limit = 0;
// 	while (s[i])
// 	{
// 		if (s[i] == '$' && s[i + 1] && s[i + 1] != '/' && limit)
// 			limit = 0;
// 		else if (s[i] == '$' && s[i + 1] && s[i + 1] == '/' && !limit)
// 			limit = 1;
// 		else if (s[i] == '/' && s[i + 1] && s[i + 1] == '$' && limit)
// 			limit = 0;
// 		i++;
// 	}
// 	if (limit)
// 		return (1);
// 	else
// 		return (0);
// }

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

// int	ft_process_var_aux(t_expand **exp, char **env, int exit)
// {
// 	int	i;

// 	if ((*exp)->limit)
// 	{
// 		i = ft_find_limit(exp, (*exp)->var);
// 		(*exp)->tmp_var = ft_substr((*exp)->var, 0, i);
// 		if (!(*exp)->tmp_var)
// 		{
// 			printf("1\n");
// 			return (ft_pd_error(ERR_MALLOC, NULL, 12));
// 		}
// 		(*exp)->aux = ft_substr((*exp)->var, i, ft_strlen((*exp)->var + i));
// 		if (!(*exp)->aux)
// 		{
// 			printf("2\n");
// 			return (ft_pd_error(ERR_MALLOC, NULL, 12));
// 		}
// 		free((*exp)->var);
// 		(*exp)->var = NULL;
// 		if (!ft_strcmp((*exp)->var, "$?"))
// 			(*exp)->var = ft_itoa(exit);
// 		else
// 		{
// 			printf("tmp_var -> %s\n", (*exp)->tmp_var);
// 			(*exp)->var = ft_get_var_value(env, (*exp)->tmp_var + 1);
// 		}
// 		free((*exp)->tmp_var);
// 		(*exp)->tmp_var = NULL;
// 		if (!(*exp)->var)
// 		{
// 			printf("aux -> %s\n", (*exp)->aux);
// 			(*exp)->tmp_var = ft_strdup((*exp)->aux);
// 		}
// 		else
// 			(*exp)->tmp_var = ft_strjoin((*exp)->var, (*exp)->aux);
// 		if (!(*exp)->tmp_var)
// 		{
// 			printf("4\n");
// 			return (ft_pd_error(ERR_MALLOC, NULL, 12));
// 		}
// 	}
// 	else
// 	{
// 		if (!ft_strcmp((*exp)->var, "$?"))
// 			(*exp)->tmp_var = ft_itoa(exit);
// 		else
// 			(*exp)->tmp_var = ft_get_var_value(env, (*exp)->tmp_var + 1);
// 	}
// 	return (0);
// }

int	ft_process_var(t_expand **exp, char **env, int exit, char *cont)
{
	int	i;
	int	x;

	// --- PASO 1: PREPARACIÓN DE VAR (INPUT) ---
	// Decidimos si recortamos comillas o duplicamos todo
	if ((*exp)->init_quote && (*exp)->end_quote)
		(*exp)->var = ft_strtrim(cont + (*exp)->s_init, (*exp)->end_quote);
	else
		(*exp)->var = ft_strdup(cont);
	if (!(*exp)->var)
		return (ft_pd_error(ERR_MALLOC, NULL, 12));
	// --- PASO 2: SPLIT ---
	(*exp)->split = ft_split_dollar((*exp)->var, '$');
	if (!(*exp)->split)
		return (ft_pd_error(ERR_MALLOC, NULL, 12));
	// --- PASO 3: EXPANSIÓN (Fragmento por fragmento) ---
	i = 0;
	while ((*exp)->split[i])
	{
		// Si NO es una variable (no empieza por $ o es solo "$"), pasamos
		if ((*exp)->split[i][0] != '$' || ft_strlen((*exp)->split[i]) == 1)
		{
			i++;
			continue ;
		}
		// Calculamos dónde termina el nombre de la variable
		x = ft_find_limit(exp, (*exp)->split[i], 0);
		// A. Extraemos el NOMBRE de la variable en tmp_var (ej: "$USER")
		(*exp)->tmp_var = ft_substr((*exp)->split[i], 0, x);
		if (!(*exp)->tmp_var)
			return (ft_pd_error(ERR_MALLOC, NULL, 12));
		// B. Extraemos el SUFIJO en aux (ej: "/bin") si existe límite
		if ((*exp)->limit)
			(*exp)->aux = ft_substr((*exp)->split[i], x, ft_strlen((*exp)->split[i]));
		else
			(*exp)->aux = NULL;
		// C. Obtenemos el VALOR y reemplazamos split[i]
		// Primero liberamos el string original "$USER/bin"
		free((*exp)->split[i]);
		(*exp)->split[i] = NULL;
		if (!ft_strcmp((*exp)->tmp_var, "$?"))
			(*exp)->split[i] = ft_itoa(exit);
		else
			(*exp)->split[i] = ft_get_var_value(env, (*exp)->tmp_var + 1);
		// Si la variable no existe, strdup vacío para evitar NULLs
		if (!(*exp)->split[i])
			(*exp)->split[i] = ft_strdup("");
		// Liberamos el nombre temporal ("$USER") ya que ya tenemos el valor
		free((*exp)->tmp_var);
		(*exp)->tmp_var = NULL;
		// D. Si había SUFIJO, lo unimos al valor recuperado
		if ((*exp)->aux)
		{
			// Unimos VALOR + SUFIJO en tmp_var
			(*exp)->tmp_var = ft_strjoin((*exp)->split[i], (*exp)->aux);
			// Limpieza
			free((*exp)->split[i]); // Liberamos valor solo
			free((*exp)->aux);	  // Liberamos sufijo solo
			(*exp)->aux = NULL;
			// Guardamos el resultado combinado de vuelta en el array
			(*exp)->split[i] = (*exp)->tmp_var; 
			// Nota: No ponemos tmp_var a NULL aquí porque split[i] apunta a lo mismo, 
			// simplemente lo reutilizaremos en la siguiente vuelta.
		}
		i++;
	}
	// --- PASO 4: RECONSTRUCCIÓN (Unir todo el array en tmp_var) ---
	// Usaremos aux como acumulador
	if ((*exp)->aux) 
		free((*exp)->aux); // Por seguridad
	(*exp)->aux = ft_strdup("");
	i = 0;
	while ((*exp)->split[i])
	{
		// Unimos lo que llevamos (aux) + el nuevo fragmento (split[i])
		(*exp)->tmp_var = ft_strjoin((*exp)->aux, (*exp)->split[i]);
		
		free((*exp)->aux);	  // Liberamos el acumulado viejo
		(*exp)->aux = (*exp)->tmp_var; // Actualizamos el acumulador
		i++;
	}
	// El resultado final está en aux y tmp_var (apuntan a lo mismo)
	// Pero por claridad y seguridad de la estructura:
	// La función debe dejar el resultado en tmp_var.
		
	// (*exp)->tmp_var YA tiene el resultado correcto del último strjoin.
	// (*exp)->aux apunta a lo mismo. Ponemos aux a NULL para no tener doble free luego.
	(*exp)->aux = NULL;
	// Limpieza final de var (ya no se necesita el input original)
	if ((*exp)->var)
	{
		free((*exp)->var);
		(*exp)->var = NULL;
	}
	// Recuerda liberar la matriz (*exp)->split fuera o aquí si tienes ft_free_matrix
	// ft_free_matrix((*exp)->split); 
	return (0);
}

// TERCERA int	ft_process_var(t_expand **exp, char **env, int exit, char *cont)
// {
// 	int		init;
// 	int		end;
// 	int		i;
// 	int		x;
// 	char	*(expanded_part);

// 	init = (*exp)->s_init;
// 	end = (*exp)->s_end;
// 	if ((*exp)->init_quote && (*exp)->end_quote)
// 		(*exp)->var = ft_strtrim(cont + init, (*exp)->end_quote);
// 	else
// 		(*exp)->var = ft_strdup(cont);
// 	if (!(*exp)->var)
// 		return (ft_pd_error(ERR_MALLOC, NULL, 12));
// 	(*exp)->split = ft_split_dollar((*exp)->var, '$');
// 	if (!(*exp)->split)
// 		return (ft_pd_error(ERR_MALLOC, NULL, 12));
// 	i = 0;
// 	while ((*exp)->split[i])
// 	{
// 		// 1. Casos para NO expandir (texto normal o '$' solo)
// 		if ((*exp)->split[i][0] != '$' || ft_strlen((*exp)->split[i]) == 1)
// 		{
// 			i++;
// 			continue ;
// 		}
// 		// 2. Lógica de expansión
// 		x = ft_find_limit(exp, (*exp)->split[i], 0);
// 		// A. Extraemos el nombre de la variable ($VAR)
// 		(*exp)->tmp_var = ft_substr((*exp)->split[i], 0, x);
// 		// B. Obtenemos su valor
// 		if (!ft_strcmp((*exp)->tmp_var, "$?"))
// 			(expanded_part) = ft_itoa(exit);
// 		else
// 			(expanded_part) = ft_get_var_value(env, (*exp)->tmp_var + 1);
// 		// Si ft_get_var_value devuelve NULL, lo tratamos como cadena vacía
// 		if (!(expanded_part))
// 			(expanded_part) = ft_strdup("");
// 		free((*exp)->tmp_var); // Liberamos "$VAR" temporal
// 		// C. Manejo del sufijo (si existe)
// 		if ((*exp)->limit)
// 		{
// 			(*exp)->aux = ft_substr((*exp)->split[i], x, ft_strlen((*exp)->split[i] + x));
// 			free((*exp)->split[i]); // Liberamos el original "$VAR/texto"
// 			(*exp)->split[i] = NULL;
// 			// Unimos Valor + Sufijo
// 			(*exp)->split[i] = ft_strjoin((expanded_part), (*exp)->aux);
// 			free((expanded_part));
// 			(expanded_part) = NULL;
// 			free((*exp)->aux);
// 			(*exp)->aux = NULL;
// 		}
// 		else
// 		{
// 			// Sin sufijo, simplemente reemplazamos
// 			free((*exp)->split[i]);
// 			(*exp)->split[i] = (expanded_part);
// 		}
// 		i++;
// 	}
// 	i = 0;
// 	if ((*exp)->aux)
// 		free((*exp)->aux);
// 	(*exp)->aux = ft_strdup("");
// 	while ((*exp)->split[i])
// 	{
// 		char *temp = ft_strjoin((*exp)->aux, (*exp)->split[i]);
// 		free((*exp)->aux);
// 		(*exp)->aux = temp;
// 		i++;
// 	}
// 	(*exp)->tmp_var = ft_strdup((*exp)->aux);
// 	// Recuerda liberar (*exp)->split y sus contenidos al final o usar una función ft_free_matrix
// 	return (0);
// }

//SEGUNDA int	ft_process_var(t_expand **exp, char **env, int exit, char *cont)
// {
// 	int	init;
// 	int	end;
// 	int			i;
// 	int			j;
// 	int			x;

// 	init = (*exp)->s_init;
// 	end = (*exp)->s_end;
// 	j = 1;
// 	if ((*exp)->init_quote && (*exp)->end_quote)
// 		(*exp)->var = ft_strtrim(cont + init, (*exp)->end_quote);
// 	else
// 		(*exp)->var = ft_strdup(cont);
// 	if (!(*exp)->var)
// 		return (ft_pd_error(ERR_MALLOC, NULL, 12));
// 	else
// 	{
// 		// ft_find_limit(exp, (*exp)->var, 0);
// 		(*exp)->split = ft_split_dollar((*exp)->var, '$');
// 		if (!(*exp)->split)
// 			return (ft_pd_error(ERR_MALLOC, NULL, 12));
// 		i = 0;
// 		while ((*exp)->split[i])
// 		{
// 			printf("split 0 -> %s\n", (*exp)->split[i]);
// 			if ((*exp)->split[i][0] != '$')
// 				i++;
// 			else if ((*exp)->split[i][1] && (*exp)->split[i][1] == '/')
// 				i++;
// 			else if (ft_strlen((*exp)->split[i]) == 1)
// 				i++;
// 			else
// 			{
// 				x = ft_find_limit(exp, (*exp)->split[i], 0);
// 				if ((*exp)->limit)
// 				{
// 					printf("if\n");
// 					(*exp)->tmp_var = ft_substr((*exp)->split[i], 0, x);
// 					if (!(*exp)->tmp_var)
// 					{
// 						printf("1\n");
// 						return (ft_pd_error(ERR_MALLOC, NULL, 12));
// 					}
// 					(*exp)->aux = ft_substr((*exp)->split[i], x, ft_strlen((*exp)->split[i] + x));
// 					// printf("aux -> %s\n", (*exp)->aux);
// 					if (!(*exp)->aux)
// 					{
// 						printf("2\n");
// 						return (ft_pd_error(ERR_MALLOC, NULL, 12));
// 					}
// 					free((*exp)->split[i]);
// 					(*exp)->split[i] = NULL;
// 					printf("tmp_var if -> %s\n", (*exp)->tmp_var);
// 					if (!ft_strcmp((*exp)->split[i], "$?"))
// 						(*exp)->split[i] = ft_itoa(exit);
// 					else
// 						(*exp)->split[i] = ft_get_var_value(env, (*exp)->tmp_var + 1);
// 					free((*exp)->tmp_var);
// 					(*exp)->tmp_var = NULL;
// 					if (!(*exp)->split[i])
// 					{
// 						(*exp)->split[i] = ft_strdup((*exp)->aux);
// 					}
// 					else
// 					{
// 						// printf("split -> %s\n", (*exp)->split[i]);
// 						(*exp)->tmp_var = ft_strjoin((*exp)->split[i], (*exp)->aux);
// 						// printf("tmp_var split -> %s\n", (*exp)->tmp_var);
// 						free((*exp)->split[i]);
// 						(*exp)->split[i] = NULL;
// 						(*exp)->split[i] = ft_strdup((*exp)->tmp_var);
// 						free((*exp)->tmp_var);
// 						(*exp)->tmp_var = NULL;
// 						free((*exp)->aux);
// 						(*exp)->aux = NULL;
// 					}
// 					if (!(*exp)->split[i])
// 					{
// 						printf("3\n");
// 						return (ft_pd_error(ERR_MALLOC, NULL, 12));
// 					}
// 				}
// 				else
// 				{
// 					// printf("split 1 -> %s\n", (*exp)->split[i]);
// 					if (!ft_strcmp((*exp)->split[i], "$?"))
// 						(*exp)->tmp_var = ft_itoa(exit);
// 					else
// 						(*exp)->tmp_var = ft_get_var_value(env, (*exp)->split[i] + 1);
// 					printf("tmp_var else -> %s\n", (*exp)->tmp_var);
// 					(*exp)->split[i] = NULL;
// 					if ((*exp)->tmp_var)
// 						(*exp)->split[i] = ft_strdup((*exp)->tmp_var);
// 					// if (!(*exp)->split[i])
// 					// {
// 					// 	printf("4\n");
// 					// 	return (ft_pd_error(ERR_MALLOC, NULL, 12));
// 					// }
// 					if ((*exp)->tmp_var)
// 					{
// 						free((*exp)->tmp_var);
// 						(*exp)->tmp_var = NULL;
// 					}
// 				}
// 				printf("split -> %s\n", (*exp)->split[i]);
// 				j++;
// 				i++;
// 			}
// 		}
// 		if ((*exp)->aux)
// 		{
// 			free((*exp)->aux);
// 			(*exp)->aux = NULL;
// 		}
// 		// (*exp)->aux = ft_strdup((*exp)->split[0]);
// 		// printf("aux -> %s\n", (*exp)->aux);
// 		// if (!(*exp)->aux)
// 		// {
// 		// 	printf("5\n");
// 		// 	return (ft_pd_error(ERR_MALLOC, NULL, 12));
// 		// }
// 		i = 0;
// 		// aa/$/aa$aa$HOME$aa.$aaa
// 		// printf("j = %d\n", j);
// 		while (i < j)
// 		{
// 			printf("i = %d\n", i);
// 			printf("split 2 -> %s\n", (*exp)->split[i]);
// 			if ((*exp)->var)
// 				free((*exp)->var);
// 			(*exp)->var = NULL;
// 			if ((*exp)->split[i])
// 			{
// 				if (!(*exp)->aux)
// 					(*exp)->var = ft_strdup((*exp)->split[i]);
// 				else
// 					(*exp)->var = ft_strjoin((*exp)->aux, (*exp)->split[i]);
// 				free((*exp)->aux);
// 				(*exp)->aux = NULL;
// 				(*exp)->aux = ft_strdup((*exp)->var);
// 				if (!(*exp)->aux)
// 					return (ft_pd_error(ERR_MALLOC, NULL, 12));
// 				i++;
// 			}
// 			else
// 				i++;
// 		}
// 		(*exp)->tmp_var = ft_strdup((*exp)->aux);
// 		// if (!(*exp)->tmp_var)
// 		// {
// 		// 	printf("7\n");
// 		// 	return (ft_pd_error(ERR_MALLOC, NULL, 12));
// 		// }
// 	}
// 	if ((*exp)->var)
// 		free((*exp)->var);
// 	return (0);
// }

// $aa$HOME
// $HOME$HOME

// int	ft_process_var(t_expand **exp, char **env, int exit, char *cont)
// {
// 	int	init;
// 	int	end;
// 	int			i;
// 	int			j;
// 	int			x;
// int			dollar;

// 	init = (*exp)->s_init;
// 	end = (*exp)->s_end;
// 	if ((*exp)->init_quote && (*exp)->end_quote)
// 		(*exp)->var = ft_strtrim(cont + init, (*exp)->end_quote);
// 	else
// 		(*exp)->var = ft_strdup(cont);
// 	if (!(*exp)->var)
// 		return (ft_pd_error(ERR_MALLOC, NULL, 12));
// 	else
// 	{
// 		i = 0;
// 		dollar = 0;
// 		while ((*exp)->var[i])
// 		{
// 			if ((*exp)->var[i] == '$' && !dollar)
// 				dollar = 1;
// 			else if ((*exp)->var[i] == '$' && dollar)
// 			{
// 				(*exp)->dollar = 1;
// 				break ;
// 			}
// 			i++;
// 		}
// 		i = 0;
// 		while ((*exp)->var[i])
// 		{
// 			if ((*exp)->var[i] == '/')
// 			{
// 				(*exp)->limit = 1;
// 				break ;
// 			}
// 			i++;
// 		}
// 		if ((*exp)->dollar)
// 		{
// 			(*exp)->split = ft_split_dollar((*exp)->var, '$');
// 			if (!(*exp)->split)
// 				return (ft_pd_error(ERR_MALLOC, NULL, 12));
// 			i = 0;
// 			while ((*exp)->split[i])
// 			{
// 				if ((*exp)->split[i][1] && (*exp)->split[i][1] == '/')
// 					i++;
// 				else if (ft_strlen((*exp)->split[i]) == 1)
// 					i++;
// 				else
// 				{
// 					j = 0;
// 					x = 0;
// 					(*exp)->limit = 0;
// 					while ((*exp)->split[i][x])
// 					{
// 						if ((*exp)->split[i][x] == '/')
// 						{
// 							(*exp)->limit = 1;
// 							break ;
// 						}
// 						x++;
// 					}
// 					if ((*exp)->limit)
// 					{
// 						(*exp)->tmp_var = ft_substr((*exp)->split[i], 0, x);
// 						if (!(*exp)->tmp_var)
// 							return (ft_pd_error(ERR_MALLOC, NULL, 12));
// 						(*exp)->aux = ft_substr((*exp)->split[i], x, ft_strlen((*exp)->split[i] + x));
// 						if (!(*exp)->aux)
// 							return (ft_pd_error(ERR_MALLOC, NULL, 12));
// 						free((*exp)->split[i]);
// 						(*exp)->split[i] = NULL;
// 						if (!ft_strcmp((*exp)->split[i], "$?"))
// 							(*exp)->split[i] = ft_itoa(exit);
// 						else
// 							(*exp)->split[i] = ft_get_var_value(env, (*exp)->tmp_var + 1);
// 						if (!(*exp)->split[i])
// 							return (ft_pd_error(ERR_MALLOC, NULL, 12));
// 						free((*exp)->tmp_var);
// 						(*exp)->tmp_var = NULL;
// 						if (!(*exp)->split[i])
// 							(*exp)->split[i] = ft_strdup((*exp)->aux);
// 						else
// 						{
// 							(*exp)->tmp_var = ft_strjoin((*exp)->split[i], (*exp)->aux);
// 							free((*exp)->split[i]);
// 							(*exp)->split[i] = NULL;
// 							(*exp)->split[i] = ft_strdup((*exp)->tmp_var);
// 							free((*exp)->tmp_var);
// 							(*exp)->tmp_var = NULL;
// 							free((*exp)->aux);
// 							(*exp)->aux = NULL;
// 						}
// 						if (!(*exp)->split[i])
// 							return (ft_pd_error(ERR_MALLOC, NULL, 12));
// 					}
// 					else
// 					{
// 						if (!ft_strcmp((*exp)->split[i], "$?"))
// 							(*exp)->tmp_var = ft_itoa(exit);
// 						else
// 							(*exp)->tmp_var = ft_get_var_value(env, (*exp)->split[i] + 1);
// 						if (!(*exp)->tmp_var)
// 							return (ft_pd_error(ERR_MALLOC, NULL, 12));
// 						if ((*exp)->split[i])
// 							free((*exp)->split[i]);
// 						(*exp)->split[i] = NULL;
// 						(*exp)->split[i] = ft_strdup((*exp)->tmp_var);
// 						if (!(*exp)->split[i])
// 							return (ft_pd_error(ERR_MALLOC, NULL, 12));
// 						if ((*exp)->tmp_var)
// 						{
// 							free((*exp)->tmp_var);
// 							(*exp)->tmp_var = NULL;
// 						}
// 					}
// 					i++;
// 				}
// 			}
// 			(*exp)->aux = ft_strdup((*exp)->split[0]);
// 			if (!(*exp)->aux)
// 				return (ft_pd_error(ERR_MALLOC, NULL, 12));
// 			i = 1;
// 			while ((*exp)->split[i])
// 			{
// 				if ((*exp)->var)
// 					free((*exp)->var);
// 				(*exp)->var = NULL;
// 				(*exp)->var = ft_strjoin((*exp)->aux, (*exp)->split[i]);
// 				free((*exp)->aux);
// 				(*exp)->aux = NULL;
// 				(*exp)->aux = ft_strdup((*exp)->var);
// 				if (!(*exp)->aux)
// 					return (ft_pd_error(ERR_MALLOC, NULL, 12));
// 				i++;
// 			}
// 			(*exp)->tmp_var = ft_strdup((*exp)->aux);
// 			if (!(*exp)->tmp_var)
// 				return (ft_pd_error(ERR_MALLOC, NULL, 12));
// 		}
// 		else
// 		{
// 			i = 0;
// 			if ((*exp)->limit)
// 				ft_process_var_aux(exp, env, exit);
// 			else
// 			{
// 				if (!ft_strcmp((*exp)->var, "$?"))
// 					(*exp)->tmp_var = ft_itoa(exit);
// 				else
// 					(*exp)->tmp_var = ft_get_var_value(env, (*exp)->var + 1);
// 				if (!(*exp)->tmp_var)
// 					return (ft_pd_error(ERR_MALLOC, NULL, 12));
// 			}
// 		}
// 	}
// 	if ((*exp)->var)
// 		free((*exp)->var);
// 	return (0);
// }

// int	ft_check_two_var(t_token **token, t_expand **exp)
// {
// 	int			i;
// 	int			dollar;

// 	i = 0;
// 	while ((*token)->content[i])
// 	{
// 		if ((*token)->content[i] == '$' && !dollar)
// 			dollar = 1;
// 		if ((*token)->content[i] == '$' && dollar)
// 		{
// 			(*exp)->dollar = 1;
// 			break ;
// 		}
// 		i++;
// 	}
// 	i = 0;
// 	while ((*token)->content[i])
// 	{
// 		if ((*token)->content[i] == '/')
// 		{
// 			(*exp)->limit = 1;
// 			break ;
// 		}
// 		i++;
// 	}
// 	if ((*exp)->dollar)
// 	{
// 		(*exp)->split = ft_split_dollar((*token)->content, '$');
// 		if (!(*exp)->split)
// 			return (-1);
// 		// hacemos cosas
// 	}
// 	else
// 	{
// 		i = 0;
// 		if ((*exp)->limit)
// 		{
// 			while ((*token)->content[i])
// 			{
// 				if ((*token)->content[i] == '/')
// 					break ;
// 				i++;
// 			}
// 		}
// 		return (1);
// 	}
// 	return (0);
// }

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