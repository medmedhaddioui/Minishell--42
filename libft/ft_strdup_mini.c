/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_mini.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noudrib <noudrib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 16:14:56 by medmed            #+#    #+#             */
/*   Updated: 2024/08/04 18:46:55 by noudrib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../srcs/inc/minishell.h"

char	*ft_strdup_mini(const char *s)
{
	size_t	len;
	char	*tab;

	len = ft_strlen(s);
	tab = (char *) malloc (len * sizeof(char) + 1);
	if (tab == NULL)
		return (NULL);
	ft_lstadd_front(&g_var->collector, ft_lstnew(tab));
	ft_memcpy(tab, s, len);
	tab [len] = '\0';
	return (tab);
}
