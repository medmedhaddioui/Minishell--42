/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noudrib <noudrib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 12:47:45 by noudrib           #+#    #+#             */
/*   Updated: 2024/08/04 18:44:01 by noudrib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stddef.h>
# include <limits.h>
// # include "../../srcs/inc/minishell.h"

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

long	ft_atoi(const char *str);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstclear(t_list **lst, void (*del)(void*));
int		ft_lstsize(t_list *lst);
t_list	*ft_lstnew(void *content);
char	*ft_strdup_mini(const char *s);
char	*ft_strjoin_mini(char const *s1, char const *s2);
char	*ft_substr_mini(char const *s, unsigned int start, size_t len);
char	*ft_itoa_mini(int n);
char	**ft_split_mini(char const *s, char c);

#endif
