/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noudrib <noudrib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 11:34:49 by mel-hadd          #+#    #+#             */
/*   Updated: 2024/07/31 23:10:04 by noudrib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	equal_index(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '+' && s[i + 1] == '=')
			return (i);
		if (s[i] == '=')
			return (i);
		i++;
	}
	return (0);
}

void	sort_export(char **arr)
{
	char	*tmp;
	int		j;
	int		i;

	i = -1;
	while (arr[++i])
	{
		j = i + 1;
		while (arr[j])
		{
			if (ft_strncmp(arr[i], arr[j], ft_strlen(arr[i])) > 0)
			{
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
			j++;
		}
	}
}

char	**creat_arr(t_list *head, t_data *data)
{
	char	**arr;
	int		len ;
	int		i;

	i = 0;
	len = ft_lstsize(head);
	if (data->flag)
		len--;
	arr = malloc(sizeof(char *) * (len + 1));
	while (head)
	{
		if (!ft_strncmp(head->content, "PATH", 4) && data->flag)
		{
			head = head->next;
			continue ;
		}
		arr[i++] = head->content;
		head = head->next;
	}
	arr[i] = NULL;
	return (arr);
}

void	print_export(t_list *head, t_cmd *cmd, t_data *data)
{
	char	**arr;
	int		sign_index;
	int		i;

	arr = creat_arr(head, data);
	sort_export(arr);
	i = 0;
	while (arr[i])
	{
		sign_index = equal_index(arr[i]);
		if (sign_index == 0)
			ft_putendl_fd(ft_strjoin_mini("declare -x ", arr[i]), cmd->fd_out);
		else if (sign_index != 0)
		{
			ft_putstr_fd(ft_strjoin_mini("declare -x ",
					ft_substr_mini(arr[i], 0, sign_index + 1)), cmd->fd_out);
			ft_putstr_fd("\"", cmd->fd_out);
			ft_putendl_fd(ft_strjoin_mini(ft_substr_mini(arr[i], sign_index + 1,
						ft_strlen(arr[i]) - sign_index), "\""), cmd->fd_out);
		}
		i++;
	}
	free(arr);
}
