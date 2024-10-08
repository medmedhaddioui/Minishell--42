/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noudrib <noudrib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 16:19:12 by noudrib           #+#    #+#             */
/*   Updated: 2024/08/06 12:09:18 by noudrib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_memory(t_data *data)
{
	free_lexer(&data->token_head);
	free_parser(&data->cmd_head);
	free_lst(&data->env_head);
	free_lst(&data->export_head);
	free_lst(&data->here_doc_collector);
	free(data->str);
	collector_free(&g_var->collector);
	free(g_var);
}

void	delete_here_doc(t_data *data)
{
	t_list	*ptr;

	ptr = data->here_doc_collector;
	while (ptr)
	{
		unlink(ptr->content);
		ptr = ptr->next;
	}
}

void	*var_static(void)
{
	static t_data	var;

	return (&var);
}
