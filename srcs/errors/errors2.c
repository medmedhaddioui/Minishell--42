/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noudrib <noudrib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 22:21:59 by noudrib           #+#    #+#             */
/*   Updated: 2024/08/07 22:22:11 by noudrib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	max_heredoc(t_data *data)
{
	int		max;
	t_token	*ptr;

	max = 0;
	ptr = data->token_head;
	while (ptr)
	{
		if (ptr->type == TOKEN_HERDOC && ptr->next
			&& ptr->next->type == TOKEN_WORD)
			max++;
		ptr = ptr->next;
	}
	if (max > 16)
	{
		ft_putendl_fd("minishell: maximum here-document count exceeded", 2);
		free_memory(data);
		exit (2);
	}
}
