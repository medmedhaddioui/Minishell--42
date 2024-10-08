/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: forrest <forrest@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 18:45:04 by mel-hadd          #+#    #+#             */
/*   Updated: 2024/08/08 16:14:45 by forrest          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_error(char *s)
{
	ft_putendl_fd(s, 2);
	g_var->exit_status = 1;
}

void	ft_exit(int value, char *s, t_data *data)
{
	ft_putstr_fd(s, 2);
	free_memory(data);
	if (data->exit_flag)
		ft_putendl_fd("exit", 1);
	exit(value);
}

void	print_err(char *str, char *err)
{
	ft_putstr_fd("minishell : ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(err, 2);
}

void	command_not_found(t_data *data, char *cmd)
{
	(void) data;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
	free_memory(data);
	exit (127);
}

void	here_doc_err(char *limiter)
{
	ft_putstr_fd("minishell: warning: here-document delimited", 2);
	ft_putstr_fd(" by end-of-file (wanted `", 2);
	ft_putstr_fd(limiter, 2);
	ft_putstr_fd("')\n", 2);
}
