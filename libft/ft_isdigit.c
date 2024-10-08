/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noudrib <noudrib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 18:54:58 by noudrib           #+#    #+#             */
/*   Updated: 2024/04/18 16:24:07 by noudrib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

/*int main(void)
{
    printf("%d\n", ft_isdigit('A'));
    printf("%d\n", ft_isdigit('0'));
    printf("%d\n", ft_isdigit('9'));
    printf("%d\n", ft_isdigit('4'));
    printf("%d\n", ft_isdigit(';'));
    printf("%d\n", ft_isdigit('7'));
}*/