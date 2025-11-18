/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_metachar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrosio <jbrosio@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 21:37:37 by jbrosio           #+#    #+#             */
/*   Updated: 2025/11/18 08:02:48 by jbrosio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int ft_is_metachar(char c)
{
    if (c == 34)
        return (T_DQUOTE);
    if (c == 39)
        return (T_SQUOTE);
    if (c == 60)
        return (T_REDIR_IN);
    if (c == 62)
        return (T_REDIR_OUT);
    if (c == 124)
        return (T_PIPE);
    return (0);
}
