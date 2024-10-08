/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noudrib <noudrib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 14:47:10 by mel-hadd          #+#    #+#             */
/*   Updated: 2024/08/07 22:21:26 by noudrib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	handle_c(int num)
{
	t_data	*data;

	(void) num;
	data = var_static();
	free_memory(data);
	exit(130);
}

char	*expand_here_doc(char *str, t_list *env_head, char *limiter)
{
	int	i;

	i = 0;
	while (limiter[i] && (limiter[i] != '\"' && limiter[i] != '\''))
		i++;
	if (limiter[i] == '\"' || limiter[i] == '\'')
		return (str);
	str = expand_value(str, env_head);
	return (str);
}

void	child_heredoc(char *limiter, int fd, t_data *data, char *delimiter)
{
	char	*str;
	char	*result;

	signal(SIGINT, handle_c);
	str = readline("> ");
	while (ft_strcmp(str, limiter))
	{
		result = expand_here_doc(str, data->env_head, delimiter);
		ft_putendl_fd(result, fd);
		free(str);
		str = readline("> ");
	}
	if (!str && !g_var->flag)
		here_doc_err(limiter);
	free(str);
	free_memory(data);
	exit (0);
}

void	open_heredoc(t_data *data, t_token *head)
{
	char	*limiter;
	int		fd;
	char	*filename;
	int		exit_s;
	int		id;

	limiter = remove_quotes(head->next->value);
	filename = generate_file(data);
	fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
	signal(SIGQUIT, SIG_IGN);
	id = fork();
	if (id == 0)
		child_heredoc(limiter, fd, data, head->next->value);
	else
	{
		waitpid(id, &exit_s, 0);
		if (WIFEXITED(exit_s))
			exit_s = WEXITSTATUS(exit_s);
		if (exit_s == 130)
			g_var->flag = 1;
		head->next->value = ft_strdup_mini(filename);
		close(fd);
	}
}

int	heredoc(t_data *data)
{
	t_token	*ptr;

	g_var->flag = 0;
	ptr = data->token_head;
	max_heredoc(data);
	while (ptr)
	{
		if (ptr->type == TOKEN_HERDOC && ptr->next
			&& ptr->next->type == TOKEN_WORD)
		{
			ptr->value = ft_strdup_mini("<");
			ptr->type = TOKEN_INR;
			open_heredoc(data, ptr);
			if (g_var->flag)
			{
				g_var->exit_status = 130;
				return (0);
			}
		}
		ptr = ptr->next;
	}
	return (1);
}
