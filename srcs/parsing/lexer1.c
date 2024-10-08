/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noudrib <noudrib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 18:28:12 by forrest           #+#    #+#             */
/*   Updated: 2024/08/04 19:33:39 by noudrib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_token	*creat_token(int type, char *value)
{
	t_token	*node;

	node = (t_token *)malloc(sizeof(t_token));
	if (node == NULL)
		return (NULL);
	node->value = value;
	node->type = type;
	node->next = NULL;
	return (node);
}

void	addback_token(t_token **head, t_token *token)
{
	t_token	*ptr;

	if (head == NULL || token == NULL)
		return ;
	if (*head == NULL)
	{
		*head = token;
		return ;
	}
	ptr = *head;
	while (ptr->next != NULL)
		ptr = ptr->next;
	ptr->next = token;
}

int	handle_quotes_word(char *str)
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
			if (is_separator(str[len]) == 1)
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

int	token_word(char *str, int i, t_token **head)
{
	char	*value;
	int		len;

	len = handle_quotes_word(str + i);
	value = (char *)malloc(sizeof(char) * (len + 1));
	if (value == NULL)
		return (-1);
	ft_lstadd_front(&g_var->collector, ft_lstnew(value));
	ft_memcpy(value, str + i, len);
	value[len] = '\0';
	addback_token(head, creat_token(TOKEN_WORD, value));
	return (len);
}

void	lexer(char *str, t_token **head)
{
	int	i;

	i = 0;
	*head = NULL;
	while (str[i])
	{
		while (str[i] != '\0' && is_space(str[i]))
			i++;
		if (str[i] == '\0')
			break ;
		if (str[i] == '<' && str[i + 1] != '<')
			addback_token(head, creat_token(TOKEN_INR, NULL));
		else if (str[i] == '<' && str[i + 1] == '<' && ++i)
			addback_token(head, creat_token(TOKEN_HERDOC, NULL));
		else if (str[i] == '>' && str[i + 1] != '>')
			addback_token(head, creat_token(TOKEN_OUTR, NULL));
		else if (str[i] == '>' && str[i + 1] == '>' && ++i)
			addback_token(head, creat_token(TOKEN_APPEND, NULL));
		else if (str[i] == '|')
			addback_token(head, creat_token(TOKEN_PIPE, NULL));
		else if (str[i] != '\0')
			i += token_word(str, i, head) - 1;
		i++;
	}
}
