/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_echo_pwd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noudrib <noudrib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 14:30:55 by mel-hadd          #+#    #+#             */
/*   Updated: 2024/08/04 18:19:47 by noudrib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	echo_option(t_args **head)
{
	int		i;
	t_args	*ptr;

	i = 0;
	ptr = *head;
	while (ptr)
	{
		i = 0;
		if (ptr->value[i] == '-' && ptr->value[i + 1])
			while (ptr->value[++i] == 'n')
				;
		if (ptr->value[i] != '\0')
			break ;
		ptr = ptr->next;
	}
	*head = ptr;
	return (1);
}

void	builtins_echo(t_cmd *cmd, t_args *head, int skip)
{
	int	flag;
	int	i;

	flag = 0;
	if (!head)
	{
		write(cmd->fd_out, "\n", 1);
		return ;
	}
	i = 0;
	if (head->value[i] == '-' && head->value[i + 1] == 'n')
		while (head->value[++i] == 'n')
			;
	if (!head->value[i])
		flag = echo_option(&head);
	while (head)
	{
		if (skip == 1)
			write(cmd->fd_out, " ", 1);
		skip = 1;
		ft_putstr_fd(head->value, cmd->fd_out);
		head = head->next;
	}
	if (!flag)
		write(cmd->fd_out, "\n", 1);
}

void	current_path(t_cmd *cmd, t_data *data)
{
	char	*path;
	char	buff[PATH_MAX];

	path = getcwd(buff, PATH_MAX);
	if (!path)
		ft_putendl_fd(data->buff, cmd->fd_out);
	else
		ft_putendl_fd(buff, cmd->fd_out);
}
