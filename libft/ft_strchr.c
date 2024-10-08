/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noudrib <noudrib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 18:54:36 by noudrib           #+#    #+#             */
/*   Updated: 2023/11/21 11:16:59 by noudrib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s != (char)c && *s)
		s++;
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}

/*int main(void)
{
    char str[] = "iafaodobnaad";
    //str[4] = 0;
    printf("%s\n", strchr(str, 0));
    //printf("%s\n", ft_strchr(str, 0) + 1);
    //printf("%p\n", ft_strchr("hello i'm noaman", 'x'));
    return (0);
}*/