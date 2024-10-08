/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noudrib <noudrib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 10:40:41 by mel-hadd          #+#    #+#             */
/*   Updated: 2024/08/01 21:55:18 by noudrib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_lim(char c)
{
	if (ft_isalpha(c) || ft_isdigit(c) || c == '_')
		return (1);
	return (0);
}

char	*handle_s_quote(char *value, int *i)
{
	int		index;
	int		len;
	char	*res;

	index = *i;
	len = 1;
	while (value[index + len] && value[index + len] != '\'')
		len++;
	if (value[index + len] == '\'')
		len++;
	res = malloc(sizeof(char *) * (len + 1));
	if (!res)
		return (NULL);
	ft_lstadd_front(&g_var->collector, ft_lstnew(res));
	ft_memcpy(res, value + index, len);
	res[len] = '\0';
	*i += len;
	return (res);
}

char	*handle_d_quote(char *value, t_list *env_head, int *i)
{
	int		index;
	int		len;
	char	*res;

	index = *i;
	len = 1;
	while (value[index + len] && value[index + len] != '\"')
		len++;
	if (value[index + len] == '\"')
		len++;
	res = malloc(sizeof(char *) * (len + 1));
	if (!res)
		return (NULL);
	ft_lstadd_front(&g_var->collector, ft_lstnew(res));
	ft_memcpy(res, value + index, len);
	res[len] = '\0';
	res = expand_value(res, env_head);
	*i += len;
	return (res);
}

char	*handle_no_quote(char *value, t_list *env_head, int *i)
{
	int		index;
	int		len;
	char	*res;

	index = *i;
	len = 1;
	while (value[index + len] && value[index + len] != '\"'
		&& value[index + len] != '\'')
		len++;
	res = malloc(sizeof(char *) * (len + 1));
	if (!res)
		return (NULL);
	ft_lstadd_front(&g_var->collector, ft_lstnew(res));
	ft_memcpy(res, value + index, len);
	res[len] = '\0';
	if (res[0] == '$' && res[1] == '\0')
		res = ft_strdup_mini("");
	else
		res = expand_value(res, env_head);
	*i += len;
	return (res);
}
