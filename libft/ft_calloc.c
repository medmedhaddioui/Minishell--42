/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noudrib <noudrib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 10:21:19 by noudrib           #+#    #+#             */
/*   Updated: 2023/11/18 13:23:36 by noudrib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	if (!count || !size)
		return (malloc(0));
	else if (count > INT_MAX / size)
		return (NULL);
	ptr = malloc(count * size);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, count * size);
	return (ptr);
}

/*int main(void)
{
    void *ptr;
    
    ptr = ft_calloc(231, 543);
	ptr++;
	printf("%zu\n", SIZE_MAX);
	printf("%d\n", INT_MAX);
	printf("%d\n", INT_MIN);
    return (0);
}*/
