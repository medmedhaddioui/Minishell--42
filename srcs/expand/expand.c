/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noudrib <noudrib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 21:04:26 by mel-hadd          #+#    #+#             */
/*   Updated: 2024/08/06 11:12:06 by noudrib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*expand_env(char *value, t_list *env_head)
{
	int		i;
	char	*tmp;

	i = 0;
	if (value[i] == '?')
		return (ft_itoa_mini(g_var->exit_status));
	while (value[i] && check_lim(value[i]))
		i++;
	value = ft_substr_mini(value, 0, i);
	while (env_head)
	{
		tmp = get_name(env_head->content);
		if (!ft_strcmp(tmp, value))
			return (ft_strdup_mini(get_content(env_head->content)));
		env_head = env_head->next;
	}
	return (ft_strdup_mini(""));
}

char	*expand_data(char *value, int *i, char *result, t_list *env_head)
{
	int		index;
	char	*expand_value;

	index = *i;
	expand_value = expand_env(value + index, env_head);
	result = ft_strjoin_mini(result, expand_value);
	if (value[index] == '?' && ++*i)
		return (result);
	while (value[index] && check_lim(value[index]))
		index++;
	*i = index;
	return (result);
}

char	*expand_value(char *value, t_list *env_head)
{
	int		i;
	char	*result;

	i = 0;
	while (value[i] && value[i] != '$')
		i++;
	result = malloc(sizeof(char *) * (i + 1));
	if (!result)
		return (NULL);
	ft_lstadd_front(&g_var->collector, ft_lstnew(result));
	ft_memcpy(result, value, i);
	result[i] = '\0';
	while (value[i])
	{
		if (value[i] == '$' && (ft_isdigit(value[i + 1])
				|| ft_isalpha(value[i + 1]) || value[i + 1] == '?'))
		{
			if (ft_isdigit(value[++i]) && ++i)
				continue ;
			result = expand_data(value, &i, result, env_head);
		}
		else
			result = non_expand_value_join(value[i++], result);
	}
	return (result);
}

char	*setup_expand_value(char *value, t_list *env_head)
{
	int		i;
	char	*str;
	char	*res;

	i = 0;
	while (value && value[i] && value[i] != '\"' && value[i] != '\'')
		i++;
	if (value && !value[i])
		return (expand_value(value, env_head));
	res = ft_strdup_mini("");
	i = 0;
	while (value && value[i])
	{
		if (value[i] == '\'')
			str = handle_s_quote(value, &i);
		else if (value[i] == '\"')
			str = handle_d_quote(value, env_head, &i);
		else if (value[i])
			str = handle_no_quote(value, env_head, &i);
		res = ft_strjoin_mini(res, str);
	}
	return (res);
}

void	expanding(t_token **token_lst, t_list *env_head)
{
	t_token	*ptr;

	ptr = *token_lst;
	while (ptr)
	{
		ptr->value = setup_expand_value(ptr->value, env_head);
		ptr = ptr->next;
	}
}
