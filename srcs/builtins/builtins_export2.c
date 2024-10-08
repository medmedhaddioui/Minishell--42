/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noudrib <noudrib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 13:11:37 by mel-hadd          #+#    #+#             */
/*   Updated: 2024/08/01 12:43:59 by noudrib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	env_existing_check(t_list **head, char *str, int sign_index)
{
	t_list	*ptr;

	ptr = *head;
	while (ptr)
	{
		if (sign_index && !ft_strcmp(get_name(ptr->content), get_name(str)))
			return (1);
		if (!sign_index && !ft_strcmp(get_name(ptr->content), str))
			return (1);
		ptr = ptr->next;
	}
	return (0);
}

char	*plus_check(char *env_var, char *str)
{
	int	i;
	int	add;
	int	index;

	i = 0;
	add = 2;
	index = equal_index(env_var);
	if (!index)
		add = 1;
	while (str[i])
	{
		if (str[i] == '+' && str[i + 1] == '=')
			return (ft_strjoin_mini(env_var, str + i + add));
		i++;
	}
	return (str);
}

char	*handle_plus_sign(char *s)
{
	int		i;
	int		len;
	char	*res;
	char	*tmp;

	i = 0;
	while (s[i])
	{
		if (s[i] == '+' && s[i + 1] == '=')
			break ;
		i++;
	}
	if (!s[i])
		return (s);
	tmp = ft_substr_mini(s, 0, i);
	len = ft_strlen(s) - i;
	res = ft_substr_mini(s, i + 1, len);
	res = ft_strjoin_mini(tmp, res);
	return (res);
}

char	*handle_2(char *value)
{
	int	i;

	i = -1;
	while (value[++i])
	{
		if (value[i] == '=' || (value[i] == '+' && value[i + 1] == '='))
			break ;
		if (value[i] >= 32 && value[i] <= 47)
		{
			ft_putstr_fd("minishell: export: ", 2);
			ft_putstr_fd(value, 2);
			ft_putstr_fd(": not a valid identifier\n", 2);
			g_var->exit_status = 1;
			return (NULL);
		}
	}
	return (value);
}

void	handle_errors(t_args *head)
{
	while (head)
	{
		if (!ft_isalpha(head->value[0]) && head->value[0] != '_')
		{
			ft_putstr_fd("minishell: export: ", 2);
			ft_putstr_fd(head->value, 2);
			ft_putstr_fd(": not a valid identifier\n", 2);
			g_var->exit_status = 1;
			head->value = NULL;
		}
		else
			head->value = handle_2(head->value);
		head = head->next;
	}
}
