/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noudrib <noudrib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 12:57:28 by mel-hadd          #+#    #+#             */
/*   Updated: 2024/08/03 23:00:46 by noudrib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	count_qoutes(char *limiter)
{
	int	count;
	int	i;
	int	d_flag;
	int	s_flag;

	count = 0;
	i = 0;
	d_flag = 0;
	s_flag = 0;
	while (limiter[i])
	{
		if (limiter[i] == '\"' && s_flag == 0 && ++count)
			d_flag = !d_flag;
		if (limiter[i] == '\'' && d_flag == 0 && ++count)
			s_flag = !s_flag;
		i++;
	}
	return (count);
}

void	get_expanded_limiter(char *result, char *limiter)
{
	int	i;
	int	j;
	int	d_flag;
	int	s_flag;

	i = 0;
	j = 0;
	d_flag = 0;
	s_flag = 0;
	while (limiter[i])
	{
		if (limiter[i] == '\"' && s_flag == 0 && ++i)
		{
			d_flag = !d_flag;
			continue ;
		}
		if (limiter[i] == '\'' && d_flag == 0 && ++i)
		{
			s_flag = !s_flag;
			continue ;
		}
		result[j++] = limiter[i++];
	}
	result[j] = '\0';
}

char	*remove_quotes(char *limiter)
{
	int		len;
	int		count;
	char	*result;

	count = count_qoutes(limiter);
	if (count == 0)
		return (limiter);
	len = ft_strlen(limiter) - count;
	result = malloc(sizeof(char *) * len + 1);
	if (!result)
		return (NULL);
	ft_lstadd_front(&g_var->collector, ft_lstnew(result));
	get_expanded_limiter(result, limiter);
	return (result);
}

int	ft_abs(int n)
{
	if (n >= 0)
		return (n);
	return (-n);
}

char	*generate_file(t_data *data)
{
	int		i;
	int		fd;
	char	*name;
	char	*symbols;
	char	buff[10];

	symbols = "0123456789abcdefghijklmnopqrstuvwxyz";
	fd = open("/dev/random", O_RDWR);
	read(fd, buff, 10);
	close(fd);
	name = malloc(sizeof(char) * 11);
	ft_lstadd_front(&g_var->collector, ft_lstnew(name));
	i = 0;
	while (i < 10)
	{
		name[i] = symbols[ft_abs(buff[i]) % 36];
		i++;
	}
	name[i] = '\0';
	name = ft_strjoin_mini("/tmp/.", name);
	ft_lstadd_front(&data->here_doc_collector, ft_lstnew(name));
	return (name);
}
