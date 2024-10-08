/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: forrest <forrest@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 19:13:03 by noudrib           #+#    #+#             */
/*   Updated: 2024/08/08 15:34:26 by forrest          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	single_cmd(t_data *data, t_cmd *cmd, char **env, int size)
{
	t_args	*head;
	char	*path;
	char	**argv;
	int		i;

	i = 0;
	head = cmd->args;
	argv = malloc(sizeof(char *) * (size + 1));
	ft_lstadd_front(&g_var->collector, ft_lstnew(argv));
	while (head)
	{
		argv[i++] = head->value;
		head = head->next;
	}
	argv[i] = NULL;
	path = read_path(env, argv[0]);
	dup2(cmd->fd_in, 0);
	dup2(cmd->fd_out, 1);
	close_fd_pipes(data->fd);
	free_fd_pipes(data->fd);
	if (execve(path, argv, env) == -1)
		command_not_found(data, argv[0]);
}

void	cmd_exec(t_data *data, t_cmd *cmd, t_args *head, t_list **env_head)
{
	char	**env;
	pid_t	id;

	env = get_copy(*env_head);
	id = fork();
	if (id == -1)
		ft_exit(EXIT_FAILURE, NULL, data);
	if (id == 0)
		single_cmd(data, cmd, env, ft_lst_size(head));
	if (cmd->next == NULL)
		data->last_pid = id;
}

int	check_builtins(t_args *head)
{
	if (head == NULL)
		return (0);
	if (!ft_strcmp(head->value, "exit"))
		return (0);
	g_var->exit_status = 0;
	if (!ft_strcmp(head->value, "env") || !ft_strcmp(head->value, "echo")
		|| !ft_strcmp(head->value, "cd") || !ft_strcmp(head->value, "pwd")
		|| !ft_strcmp(head->value, "export") || !ft_strcmp(head->value, "unset")
		|| (!(*head->value) && head->quotes != 1))
		return (0);
	return (1);
}

void	builtins_exec(t_cmd *cmd, t_data *data, t_list **env, t_list **export)
{
	pid_t	pid;
	int		exit_status;

	data->exit_flag = true;
	if (cmd_number(data->cmd_head) > 1)
	{
		pid = fork();
		if (pid == 0)
		{
			data->exit_flag = false;
			g_var->exit_status = 0;
			builtins(cmd, env, data, export);
			exit_status = g_var->exit_status;
			free_memory(data);
			exit(exit_status);
		}
		else if (cmd->next == NULL)
			data->last_pid = pid;
	}
	else
		builtins(cmd, env, data, export);
}

void	execution(t_data *data, t_list **env_head, t_list **export_head)
{
	t_cmd	*cmd;

	cmd = data->cmd_head;
	data->cmd_num = cmd_number(data->cmd_head);
	getcwd(data->buff, PATH_MAX);
	creat_pipe(cmd, data);
	set_pipes_fd(data);
	set_redirection_fd(data);
	while (cmd)
	{
		if (cmd->redir_failed)
		{
			cmd = cmd->next;
			g_var->exit_status = 1;
			continue ;
		}
		if (check_builtins(cmd->args))
			cmd_exec(data, cmd, cmd->args, env_head);
		else
			builtins_exec(cmd, data, env_head, export_head);
		cmd = cmd->next;
	}
	close_fd(data);
	wait_for_childs(data);
}
