/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exit_env.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noudrib <noudrib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 17:44:00 by mel-hadd          #+#    #+#             */
/*   Updated: 2024/07/31 19:33:43 by noudrib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	get_env(t_cmd *cmd, t_list **head, t_data *data)
{
	t_list	*ptr;

	ptr = *head;
	while (ptr)
	{
		if (!ft_strncmp(ptr->content, "PATH", 4) && data->flag)
		{
			ptr = ptr->next;
			continue ;
		}
		ft_putstr_fd((ptr)->content, cmd->fd_out);
		write(cmd->fd_out, "\n", 1);
		ptr = (ptr)->next;
	}
}

void	exit_func(t_args *head, t_data *data)
{
	int	i;

	i = 0;
	if (!head->next)
		ft_exit(g_var->exit_status, NULL, data);
	head = head->next;
	while (head->value[i])
	{
		if (head->value[0] == '+' || head->value[0] == '-')
			i++;
		if (!ft_isdigit(head->value[i]))
			ft_exit(2, "minishell: exit: : numeric argument required\n", data);
		i++;
	}
	if (!head->next)
		ft_exit(ft_atoi(head->value), NULL, data);
	return (ft_error("bash: exit: too many arguments\n"));
}
