/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medmed <medmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 14:35:00 by mel-hadd          #+#    #+#             */
/*   Updated: 2024/08/07 16:20:00 by medmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/minishell.h"

t_global	*g_var = NULL;

void	sigint_handler1(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
	g_var->exit_status = 130;
}

void	sigint_handler2(int sig)
{
	(void)sig;
	printf("\n");
}

void	sigquit_handler(int sig)
{
	(void)sig;
	printf("Quit (core dumped)\n");
}

int	ft_readline(t_data *data)
{
	signal(SIGINT, sigint_handler1);
	signal(SIGQUIT, SIG_IGN);
	data->str = readline(data->prompt);
	if (!data->str)
		ft_exit(g_var->exit_status, NULL, data);
	if (*data->str == '\0' || !ft_strcmp(data->str, ":")
		|| !ft_strcmp(data->str, "#"))
		return (1);
	if (!ft_strcmp(data->str, "!") && set_exit_status(1))
		return (1);
	signal(SIGINT, sigint_handler2);
	signal(SIGQUIT, sigquit_handler);
	add_history(data->str);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_data	*data;

	data = var_static();
	init_program(ac, av, env, data);
	while (1)
	{
		if (ft_readline(data))
			continue ;
		if (check_quotes(data->str))
		{
			lexer(data->str, &data->token_head);
			if (heredoc(data) && syntax_error(data->token_head) == 0)
			{
				expanding(&data->token_head, data->env_head);
				parser(data, data->token_head);
				execution(data, &data->env_head, &data->export_head);
			}
		}
		free_lexer(&data->token_head);
		free_parser(&data->cmd_head);
		delete_here_doc(data);
		free(data->str);
		data->last_pid = -1;
	}
	return (0);
}
