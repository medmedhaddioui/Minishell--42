/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noudrib <noudrib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 18:11:49 by noudrib           #+#    #+#             */
/*   Updated: 2024/07/31 23:03:16 by noudrib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_args	*new_args(char *value, int quotes)
{
	t_args	*args;

	args = (t_args *)malloc(sizeof(t_args));
	if (args == NULL)
		return (NULL);
	ft_lstadd_front(&g_var->collector, ft_lstnew(args));
	args->value = value;
	args->quotes = quotes;
	args->next = NULL;
	return (args);
}

t_redir	*new_redir(int type, char *name)
{
	t_redir	*redir;

	redir = (t_redir *)malloc(sizeof(t_redir));
	if (redir == NULL)
		return (NULL);
	ft_lstadd_front(&g_var->collector, ft_lstnew(redir));
	redir->type = type;
	redir->name = name;
	redir->next = NULL;
	return (redir);
}

t_cmd	*new_cmd(t_redir *redir, t_args *args)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (cmd == NULL)
		return (NULL);
	cmd->args = args;
	cmd->redirs = redir;
	cmd->fd_in = 0;
	cmd->fd_out = 1;
	cmd->redir_failed = 0;
	cmd->next = NULL;
	return (cmd);
}

void	arg_add_back(t_args **lst, t_args *new)
{
	t_args	*ptr;

	if (lst == NULL || new == NULL)
		return ;
	else if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	ptr = *lst;
	while (ptr->next != NULL)
		ptr = ptr->next;
	ptr->next = new;
}

void	redir_add_back(t_redir **lst, t_redir *new)
{
	t_redir	*ptr;

	if (lst == NULL || new == NULL)
		return ;
	else if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	ptr = *lst;
	while (ptr -> next != NULL)
		ptr = ptr -> next;
	ptr -> next = new;
}
