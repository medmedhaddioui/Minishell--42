/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noudrib <noudrib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 18:54:03 by noudrib           #+#    #+#             */
/*   Updated: 2023/11/21 11:22:18 by noudrib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen(s);
	while (*(s + i) != (char)c && i)
		i--;
	if (*(s + i) == (char)c)
		return ((char *)s + i);
	return (NULL);
}

/*int main(void)
{
    char str[] = "";
    //str[4] = 0;
    printf("%s\n", strrchr(str, 0));
    //printf("%s\n", ft_strrchr(str, 0) + 1);
    //printf("%s\n", ft_strrchr("hello world i'm noaman", 'l'));
    return (0);
}*/