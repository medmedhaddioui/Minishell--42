/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noudrib <noudrib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 15:56:45 by medmed            #+#    #+#             */
/*   Updated: 2024/08/04 19:32:31 by noudrib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_fd	*fd_lstnew(int fd)
{
	t_fd	*new;

	new = (t_fd *) malloc(sizeof(t_fd));
	if (new == NULL)
		return (NULL);
	ft_lstadd_front(&g_var->collector, ft_lstnew(new));
	new -> fd = fd;
	new -> next = NULL;
	return (new);
}

void	close_fd_redir(t_fd *lst)
{
	while (lst)
	{
		close(lst->fd);
		lst = lst->next;
	}
}

void	fd_add_back(t_fd **lst, t_fd *new)
{
	t_fd	*ptr;

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
