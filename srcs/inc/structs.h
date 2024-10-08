/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noudrib <noudrib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 16:54:23 by noudrib           #+#    #+#             */
/*   Updated: 2024/08/07 21:44:27 by noudrib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# define EXPORT 1
# define ENV 0
# define PATH_MAX 4096
# define PTH "PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"

typedef enum e_type
{
	TOKEN_PIPE,
	TOKEN_INR,
	TOKEN_OUTR,
	TOKEN_HERDOC,
	TOKEN_APPEND,
	TOKEN_WORD,
	TOKEN_NO_SUCH_FILE
}					t_type;

typedef enum e_quotes
{
	NO_QUOTES,
	S_QUOTES,
	D_QUOTES
}					t_quotes;

typedef struct s_token
{
	int				type;
	int				quotes;
	char			*value;
	struct s_token	*next;
}					t_token;

typedef struct s_redir
{
	int				type;
	char			*name;
	struct s_redir	*next;
}					t_redir;

typedef struct s_args
{
	char			*value;
	int				quotes;
	struct s_args	*next;
}					t_args;

typedef struct s_cmd
{
	t_redir			*redirs;
	t_args			*args;
	int				fd_in;
	int				fd_out;
	int				redir_failed;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_fd
{
	int				fd;
	struct s_fd		*next;
}					t_fd;

typedef struct s_data
{
	char			*prompt;
	char			*str;
	t_list			*env_head;
	t_list			*export_head;
	t_list			*memory;
	t_token			*token_head;
	t_cmd			*cmd_head;
	char			buff[PATH_MAX];
	int				**fd;
	t_fd			*fd_collector;
	t_list			*here_doc_collector;
	int				cmd_num;
	pid_t			last_pid;
	bool			flag;
	bool			exit_flag;
}					t_data;

typedef struct s_global
{
	int				flag;
	int				save_stdin;
	int				exit_status;
	t_list			*collector;
}					t_global;

#endif
