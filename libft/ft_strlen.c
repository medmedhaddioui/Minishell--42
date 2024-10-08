/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noudrib <noudrib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 20:10:48 by noudrib           #+#    #+#             */
/*   Updated: 2023/11/17 20:16:17 by noudrib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

/*int main(void)
{
    // printf("%ld\n", ft_strlen(0));
    //printf("%ld\n", strlen(0));
    printf("%ld\n", ft_strlen("h123"));
    printf("%ld\n", ft_strlen(""));
    printf("%ld\n", ft_strlen("h"));  
    char  
    return (0);
}*/
/*int main ()
{
    char c = 'a';
    printf("%zu",ft_strlen(&c));
     printf("%zu",strlen(&c));
}
*/