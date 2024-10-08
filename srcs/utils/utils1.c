/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medmed <medmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 14:16:00 by mel-hadd          #+#    #+#             */
/*   Updated: 2024/08/08 14:57:47 by medmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	collector_free(t_list **head)
{
	t_list	*tmp;

	if (!head || !*head)
		return ;
	while (*head)
	{
		tmp = (*head)->next;
		free((*head)->content);
		free(*head);
		*head = tmp;
	}
	*head = NULL;
}

char	*get_name(char *env)
{
	int		len;
	char	*str;

	len = 0;
	while (env[len] && env[len] != '=' && env[len] != '+')
		len++;
	str = malloc(sizeof(char *) * (len + 1));
	if (!str)
		return (NULL);
	ft_lstadd_front(&g_var->collector, ft_lstnew(str));
	ft_memcpy(str, env, len);
	str[len] = '\0';
	return (str);
}

void	free_lst(t_list **head)
{
	t_list	*ptr;

	if (!head || !*head)
		return ;
	ptr = *head;
	while (ptr)
	{
		*head = ptr->next;
		free(ptr);
		ptr = *head;
	}
}

void	free_parser(t_cmd **cmd)
{
	t_cmd	*ptr;

	if (!cmd || !*cmd)
		return ;
	ptr = *cmd;
	while (ptr)
	{
		*cmd = ptr->next;
		free(ptr);
		ptr = *cmd;
	}
}

void	init_program(int ac, char **av, char **env, t_data *data)
{
	if (ac != 1)
		exit(1);
	data->env_head = NULL;
	data->export_head = NULL;
	data->token_head = NULL;
	data->cmd_head = NULL;
	data->prompt = "\x1b[31mminishell$ \x1b[0m";
	data->fd = NULL;
	data->fd_collector = NULL;
	data->here_doc_collector = NULL;
	data->cmd_num = 0;
	g_var = malloc(sizeof(t_global));
	g_var->collector = NULL;
	data->last_pid = -1;
	g_var->exit_status = 0;
	data->flag = false;
	data->exit_flag = true;
	(void)av;
	env_copy(env, &data->env_head, data);
	env_export(&data->export_head, data->env_head);
}
