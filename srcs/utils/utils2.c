/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noudrib <noudrib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 23:16:08 by noudrib           #+#    #+#             */
/*   Updated: 2024/08/06 12:11:30 by noudrib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	set_exit_status(int exit)
{
	g_var->exit_status = exit;
	return (1);
}

void	manual_add_env(t_list **env_head, t_data *data)
{
	data->flag = true;
	getcwd(data->buff, PATH_MAX);
	ft_lstadd_back(env_head, ft_lstnew(ft_strjoin_mini("PWD=", data->buff)));
	ft_lstadd_back(env_head, ft_lstnew("SHLVL=1"));
	ft_lstadd_back(env_head, ft_lstnew(PTH));
	ft_lstadd_back(env_head, ft_lstnew("_=/usr/bin/env"));
}

void	env_copy(char **env, t_list **env_head, t_data *data)
{
	int	i;
	int	shlvl;

	i = 0;
	if (!*env)
		return (manual_add_env(env_head, data));
	while (env[i])
	{
		if (ft_strncmp(env[i], "SHLVL=", 6) != 0)
			ft_lstadd_back(env_head, ft_lstnew(env[i]));
		else
		{
			shlvl = ft_atoi(ft_strchr(env[i], '=') + 1);
			if (shlvl == 999)
			{
				ft_putstr_fd("minishell: warning: shell ", 2);
				ft_putendl_fd("level (1000) too high, resetting to 1", 2);
				shlvl = 0;
			}
			ft_lstadd_back(env_head,
				ft_lstnew(ft_strjoin_mini("SHLVL=", ft_itoa_mini(++shlvl))));
		}
		i++;
	}
}

void	env_export(t_list **export_head, t_list *env_head)
{
	while (env_head)
	{
		ft_lstadd_back(export_head, ft_lstnew(env_head->content));
		env_head = env_head->next;
	}
}

int	ft_lst_size(t_args *head)
{
	int	i;

	i = 0;
	while (head)
	{
		i++;
		head = head->next;
	}
	return (i);
}
