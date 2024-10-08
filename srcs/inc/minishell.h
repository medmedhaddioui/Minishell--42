/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noudrib <noudrib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 17:47:30 by mel-hadd          #+#    #+#             */
/*   Updated: 2024/08/07 22:23:08 by noudrib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../../libft/libft.h"
# include <stdbool.h>
# include "structs.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <unistd.h>

extern t_global	*g_var;

// data_program
void	ft_error(char *s);
void	free_lst(t_list **head);
void	free_parser(t_cmd **cmd);
int		ft_lst_size(t_args *head);
void	free_lexer(t_token **lst);
void	collector_free(t_list **head);
void	collector_free(t_list **head);
void	ft_exit(int value, char *s, t_data *data);
void	env_copy(char **env, t_list **env_head, t_data *data);
void	init_program(int ac, char **av, char **env, t_data *prog);

// builtins
int		equal_index(char *s);
char	*handle_plus_sign(char *s);
void	handle_errors(t_args *head);
void	unset_env(t_list **head, char *s);
char	*plus_check(char *env_var, char *str);
void	exit_func(t_args *head, t_data *data);
void	current_path(t_cmd *cmd, t_data *data);
void	get_env(t_cmd *cmd, t_list **head, t_data *data);
void	builtins_echo(t_cmd *cmd, t_args *head, int skip);
void	env_export(t_list **export_head, t_list *env_head);
void	print_export(t_list *head, t_cmd *cmd, t_data *data);
int		env_existing_check(t_list **head, char *str, int sign_index);
void	builtins(t_cmd *cmd, t_list **env, t_data *data, t_list **export);
void	export_func(t_list **env_head, t_args *head, t_list **export_head);
void	builtins_cd(t_args *head, t_list **env, t_list **export, t_data *data);

// execuction
void	close_fd_pipes(int **fd);
void	free_fd_pipes(int **fd);
void	print_err(char *str, char *err);
void	set_redirection_fd(t_data *data);
t_redir	*new_redir(int type, char *name);
t_args	*new_args(char *value, int quotes);
t_cmd	*new_cmd(t_redir *redir, t_args *args);
int		**creat_pipe(t_cmd *cmd, t_data *data);
void	arg_add_back(t_args **lst, t_args *new);
void	redir_add_back(t_redir **lst, t_redir *new);
void	execution(t_data *data, t_list **env_head, t_list **export_head);

// expanding
int		check_lim(char c);
char	*get_name(char *env);
int		heredoc(t_data *data);
char	*get_content(char *str);
char	*get_content(char *str);
char	*remove_quotes(char *limiter);
char	*handle_s_quote(char *value, int *i);
char	*non_expand_value_join(char c, char *result);
char	*expand_value(char *value, t_list *env_head);
char	*non_expand_value_join(char c, char *result);
void	expanding(t_token **token_lst, t_list *env_head);
char	*setup_expand_value(char *value, t_list *env_head);
char	*handle_d_quote(char *value, t_list *env_head, int *i);
char	*handle_no_quote(char *value, t_list *env_head, int *i);
char	*expand_here_doc(char *str, t_list *env_head, char *limter);

// parsing
int		is_space(char c);
t_fd	*fd_lstnew(int fd);
int		is_separator(char c);
int		cmd_number(t_cmd *cmd);
int		check_quotes(char *str);
void	close_fd_redir(t_fd *lst);
void	set_pipes_fd(t_data *data);
int		syntax_error(t_token *head);
void	lexer(char *str, t_token **head);
void	set_redirection_fd(t_data *data);
void	fd_add_back(t_fd **lst, t_fd *new);
t_token	*creat_token(int type, char *value);
void	parser(t_data *data, t_token *head);
void	cmd_add_back(t_cmd **lst, t_cmd *new);
void	arg_add_back(t_args **lst, t_args *new);
void	redir_add_back(t_redir **lst, t_redir *new);
int		token_word(char *str, int i, t_token **head);
void	addback_token(t_token **head, t_token *token);
int		token_wordv2(char *str, int i, t_args **args);
void	remove_quotes_args(t_args **args, t_redir **redir);
int		open_input_redir(char *file_name, t_cmd *cmd, t_data *data);
int		open_output_append_redir(t_redir *redir, t_cmd *cmd, t_data *data);

char	**get_copy(t_list *head_env);
char	*read_path(char **env, char *cmd);
void	command_not_found(t_data *data, char *cmd);

//utils
void	*var_static(void);
void	close_fd(t_data *data);
void	free_memory(t_data *data);
int		set_exit_status(int exit);
void	max_heredoc(t_data *data);
void	here_doc_err(char *limiter);
char	*generate_file(t_data *data);
void	wait_for_childs(t_data *data);
void	delete_here_doc(t_data *data);
#endif
