/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirictions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: forrest <forrest@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 19:17:45 by forrest           #+#    #+#             */
/*   Updated: 2024/08/08 15:34:31 by forrest          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	open_input_redir(char *file_name, t_cmd *cmd, t_data *data)
{
	int		fd;
	char	*str;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		cmd->redir_failed = 1;
		str = strerror(errno);
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(file_name, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(str, 2);
		g_var->exit_status = 1;
		return (1);
	}
	cmd->fd_in = fd;
	fd_add_back(&data->fd_collector, fd_lstnew(cmd->fd_in));
	return (0);
}

int	open_output_append_redir(t_redir *redir, t_cmd *cmd, t_data *data)
{
	int		fd;
	char	*str;

	fd = 1;
	if (redir->type == TOKEN_OUTR)
		fd = open(redir->name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	else if (redir->type == TOKEN_APPEND)
		fd = open(redir->name, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fd == -1)
	{
		cmd->redir_failed = 1;
		str = strerror(errno);
		print_err(redir->name, str);
		g_var->exit_status = 1;
		return (1);
	}
	cmd->fd_out = fd;
	fd_add_back(&data->fd_collector, fd_lstnew(cmd->fd_out));
	return (0);
}

int	check_empty_redir(t_cmd *cmd, t_redir *redir)
{
	if (redir->type == TOKEN_NO_SUCH_FILE)
	{
		print_err(redir->name, "No such file or directory");
		g_var->exit_status = 1;
		cmd->redir_failed = 1;
		return (1);
	}
	if (!*redir->name)
	{
		print_err(redir->name, "ambiguous redirect");
		g_var->exit_status = 1;
		cmd->redir_failed = 1;
		return (1);
	}
	return (0);
}

void	set_redirection_fd(t_data *data)
{
	t_cmd	*cmd;
	t_redir	*redir;

	cmd = data->cmd_head;
	while (cmd)
	{
		redir = cmd->redirs;
		while (redir)
		{
			if (check_empty_redir(cmd, redir) == 1)
				break ;
			if (redir->type == TOKEN_INR
				&& open_input_redir(redir->name, cmd, data))
				break ;
			else if ((redir->type == TOKEN_OUTR || redir->type == TOKEN_APPEND)
				&& open_output_append_redir(redir, cmd, data))
				break ;
			redir = redir->next;
		}
		cmd = cmd->next;
	}
}

			// if (redir->type == TOKEN_NO_SUCH_FILE)
			// {
			// 	print_err(redir->name, "No such file or directory");
			// 	g_var->exit_status = 1;
			// 	cmd->redir_failed = 1;
			// 	break ;
			// }
			// if (!*redir->name)
			// {
			// 	print_err(redir->name, "ambiguous redirect");
			// 	g_var->exit_status = 1;
			// 	cmd->redir_failed = 1;
			// 	break ;
			// }