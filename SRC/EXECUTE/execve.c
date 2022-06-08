/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyoo <yyoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 20:20:31 by yyoo              #+#    #+#             */
/*   Updated: 2022/06/08 18:33:27 by yyoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

char	**get_command_list(t_token_list *token)
{
	t_token	*curr;
	char	**command_list;
	int		i;

	command_list = malloc(sizeof(char *) * (token->num_of_tokens + 1));
	curr = token->head;
	i = 0;
	while (curr)
	{
		command_list[i] = malloc(sizeof(char) * ft_strlen(curr->text));
		command_list[i] = curr->text;
		i++;
		curr = curr->next;
	}
	command_list[i] = 0;
	return (command_list);
}

void	when_child(t_env *env, char **command_list)
{
	struct stat	buf;
	char		*path;
	int			num;

	num = 0;
	if (stat(command_list[0], &buf) != -1)
	{
		if (execve(command_list[0], command_list, 0) != -1)
			exit(1);
	}
	else
	{
		path = get_path(env, command_list, num);
		if (path == 0)
		{
			printf("minishell: %s: command not found\n", command_list[0]);
			exit(1);
		}
		if (execve(path, command_list, 0) != -1)
			exit(1);
	}
}

void	pipe_do_execve(t_env *env, t_token_list *token)
{
	char		**command_list;

	command_list = NULL;
	command_list = get_command_list(token);
	when_child(env, command_list);
	ft_double_free(command_list);
}

void	do_execve(t_env *env, t_token_list *token)
{
	char		**command_list;
	pid_t		pid;
	int			status;

	status = 0;
	command_list = NULL;
	command_list = get_command_list(token);
	pid = fork();
	if (pid == 0)
		when_child(env, command_list);
	else if (pid > 0)
	{
		wait(&status);
		status = status >> 8;
		// write(2, "1111\n", 5);
	}
	ft_double_free(command_list);
}
