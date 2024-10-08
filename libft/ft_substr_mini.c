/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr_mini.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noudrib <noudrib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 16:15:00 by medmed            #+#    #+#             */
/*   Updated: 2024/08/04 18:46:33 by noudrib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../srcs/inc/minishell.h"

char	*ft_substr_mini(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*ptr;

	i = 0;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup_mini(""));
	else if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	ptr = (char *)malloc((len + 1) * sizeof(char));
	ft_lstadd_front(&g_var->collector, ft_lstnew(ptr));
	while (len && s[start + i] != '\0')
	{
		ptr[i] = (char)s[start + i];
		i++;
		len--;
	}
	ptr[i] = '\0';
	return (ptr);
}
