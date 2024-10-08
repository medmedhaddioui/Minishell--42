/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_mini.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noudrib <noudrib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 21:44:59 by noudrib           #+#    #+#             */
/*   Updated: 2024/08/04 18:47:00 by noudrib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../srcs/inc/minishell.h"

static	int	is_sep(char c, char sep)
{
	if (c == sep || c == 0)
		return (1);
	return (0);
}

static char	*ft_word(const char *s, char sep)
{
	int		i;
	char	*word;

	i = 0;
	while (s[i] && s[i] != sep)
		i++;
	word = (char *) malloc((i + 1) * sizeof(char));
	ft_lstadd_front(&g_var->collector, ft_lstnew(word));
	if (!word)
		return (NULL);
	ft_memcpy(word, s, i);
	word[i] = 0;
	return (word);
}

static	char	**split_alloc(char ***split, const char *s, char c, int len)
{
	int	i;
	int	word_count;

	i = 0;
	word_count = 0;
	while (i < len)
	{
		if (!is_sep(s[i], c) && is_sep(s[i + 1], c))
			word_count++;
		i++;
	}
	*split = (char **) malloc((word_count + 1) * sizeof(char *));
	ft_lstadd_front(&g_var->collector, ft_lstnew(*split));
	if (!*split)
		return (NULL);
	(*split)[word_count] = 0;
	return (*split);
}

static	int	word_alloc(char ***split, const char *s, char c, int j)
{
	int	i;
	int	k;
	int	len;

	i = 0;
	k = 0;
	len = ft_strlen(s);
	while (i < len)
	{
		if (is_sep(s[i], c) && !is_sep(s[i + 1], c))
		{
			(*split)[j] = ft_word(s + i + 1, c);
			if ((*split)[j] == 0)
			{
				while (k < j)
					free((*split)[k++]);
				free(*split);
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

char	**ft_split_mini(char const *s, char c)
{
	int		i;
	int		len;
	char	**split;

	i = 0;
	if (s == 0)
		return (NULL);
	len = ft_strlen(s);
	split = NULL;
	if (!split_alloc(&split, s, c, len))
		return (NULL);
	if (!is_sep(s[0], c))
	{
		split[i] = ft_word(s, c);
		if (!split[i])
		{
			free (split);
			return (NULL);
		}
		i++;
	}
	if (!word_alloc(&split, s, c, i))
		return (NULL);
	return (split);
}

// int main()
// {
// 	int	i = 0;
//     char str[] = "   ";
//     char **array = ft_split(str, ' ');
// 	if (array[i] == NULL)
// 		printf("%s", array[i]);
// 	while (array[i])
//         printf("%s:\n", array[i++]);
// 	free(array);
//     return (0);
// }