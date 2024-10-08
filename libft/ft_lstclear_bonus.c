/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: forrest <forrest@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 20:22:15 by noudrib           #+#    #+#             */
/*   Updated: 2024/03/30 14:52:46 by forrest          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*ptr;

	if (!lst || !del || !*lst)
		return ;
	ptr = *lst;
	while (ptr)
	{
		*lst = ptr -> next;
		del(ptr -> content);
		free(ptr);
		ptr = *lst;
	}
}
