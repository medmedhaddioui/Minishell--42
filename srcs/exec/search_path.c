/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noudrib <noudrib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 10:15:52 by noudrib           #+#    #+#             */
/*   Updated: 2024/08/07 22:18:02 by noudrib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <sys/stat.h>

char	*find_path(char **arr, char *cmd)
{
	int		i;
	char	*path;

	i = 0;
	cmd = ft_strjoin_mini("/", cmd);
	path = ft_strjoin_mini(arr[i], cmd);
	while (path && access(path, F_OK | X_OK) == -1)
	{
		i++;
		if (arr[i] == NULL)
			return (cmd);
		path = ft_strjoin_mini(arr[i], cmd);
	}
	return (path);
}

char	**get_copy(t_list *head_env)
{
	char	**arr;
	int		size;
	int		i;

	i = 0;
	size = ft_lstsize(head_env);
	arr = malloc(sizeof(char *) * (size + 1));
	if (!arr)
		return (NULL);
	ft_lstadd_front(&g_var->collector, ft_lstnew(arr));
	while (head_env)
	{
		arr[i++] = head_env->content;
		head_env = head_env->next;
	}
	arr[i] = NULL;
	return (arr);
}

int	slash_exist(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i++] == '/')
			return (1);
	}
	return (0);
}

char	*is_command_exist(char *cmd)
{
	struct stat	statbuf;

	if (slash_exist(cmd) && access(cmd, F_OK) == -1)
	{
		print_err(cmd, "No such file or directory");
		exit (127);
	}
	else if (slash_exist(cmd) && access(cmd, F_OK) != -1)
	{
		stat(cmd, &statbuf);
		if (S_ISREG(statbuf.st_mode) && access(cmd, X_OK) != -1)
			return (cmd);
		else if (S_ISREG(statbuf.st_mode) && access(cmd, X_OK) == -1)
		{
			print_err(cmd, "Permission denied");
			exit (126);
		}
		else if (S_ISDIR(statbuf.st_mode))
		{
			print_err(cmd, "Is a directory");
			exit (126);
		}
	}
	return (NULL);
}

char	*read_path(char **env, char *cmd)
{
	int			i;
	char		*path;
	char		**arr;

	i = 0;
	if (is_command_exist(cmd) != NULL)
		return (cmd);
	else
	{
		while (env && env[i] && ft_strncmp(env[i], "PATH=", 5) != 0)
			i++;
		if (env[i] == NULL)
			return (cmd);
		arr = ft_split_mini(ft_strchr(env[i], '/'), ':');
		if (arr == NULL)
			return (cmd);
		path = find_path(arr, cmd);
		return (path);
	}
}
