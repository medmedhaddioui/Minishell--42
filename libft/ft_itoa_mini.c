/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_mini.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noudrib <noudrib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 15:59:28 by medmed            #+#    #+#             */
/*   Updated: 2024/08/04 18:47:09 by noudrib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../srcs/inc/minishell.h"

static void	str_fill(char *str, int i, int n)
{
	int	j;

	j = 0;
	if (n < 0)
	{
		str[0] = '-';
		j = 1;
		n *= -1;
	}
	else if (n >= 0)
		i--;
	while (j <= i)
	{
		str[i--] = n % 10 + 48;
		n /= 10;
	}
}

char	*ft_itoa_mini(int n)
{
	int		i;
	int		a;
	char	*str;

	if (n == -2147483648)
		return (ft_strdup_mini("-2147483648"));
	i = 1;
	a = n;
	while (a / 10 != 0 && i++)
		a /= 10;
	if (n < 0)
		str = (char *) ft_calloc(i + 2, sizeof(char));
	else
		str = (char *) ft_calloc(i + 1, sizeof(char));
	if (str == NULL)
		return (NULL);
	ft_lstadd_front(&g_var->collector, ft_lstnew(str));
	str_fill(str, i, n);
	return (str);
}
