/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noudrib <noudrib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 18:53:41 by noudrib           #+#    #+#             */
/*   Updated: 2024/08/04 19:21:47 by noudrib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atoi(const char *str)
{
	int		i;
	long	num;
	int		sign;

	i = 0;
	num = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = -1;
	while (ft_isdigit(str[i]))
	{
		num = num * 10 + str[i++] - 48;
		if ((sign == 1 && num > INT_MAX) || (sign == -1 && - num < INT_MIN))
			return ((long)INT_MAX + 1);
	}
	return (sign * num);
}

// int main(void)
// {
//     //char *str1 = "2147483647";
//     // char *str2 = "+\t   -4935163hgadc99";
//     // char *str3 = "  1235163uhwr494";
//     // char *str4 = "\n\n\n  -46\b9 \n5d6";
//     // char *str5 = "+0163wef651";
//     // char *str6 = "+w5163fwf6515";
//     // char *str7 = "-2147483648";
//     // char *str8 = "";
//     //char *str9 = NULL;
//     printf("%d\n", LONG_MAX);
//     // printf("%d\n", ft_atoi(str2));
//     // printf("%d\n", ft_atoi(str3));
//     // printf("%d\n", ft_atoi(str4));
//     // printf("%d\n", ft_atoi(str5));
//     // printf("%d\n", ft_atoi(str6));
//     // printf("%d\n", ft_atoi(str7));
//     // printf("%d\n", ft_atoi(str8));
//     // //printf("%d\n", atoi(str9));
//     // printf("################\n");
//     // printf("%d\n", atoi(str1));
//     // printf("%d\n", atoi(str2));
//     // printf("%d\n", atoi(str3));
//     // printf("%d\n", atoi(str4));
//     // printf("%d\n", atoi(str5));
//     // printf("%d\n", atoi(str6));
//     // printf("%d\n", atoi(str1));
//     // printf("%d\n", ft_atoi(str1));
//     // //printf("%d\n", atoi(str9));
//     return (0);
// }
