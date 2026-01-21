/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrosio <jbrosio@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 19:09:39 by jbrosio           #+#    #+#             */
/*   Updated: 2026/01/15 19:09:40 by jbrosio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ============================ */
/* ======= parse_utils ======== */
/* ============================ */

char	ft_quote_track(char c, char quote)
{
	if (!quote && (c == '\'' || c == '\"'))
		quote = c;
	else if (quote && c == quote)
		quote = 0;
	return (quote);
}

int	ft_redir_bucle_check(char *s, char quote)
{
	int		i;

	i = 0;
	while (s[i])
	{
		quote = ft_quote_track(s[i], quote);
		if ((s[i] == '>' || s[i] == '<') && !quote)
		{
			if (s[i] == '>' && s[i + 1] == '>')
				i += 2;
			else if (s[i] == '<' && s[i + 1] == '<')
				i += 2;
			else
				i++;
			while (s[i] && s[i] <= 32)
				i++;
			if (s[i] == '>' || s[i] == '<' || s[i] == '|' || s[i] == '\0')
				return (1);
			continue ;
		}
		i++;
	}
	return (0);
}
