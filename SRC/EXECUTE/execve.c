/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyoo <yyoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 20:20:31 by yyoo              #+#    #+#             */
/*   Updated: 2022/06/09 19:28:47 by yyoo             ###   ########.fr       */
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
		command_list[i] = curr->text;
		i++;
		curr = curr->next;
	}
	command_list[i] = NULL;
	return (command_list);
}

void	child_err(t_env *envlst, char *command)
{
	if (command[ft_strlen(command) - 1] == '/')
	{
		write(2, "minishell: ", 11);
		write(2, command, ft_strlen(command));
		write(2, ": No such file or directory\n", 28);
	}
	else
	{
		write(2, "minishell: ", 11);
		write(2, command, ft_strlen(command));
		write(2, ": command not found\n", 20);
	}
	envlst->error = 127;
	exit(127);
}

void	when_child(t_env *envlst, char **command_list)
{
	char		*path;
	char		**converted_envlst;
	struct stat	buf;
	int			num;

	num = 0;
	converted_envlst = envlst_to_arr(envlst);
	if (converted_envlst == NULL)
		return ;
	if (stat(command_list[0], &buf) != -1)
	{
		if (execve(command_list[0], command_list, converted_envlst) != -1)
			exit(127);
	}
	else
	{
		path = get_path(envlst, command_list, num);
		if (execve(path, command_list, converted_envlst) != -1)
			exit(127);
	}
	child_err(envlst, command_list[0]);	
}

void	pipe_do_execve(t_env *envlst, t_token_list *token)
{
	char		**command_list;

	command_list = NULL;
	command_list = get_command_list(token);
	when_child(envlst, command_list);
	free(command_list);
}

void	do_execve(t_env *envlst, t_token_list *token)
{
	char		**command_list;
	pid_t		pid;
	int			status;

	status = 0;
	command_list = NULL;
	command_list = get_command_list(token);
	pid = fork();
	if (pid == 0)
		when_child(envlst, command_list);
	else if (pid > 0)
	{
		wait(&status);
		envlst->error = status >> 8;
	}
	free(command_list);
}
