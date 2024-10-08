/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noudrib <noudrib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 11:46:23 by medmed            #+#    #+#             */
/*   Updated: 2024/08/06 12:26:33 by noudrib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*home_path(t_list *head)
{
	while (head)
	{
		if (!ft_strncmp(head->content, "HOME", 4))
			return (ft_substr_mini(head->content, 5,
					ft_strlen(head->content) - 5));
		head = head->next;
	}
	return (NULL);
}

char	*find_current_pwd(t_list *head)
{
	while (head)
	{
		if (!ft_strncmp(head->content, "PWD", 3))
			return (ft_strchr(head->content, '=') + 1);
		head = head->next;
	}
	return (NULL);
}

void	update_old_pwd(t_list **env, t_list **export)
{
	t_list	*ptr;
	char	*pwd_value;
	int		flag;

	flag = 0;
	ptr = *env;
	pwd_value = find_current_pwd(*env);
	if (!pwd_value)
		return ;
	while (ptr)
	{
		if (!ft_strncmp(ptr->content, "OLDPWD", 6))
		{
			ptr->content = ft_strjoin_mini("OLDPWD=", pwd_value);
			if (!flag && ++flag)
				ptr = *export;
			else
				return ;
		}
		else
			ptr = ptr->next;
	}
	ft_lstadd_back(env, ft_lstnew(ft_strjoin_mini("OLDPWD=", pwd_value)));
	ft_lstadd_back(export, ft_lstnew(ft_strjoin_mini("OLDPWD=", pwd_value)));
}

void	update_pwd(t_list **env_head, t_list **export_head, t_data *data)
{
	char	buff[PATH_MAX];
	char	*path;
	t_list	*ptr;
	int		flag;

	path = getcwd(buff, PATH_MAX);
	if (!path)
		path = data->buff;
	ptr = *env_head;
	flag = 0;
	while (ptr)
	{
		if (!ft_strncmp(ptr->content, "PWD", 3))
		{
			ptr->content = ft_strjoin_mini("PWD=", path);
			if (!flag && ++flag)
				ptr = *export_head;
			else
				break ;
		}
		else
			ptr = ptr->next;
	}
}

void	builtins_cd(t_args *head, t_list **env, t_list **export, t_data *data)
{
	char	*path;

	if (ft_lst_size(head) > 2)
		return (ft_error("minishell: cd: too many arguments"));
	if (!head->next)
	{
		path = home_path(*env);
		if (!path)
			return (ft_error("minishell: cd: HOME not set"));
		if (access(path, F_OK) == -1)
			return (ft_error("minishell: cd: : No such file or directory"));
		update_old_pwd(env, export);
		chdir(path);
		update_pwd(env, export, data);
	}
	else
	{
		update_old_pwd(env, export);
		if (chdir(head->next->value) == -1)
			return (ft_error("minishell: cd: : No such file or directory"));
		update_pwd(env, export, data);
	}
}
