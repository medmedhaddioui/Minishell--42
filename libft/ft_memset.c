/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noudrib <noudrib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 20:11:00 by noudrib           #+#    #+#             */
/*   Updated: 2024/08/04 18:43:20 by noudrib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
		*((unsigned char *)s + i++) = (unsigned char)c;
	return (s);
}

/*int main(void)
{
    char *str1 = NULL;
    ft_memset(str1, 'z', 5);
    printf("%s\n", str1);
    return (0);
}*/