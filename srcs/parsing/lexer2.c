/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noudrib <noudrib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 18:25:25 by noudrib           #+#    #+#             */
/*   Updated: 2024/08/04 19:28:50 by noudrib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_quotes(char *str)
{
	int	s_flag;
	int	d_flag;
	int	len;

	s_flag = 0;
	d_flag = 0;
	len = 0;
	while (str[len])
	{
		if (str[len] == '\"' && s_flag == 0)
			d_flag = !d_flag;
		if (str[len] == '\'' && d_flag == 0)
			s_flag = !s_flag;
		len++;
	}
	if (s_flag == 1 || d_flag == 1)
		return (write(2, "Syntax error\n", 13), 0);
	return (1);
}

int	is_space(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

int	is_separator(char c)
{
	if (c == '<' || c == '>' || c == '|' || is_space(c))
		return (1);
	return (0);
}

void	free_lexer(t_token **lst)
{
	t_token	*ptr;

	if (!lst || !*lst)
		return ;
	ptr = *lst;
	while (ptr)
	{
		*lst = ptr->next;
		free(ptr);
		ptr = *lst;
	}
}
