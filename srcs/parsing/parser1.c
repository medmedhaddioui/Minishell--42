/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noudrib <noudrib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 21:50:42 by noudrib           #+#    #+#             */
/*   Updated: 2024/08/04 19:32:06 by noudrib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	syntax_error2(t_token *lst)
{
	if ((lst->type == TOKEN_APPEND || lst->type == TOKEN_HERDOC
			|| lst->type == TOKEN_INR || lst->type == TOKEN_OUTR)
		&& ((lst->next && lst->next->type != TOKEN_WORD) || lst->next == NULL))
	{
		ft_putendl_fd("minishell: syntax error near redirection token", 2);
		g_var->exit_status = 2;
		return (1);
	}
	if (lst->type == TOKEN_PIPE && lst->next && lst->next->type == TOKEN_PIPE)
	{
		printf("syntax error near unexpected token `%s'\n", lst->next->value);
		g_var->exit_status = 2;
		return (1);
	}
	if (lst->type == TOKEN_PIPE && lst->next == NULL)
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `|'", 2);
		g_var->exit_status = 2;
		return (1);
	}
	return (0);
}

int	syntax_error(t_token *head)
{
	t_token	*lst;

	lst = head;
	if (head == NULL)
		return (0);
	if (lst->type == TOKEN_PIPE && set_exit_status(2))
		return (ft_putendl_fd(
				"minishell: syntax error near unexpected token `|'", 2), 1);
	while (lst)
	{
		if (syntax_error2(lst) == 1)
			return (1);
		lst = lst->next;
	}
	return (0);
}

void	cmd_add_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*ptr;

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

void	parser2(t_redir **redir, t_args **args, t_token **head)
{
	int	i;

	if ((*head)->type == TOKEN_INR)
		redir_add_back(redir, new_redir(TOKEN_INR, (*head)->next->value));
	else if ((*head)->type == TOKEN_OUTR)
		redir_add_back(redir, new_redir(TOKEN_OUTR,
				(*head)->next->value));
	else if ((*head)->type == TOKEN_APPEND)
		redir_add_back(redir, new_redir(TOKEN_APPEND,
				(*head)->next->value));
	if ((*head)->type == TOKEN_INR || (*head)->type == TOKEN_OUTR
		|| (*head)->type == TOKEN_APPEND)
		(*head) = (*head)->next->next;
	else if ((*head)->type == TOKEN_WORD)
	{
		i = 0;
		while (is_space((*head)->value[i]))
			i++;
		while ((*head)->value[i])
			i += token_wordv2((*head)->value, i, args);
		(*head) = (*head)->next;
	}
}

void	parser(t_data *data, t_token *head)
{
	t_args	*args;
	t_redir	*redir;

	data->cmd_head = NULL;
	while (head)
	{
		args = NULL;
		redir = NULL;
		while (head && head->type != TOKEN_PIPE)
			parser2(&redir, &args, &head);
		cmd_add_back(&data->cmd_head, new_cmd(redir, args));
		remove_quotes_args(&args, &redir);
		if (head && head->type == TOKEN_PIPE)
			head = head->next;
	}
}
