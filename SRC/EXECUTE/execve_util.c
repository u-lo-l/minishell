/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 20:20:28 by yyoo              #+#    #+#             */
/*   Updated: 2022/06/13 16:04:56 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"
#include <sys/stat.h>
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

static char	*get_path(t_env *envlst, char **command_list)
{
	struct stat	buf;
	char		**path;
	char		*simple_path;
	char		*str;
	int			i;

	path = split_path(envlst);
	if (path == NULL)
		return (NULL);
	str = ft_strjoin("/", command_list[0]);
	i = -1;
	while (path[++i])
	{
		simple_path = ft_strjoin(path[i], str);
		if (stat(simple_path, &buf) != -1)
		{
			free(str);
			ft_double_free(path);
			return (simple_path);
		}
		free(simple_path);
	}
	free(str);
	ft_double_free(path);
	return (NULL);
}

void	exe(t_env *envlst, char **cmdlst, char **envp, int stat_result)
{
	char	*path;

	if (stat_result != -1)
		path = cmdlst[0];
	else
		path = get_path(envlst, cmdlst);
	if (path == NULL)
		exit (return_err("command not found", 127));
	if (execve(path, cmdlst, envp) == -1)
	{
		exit (return_err("command not found", 127));
	}
}

static int	is_minishell_builtins(t_token_list *toklst)
{
	if (!ft_strncmp(toklst->head->text, "echo", 5) \
		|| !ft_strncmp(toklst->head->text, "cd", 3) \
		|| !ft_strncmp(toklst->head->text, "pwd", 4) \
		|| !ft_strncmp(toklst->head->text, "export", 7) \
		|| !ft_strncmp(toklst->head->text, "unset", 6) \
		|| !ft_strncmp(toklst->head->text, "env", 4) \
		|| !ft_strncmp(toklst->head->text, "exit", 5))
		return (TRUE);
	return (FALSE);
}

int	check_builtin(t_env *envlst, t_token_list *toklst, int command_num)
{
	if (envlst == NULL || toklst->head == NULL)
		return (0);
	if (is_minishell_builtins(toklst) == TRUE)
		if_builtin(envlst, toklst, command_num);
	else
		pipe_do_execve(envlst, toklst);
	return (0);
}
