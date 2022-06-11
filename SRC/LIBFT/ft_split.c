/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 23:40:46 by dkim2             #+#    #+#             */
/*   Updated: 2022/05/21 01:39:01 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	count_delimeter(char const *s, char c)
{
	int	i;
	int	is_delimeter;
	int	count;

	i = 0;
	is_delimeter = 1;
	count = 0;
	while (s[i])
	{
		if (s[i] == c)
			is_delimeter = 1;
		else
		{
			if (is_delimeter == 1)
				count++;
			is_delimeter = 0;
		}
		i++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	int			set_idx;
	int			count;
	const char	*start;
	char		**str_set;

	if (s == NULL)
		return (NULL);
	count = count_delimeter(s, c);
	str_set = malloc(sizeof(char *) * (count + 1));
	if (!str_set)
		return (NULL);
	set_idx = 0;
	while (set_idx < count)
	{
		while (*s == c)
			s++;
		if (*s == 0)
			break ;
		start = s;
		while (*s != c && *s != 0)
			s++;
		str_set[set_idx++] = ft_strndup(start, s - start);
	}
	str_set[set_idx] = NULL;
	return (str_set);
}
