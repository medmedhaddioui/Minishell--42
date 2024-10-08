/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noudrib <noudrib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 13:11:25 by medmed            #+#    #+#             */
/*   Updated: 2024/08/06 12:27:08 by noudrib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	builtins2(t_args **head, t_list **env_head, t_list **export_head)
{
	t_args	*ptr;
	t_args	*tmp;

	ptr = *head;
	if (!ft_strcmp(ptr->value, "unset") && ptr->next)
	{
		tmp = ptr->next;
		while (tmp)
		{
			unset_env(env_head, tmp->value);
			unset_env(export_head, tmp->value);
			tmp = tmp->next;
		}
	}
}

void	builtins(t_cmd *cmd, t_list **env, t_data *data, t_list **export)
{
	t_args	*head;

	head = cmd->args;
	if (head == NULL)
		return ;
	if (!ft_strcmp(head->value, "echo"))
		builtins_echo(cmd, head->next, 0);
	if (!ft_strcmp(head->value, "cd"))
		builtins_cd(head, env, export, data);
	if (!ft_strcmp(head->value, "pwd"))
		current_path(cmd, data);
	if (!ft_strcmp(head->value, "env"))
		get_env(cmd, env, data);
	if (!ft_strcmp(head->value, "exit"))
		exit_func(head, data);
	if (!ft_strcmp(head->value, "export") && head->next)
		export_func(env, head->next, export);
	if (!ft_strcmp(head->value, "export") && !head->next)
		print_export(*export, cmd, data);
	builtins2(&head, env, export);
}
