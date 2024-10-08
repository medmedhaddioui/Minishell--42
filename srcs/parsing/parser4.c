/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noudrib <noudrib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 22:54:54 by noudrib           #+#    #+#             */
/*   Updated: 2024/08/07 21:27:30 by noudrib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_sep(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

int	handle_quotes_wordv2(char *str)
{
	int	s_flag;
	int	d_flag;
	int	len;

	s_flag = 0;
	d_flag = 0;
	len = 0;
	while (str[len])
	{
		if (!s_flag && !d_flag)
		{
			if (is_sep(str[len]) == 1)
				return (len);
		}
		if (str[len] == '\"' && s_flag == 0)
			d_flag = !d_flag;
		if (str[len] == '\'' && d_flag == 0)
			s_flag = !s_flag;
		len++;
	}
	return (len);
}

int	token_wordv2(char *str, int i, t_args **args)
{
	char	*value;
	int		len;

	len = handle_quotes_wordv2(str + i);
	value = (char *)malloc(sizeof(char) * (len + 1));
	if (value == NULL)
		return (-1);
	ft_lstadd_front(&g_var->collector, ft_lstnew(value));
	ft_memcpy(value, str + i, len);
	value[len] = '\0';
	arg_add_back(args, new_args(value, 0));
	while (str[i + len] && (str[i + len] == ' ' || str[i + len] == '\t'))
		len++;
	return (len);
}

int	is_quote(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

void	remove_quotes_args(t_args **args, t_redir **redir)
{
	t_args	*ptr;
	t_redir	*tmp;

	ptr = *args;
	tmp = *redir;
	while (ptr)
	{
		if (is_quote(ptr->value[0]) && is_quote(ptr->value[1])
			&& !ptr->value[2])
			ptr->quotes = 1;
		ptr->value = remove_quotes(ptr->value);
		ptr = ptr->next;
	}
	while (tmp)
	{
		if (is_quote(tmp->name[0]) && is_quote(tmp->name[1]) && !tmp->name[2])
			tmp->type = TOKEN_NO_SUCH_FILE;
		tmp->name = remove_quotes(tmp->name);
		tmp = tmp->next;
	}
}
