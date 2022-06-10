/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 20:20:28 by yyoo              #+#    #+#             */
/*   Updated: 2022/06/10 15:54:06 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

static char	**split_path(t_env *envlst)
{
	t_envnode	*curr;
	char		**path;

	path = NULL;
	curr = envlst->phead;
	while (curr)
	{
		if (ft_strnstr(curr->key, "PATH", 4))
		{
			path = ft_split(curr->value, ':');
			break ;
		}
		curr = curr->nextnode;
	}
	return (path);
}

char	*get_path(t_env *envlst, char **command_list)
{
	struct stat	buf;
	char		**path;
	char		*simple_path;
	char		*str;
	int			i;

	path = split_path(envlst);
	str = ft_strjoin("/", command_list[0]);
	i = 0;
	while (path[i])
	{
		simple_path = ft_strjoin(path[i], str);
		if (stat(simple_path, &buf) != -1)
			return (simple_path);
		free(simple_path);
		i++;
	}
	return (NULL);
}
