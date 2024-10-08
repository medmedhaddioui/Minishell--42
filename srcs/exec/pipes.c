/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noudrib <noudrib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 09:53:16 by noudrib           #+#    #+#             */
/*   Updated: 2024/08/01 11:50:04 by noudrib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	cmd_number(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd)
	{
		cmd = cmd->next;
		i++;
	}
	return (i);
}

int	**creat_pipe(t_cmd *cmd, t_data *data)
{
	int	i;
	int	j;

	i = cmd_number(cmd);
	j = 0;
	if (i == 0 || i == 1)
		return (NULL);
	data->fd = (int **)malloc(i * sizeof(int *));
	if (data->fd == NULL)
		return (NULL);
	while (j < i - 1)
	{
		data->fd[j] = (int *)malloc(sizeof(int) * 2);
		if (data->fd[j] == NULL)
			return (NULL);
		pipe(data->fd[j++]);
	}
	data->fd[j] = NULL;
	return (data->fd);
}

void	close_fd_pipes(int **fd)
{
	int	i;

	i = 0;
	if (fd == NULL)
		return ;
	while (fd[i])
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
	}
}

void	free_fd_pipes(int **fd)
{
	int	i;

	i = 0;
	if (fd == NULL)
		return ;
	while (fd[i])
		free(fd[i++]);
	free(fd);
	fd = NULL;
}

void	set_pipes_fd(t_data *data)
{
	int		i;
	int		**fd;
	t_cmd	*cmd;

	i = 1;
	if (data->fd == NULL)
		return ;
	fd = data->fd;
	cmd = data->cmd_head;
	cmd->fd_out = fd[0][1];
	cmd = cmd->next;
	while (fd[i])
	{
		cmd->fd_in = fd[i - 1][0];
		cmd->fd_out = fd[i][1];
		cmd = cmd->next;
		i++;
	}
	cmd->fd_in = fd[i - 1][0];
}
