/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noudrib <noudrib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 09:38:31 by mel-hadd          #+#    #+#             */
/*   Updated: 2024/07/30 18:05:37 by noudrib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	update_export(t_list **export, char *str, int sign_index)
{
	t_list	*ptr;

	ptr = *export;
	if (!sign_index)
		return ;
	while (ptr)
	{
		if (!ft_strcmp(get_name(ptr->content), get_name(str)))
			ptr->content = plus_check(ptr->content, str);
		ptr = ptr->next;
	}
}

void	update_env(t_list **env, char *str, int sign_index)
{
	t_list	*ptr;

	ptr = *env;
	if (!sign_index)
		return ;
	while (ptr)
	{
		if (!ft_strcmp(get_name(ptr->content), get_name(str)))
			ptr->content = plus_check(ptr->content, str);
		ptr = ptr->next;
	}
}

void	add_new_env(t_list **head, char *str, int sign, int flag)
{
	str = handle_plus_sign(str);
	if (!flag && sign != 0)
		ft_lstadd_back(head, ft_lstnew(str));
	if (flag)
		ft_lstadd_back(head, ft_lstnew(str));
}

void	export_func(t_list **env_head, t_args *head, t_list **export_head)
{
	int	sign_index;

	sign_index = 0;
	handle_errors(head);
	while (head)
	{
		if (!head->value)
		{
			head = head->next;
			continue ;
		}
		sign_index = equal_index(head->value);
		if (env_existing_check(export_head, head->value, sign_index))
			update_export(export_head, ft_strdup_mini(head->value), sign_index);
		else
			add_new_env(export_head, ft_strdup_mini(head->value), sign_index,
				EXPORT);
		if (env_existing_check(env_head, head->value, sign_index))
			update_env(env_head, ft_strdup_mini(head->value), sign_index);
		else
			add_new_env(env_head, ft_strdup_mini(head->value), sign_index, ENV);
		head = head->next;
	}
}
