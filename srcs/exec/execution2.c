/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noudrib <noudrib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 15:54:50 by noudrib           #+#    #+#             */
/*   Updated: 2024/08/06 12:24:45 by noudrib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	close_fd(t_data *data)
{
	close_fd_pipes(data->fd);
	free_fd_pipes(data->fd);
	close_fd_redir(data->fd_collector);
	data->fd = NULL;
}

void	wait_for_childs(t_data *data)
{
	if (data->last_pid == -1)
		return ;
	waitpid(data->last_pid, &g_var->exit_status, 0);
	if (WIFEXITED(g_var->exit_status))
		g_var->exit_status = WEXITSTATUS(g_var->exit_status);
	else if (WIFSIGNALED(g_var->exit_status))
		g_var->exit_status = 128 + WTERMSIG(g_var->exit_status);
	while (wait(NULL) > 0)
		;
}
