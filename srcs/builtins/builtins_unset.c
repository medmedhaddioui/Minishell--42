/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medmed <medmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 14:18:23 by mel-hadd          #+#    #+#             */
/*   Updated: 2024/07/24 13:13:22 by medmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_var_name(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '=')
			return (0);
		i++;
	}
	return (1);
}

void	unset_env(t_list **head, char *s)
{
	t_list	*ptr;
	t_list	*tmp;

	if (!head || !*head)
		return ;
	ptr = *head;
	tmp = *head;
	if (check_var_name(s) && !ft_strcmp(get_name(ptr->content), s))
	{
		*head = ptr->next;
		return (free(ptr));
	}
	while (ptr)
	{
		if (check_var_name(s) && !ft_strcmp(get_name(ptr->content), s))
		{
			tmp->next = ptr->next;
			return (free(ptr));
		}
		tmp = ptr;
		ptr = ptr->next;
	}
}
