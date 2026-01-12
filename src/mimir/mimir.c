#include "minishell.h"

/* ====================== */
/* ======== mimir ======= */
/* ====================== */

// // echo "hola ""$USER '$USER'"   '"USER"'

// // (23 lineas)
// // Esta funcion vuelve a poner en el imput todos los cambios
// // Va haciendo un join de cada string guardado en el split,
// // en el caso de que no haya guardado nada porque no hubo valor dentro de las
// // variables de entorno (previamente se guardo como string vacio) asi que
// // en el join simplemente pasara de largo.
// int	ft_rebuild_var(t_expand **exp)
// {
// 	int	i;

// 	// Limpiamos aux por las dudas de que se haya quedado con algo
// 	if ((*exp)->aux)
// 		free((*exp)->aux);
// 	// Inicializamos la variable a un string vacio
// 	(*exp)->aux = ft_strdup("");
// 	if (!(*exp)->aux) // Protegemos por si falla
// 		return (ft_pd_error(ERR_MALLOC, NULL, 12));
// 	i = 0;
// 	while ((*exp)->split[i])
// 	{
// 		// Vamos haciendo el join de aux y lo que haya en la posicion de split
// 		// Metiendolo en tmp_var
// 		(*exp)->tmp_var = ft_strjoin((*exp)->aux, (*exp)->split[i]);
// 		if (!(*exp)->tmp_var)
// 			return (ft_pd_error(ERR_MALLOC, NULL, 12));
// 		// Liberamos aux para poder apuntarle su nuevo valor
// 		free((*exp)->aux);
// 		// Direccionamos lo que hay en tmp_var a aux para volver a agregarlo
// 		// en la siguiente vuelta
// 		(*exp)->aux = (*exp)->tmp_var;
// 		i++;
// 	}
// 	// Ultimas limpiezas
// 	(*exp)->aux = NULL;
// 	if ((*exp)->var)
// 	{
// 		free((*exp)->var);
// 		(*exp)->var = NULL;
// 	}
// 	return (0);
// }

// // EXPANCION DE DOMINO (24 lineas)
// // Esta funcion es la que separa todo el input para poder guardar el sobrante
// // Si existe sobrante lo guarda y lo une al final de la busqueda del valor
// // En el caso de que no existe simplemente busca la variable y guarda su valor
// int	ft_domain_expansion(t_expand **exp, int i, char **env, int exit)
// {
// 	int	str_size;
// 	int	x;
// //  aa.
// //  $HOME/puto
// 	// Sacamos el size del string que esta en la posicion 'i' del split
// 	str_size = ft_strlen((*exp)->split[i]);
// 	// Calculamos donde termina la variable completa
// 	x = ft_find_limit(exp, (*exp)->split[i], 0);
// 	// Guardamos la variable. Ej: $HOME
// 	(*exp)->tmp_var = ft_substr((*exp)->split[i], 0, x);
// 	if (!(*exp)->tmp_var)
// 		return (ft_pd_error(ERR_MALLOC, NULL, 12));
// 	// Si la flag LIMIT esta activa guardamos ese sobrante en aux.
// 	// Ej: $HOME.aa = [ .aa ] | sino solo ponemos a NULL
// 	// echo $?hcudshfuewrf ew  wr 4ew""""
// 	if ((*exp)->limit)
// 		(*exp)->aux = ft_substr((*exp)->split[i], x, str_size);
// 	else
// 		(*exp)->aux = NULL;
// 	free((*exp)->split[i]);
// 	(*exp)->split[i] = NULL;
// 	// - Buscamos la variable -
// 	ft_variable_search(exp, env, i, exit);
// 	// Si existe un sobrante lo guardamos
// 	if ((*exp)->aux)
// 	{
// 		// Hacemos un join con lo que encontramos de variable y lo guardamos
// 		// en tmp_var
// 		(*exp)->tmp_var = ft_strjoin((*exp)->split[i], (*exp)->aux);
// 		// Liberamos la posicion del split y tambien la variable aux
// 		free((*exp)->split[i]);
// 		free((*exp)->aux);
// 		(*exp)->aux = NULL;
// 		// Apuntamos la posicion del split a nuestro nuevo resultado
// 		(*exp)->split[i] = (*exp)->tmp_var;
// 	}
// 	return (0);
// }

// // 			LA MARAVILLOSA - LA RICARDA - LA MANOSEABLE - LA JUGUETONA 
// // 					LA DULSONA - LA JUGOSA - LA POTENTE

// int	ft_process_var(t_expand **exp, char **env, int exit, char *cont)
// {
// 	int		i;

// 	// 				--- LIMPIEZA DE VAR (INPUT) ---
// 	// si existen comillas recortamos sino duplicamos el input exacto
// 	if ((*exp)->init_quote && (*exp)->end_quote)
// 		(*exp)->var = ft_strtrim(cont + (*exp)->s_init, (*exp)->end_quote);
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
// // 	primer corte (funcion para validar el string)
// // 			       V  V  V
// 		if (ft_expander_validator(exp, i, ft_strlen((*exp)->split[i])))
// 			i++;
// 		else
// 		{
// // 	segundo corte (expancion de PUTO dominio)
// // 				   V  V  V
// 			ft_domain_expansion(exp, i, env, exit);
// 			i++;
// 		}
// 	}
// //	tercer corte (RE-construccion de variable)
// //		  V  V  V
// 	ft_rebuild_var(exp);
// 	return (0);
// }

// int	ft_expand_var(t_token **token, char **env, int exit_status)
// {
// 	t_expand	*exp;

// 	exp = ft_init_expanders();
// 	if (ft_handle_init_quote(&exp, (*token)->content))
// 		return (ft_clean_expanders(&exp));
// 	if (ft_handle_end_quote(&exp, (*token)->content))
// 		return (ft_clean_expanders(&exp));
// 	if (ft_process_var(&exp, env, exit_status, (*token)->content))
// 		return (ft_clean_expanders(&exp));
// 	if (!exp->tmp_var)
// 	{
// 		if (ft_no_found_var(&exp, token))
// 			return (ft_clean_expanders(&exp));
// 	}
// 	else
// 	{
// 		if (ft_found_var(&exp, token))
// 			return (ft_clean_expanders(&exp));
// 	}
// 	ft_clean_expanders(&exp);
// 	return (0);
// }


/*===========================================================================*/
/*===========================================================================*/

/* Maneja la lógica de encontrar el valor y avanzar el índice */
/* Usa tu ft_find_limit y ft_get_var_value existentes */
static int	ft_append_val(char **res, char *str, int i, char **env, int exit_s)
{
	int		len;
	char	*var_name;
	char	*val;

	if (str[i + 1] == '?')
	{
		ft_add_str(res, ft_itoa(exit_s));
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
	val = ft_get_var_value(env, var_name);
	ft_add_str(res, val);
	free(var_name);
	free(val);
	return (i + 1 + len);
}

/* State 0: Nada
   State 1: Comilla Simple ' (No expande nada)
   State 2: Comilla Doble " (Expande $)
*/
char	*ft_process_new_expansion(char *str, char **env, int exit_status)
{
	char	*res;
	int		i;
	int		state;

	res = ft_strdup("");
	i = 0;
	state = 0;
	while (str[i])
	{
		if (str[i] == '\'' && state == 0)
			state = 1;
		else if (str[i] == '\'' && state == 1)
			state = 0;
		else if (str[i] == '\"' && state == 0)
			state = 2;
		else if (str[i] == '\"' && state == 2)
			state = 0;
		if (str[i] == '$' && state != 1 && (ft_isalnum(str[i + 1])
				|| str[i + 1] == '_' || str[i + 1] == '?'))
			i = ft_append_val(&res, str, i, env, exit_status);
		else
		{
			ft_add_char(&res, str[i]);
			i++;
		}
	}
	return (res);
}

int	ft_expand_var(t_token **token, char **env, int exit_status)
{
	char	*new_content;

	if (!token || !*token || !(*token)->content)
		return (0);
	new_content = ft_process_new_expansion((*token)->content, env, exit_status);
	if (!new_content)
		return (ft_pd_error(ERR_MALLOC, NULL, 12));
	free((*token)->content);
	(*token)->content = new_content;
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
