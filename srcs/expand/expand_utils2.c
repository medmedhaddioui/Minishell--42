/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noudrib <noudrib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 13:44:54 by mel-hadd          #+#    #+#             */
/*   Updated: 2024/07/30 18:06:35 by noudrib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*get_content(char *str)
{
	while (*str)
	{
		if (*str != '=')
			str++;
		else
			break ;
	}
	return (str + 1);
}

char	*non_expand_value_join(char c, char *result)
{
	char	*str;
	char	*res;

	str = malloc(sizeof(char *) * 2);
	if (!str)
		return (NULL);
	ft_lstadd_front(&g_var->collector, ft_lstnew(str));
	str[0] = c;
	str[1] = '\0';
	res = ft_strjoin_mini(result, str);
	return (res);
}
